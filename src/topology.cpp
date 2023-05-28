#include "topology.h"

namespace molcpp
{
    Topology::Topology() : _atoms{}, _atomTopoMask{}, _bonds{}, _bondConnect{}
    {
    }

    Topology::~Topology()
    {
        for (auto bond : _bonds)
        {
            delete bond;
        }
        for (auto atom : _atoms)
        {
            delete atom;
        }
    }

    void Topology::add_atom(Atom *atom)
    {
        _atoms.push_back(atom);
    }

    bool Topology::has_atom(Atom *atom)
    {
        auto results = std::find_if(_atoms.begin(), _atoms.end(), [atom](Atom* a)
                                    { return a->equal_to(atom); });
        return results == _atoms.end() ? false : true;
    }

    Atom *Topology::create_atom(const std::string &name, Vector3D pos)
    {
        _atoms.emplace_back(new Atom(name, pos));
        return _atoms.back();
    }

    void Topology::del_atom(Atom *atom)
    {
        
        for (auto bond : _bonds)
        {
            if (bond->get_itom() == atom || bond->get_jtom() == atom)
            {
                delete bond;
            }
        }

        std::erase(_atoms, atom);
    }

    AtomVec &Topology::get_atoms()
    {
        return _atoms;
    }

    void Topology::add_bond(Bond *bond)
    {
        _bonds.push_back(bond);
    }

    bool Topology::has_bond(Bond *bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](Bond* b)
                                    { return b == bond; });
        return results == _bonds.end() ? false : true;
    }

    Bond *Topology::create_bond(Atom *itom, Atom *jtom)
    {
        auto i = std::find(_atoms.begin(), _atoms.end(), itom);
        auto j = std::find(_atoms.begin(), _atoms.end(), jtom);
        connect(std::distance(_atoms.begin(), i), std::distance(_atoms.begin(), j));

        _bonds.emplace_back(new Bond(itom, jtom));
        return _bonds.back();
    }

    Bond *Topology::create_bond(size_t itom_index, size_t jtom_index)
    {
        connect(itom_index, jtom_index);

        Atom *itom = _atoms[itom_index];
        Atom *jtom = _atoms[jtom_index];
        _bonds.emplace_back(new Bond(itom, jtom));
        return _bonds.back();
    }

    void Topology::connect(size_t i, size_t j)
    {
        check_connect(i, j);
        _bondConnect.emplace_back(std::initializer_list<size_t>{i, j});
    }

    void Topology::check_connect(size_t i, size_t j)
    {
        if (i == j)
        {
            auto msg = "Cannot connect atom index " + std::to_string(i) + " to itself";
            throw ValueError(msg);
        }

        if (i > _atoms.size() || j > _atoms.size())
        {
            auto msg = "Cannot connect atom index " + std::to_string(i) + " to " + std::to_string(j) + " because one of them is out of range";
            throw IndexError(msg);
        }
    }

    Bond *Topology::get_bond(Atom *itom, Atom *jtom)
    {
        auto result = std::find_if(_bonds.begin(), _bonds.end(), [itom, jtom](Bond* bond)
                                   { return bond->get_itom() == itom && bond->get_jtom() == jtom; });
        if (result != _bonds.end())
        {
            return *result;
        }
        else
        {
            throw KeyError("Bond not found");
        }
    }

    Bond *Topology::get_bond(size_t itom_index, size_t jtom_index)
    {
        check_connect(itom_index, jtom_index);
        Atom *itom = _atoms[itom_index];
        Atom *jtom = _atoms[jtom_index];
        return get_bond(itom, jtom);
    }

    void Topology::del_bond(Bond *bond)
    {
        std::erase(_bonds, bond);
    }

    void Topology::del_bond(Atom *itom, Atom *jtom)
    {
        auto bond = molcpp::create_bond(itom, jtom);
        del_bond(bond.get());
    }

    void Topology::set(const std::string &key, const xt::xarray<AtomProperty> &value)
    {
        if (value.size() != get_natoms())
            throw ValueError("The size of the value array must be equal to the number of atoms");

        for (size_t i = 0; i < get_natoms(); i++)
        {
            _atoms[i]->set(key, value[i]);
        }
    }

    void Topology::set_positions(xt::xarray<double> &positions)
    {
        if (positions.shape().size() == 2)
        {
            if (positions.shape()[0] != get_natoms())
                throw ValueError("The size of the positions array must be equal to the number of atoms");
        }
        else
        {
            throw ValueError("The positions array must be 2D");
        }

        int i = 0;
        for (auto &atom : get_atoms())
        {
            atom->set_position(Vector3D(positions(i, 0), positions(i, 1), positions(i, 2)));
            i++;
        }
    }

    xt::xarray<double> Topology::get_positions()
    {
        auto natoms = get_natoms();
        std::vector<double> positions(natoms * 3);
        auto &atoms = get_atoms();
        for (size_t i = 0; i < natoms; i++)
        {
            auto pos = atoms[i]->get_position();
            positions[i * 3] = pos[0];
            positions[i * 3 + 1] = pos[1];
            positions[i * 3 + 2] = pos[2];
        }
        std::vector<std::size_t> shape = {natoms, 3};
        return xt::adapt(positions, shape);
    }

    std::unique_ptr<Topology> from_chemfiles(const chemfiles::Topology &chflTopo)
    {
        auto topo = create_topology();
        for (auto chflAtom : chflTopo)
        {
            auto atom = from_chemfiles(chflAtom);
            topo->add_atom(atom.release());
        }

        for (auto chflBond : chflTopo.bonds())
        {
            topo->create_bond(chflBond[0], chflBond[1]);
        }
        return topo;
    }

    chemfiles::Topology to_chemfiles(Topology *topo)
    {
        chemfiles::Topology chflTopo;
        for (auto atom : topo->get_atoms())
        {
            chflTopo.add_atom(to_chemfiles(atom));
        }

        for (auto bond : topo->get_bond_connect())
        {
            chflTopo.add_bond(bond[0], bond[1]);
        }
        return chflTopo;
    }

    std::unique_ptr<Topology> create_topology()
    {
        return std::make_unique<Topology>();
    }

}