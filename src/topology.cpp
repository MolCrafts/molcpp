#include "topology.h"

namespace molcpp
{
    Topology::Topology() : _atoms{}, _bonds{}, _topos{}, _graph{}
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
        auto is_find_in_atoms = std::find_if(_atoms.begin(), _atoms.end(), [atom](Atom *a)
                                             { return a->equal_to(atom); });
        if (is_find_in_atoms == _atoms.end())
        {
            auto is_find_in_sub_topo = std::find_if(_topos.begin(), _topos.end(), [atom](Topology *t)
                                                    { return t->has_atom(atom); });
            return is_find_in_sub_topo == _topos.end() ? false : true;
        }
        else
            return true;
    }

    Atom *Topology::create_atom(const std::string &name, Vector3D pos)
    {
        _atoms.emplace_back(new Atom(name, pos));
        return _atoms.back();
    }

    void Topology::del_atom(Atom *atom)
    {
        size_t n = std::erase_if(_atoms, [atom](Atom *a)
                                 { return a->equal_to(atom); });
        if (n == 0)
        {
            for (auto topo : _topos)
            {
                size_t o_natoms = topo->get_natoms();
                topo->del_atom(atom);
                if (o_natoms != topo->get_natoms())
                    break;
            }
        }
    }

    AtomVec Topology::get_atoms()
    {
        AtomVec tmp(_atoms);
        for (auto topo : _topos)
        {
            AtomVec sub_atoms = topo->get_atoms();
            tmp.insert(tmp.end(), sub_atoms.begin(), sub_atoms.end());
        }
        return tmp;
    }

    void Topology::add_bond(Bond *bond)
    {
        _bonds.push_back(bond);
    }

    bool Topology::has_bond(Bond *bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](Bond *b)
                                    { return b == bond; });
        return results == _bonds.end() ? false : true;
    }

    bool Topology::has_bond(Atom *itom, Atom *jtom)
    {
        auto trial_bond = molcpp::create_bond(itom, jtom);
        Bond* bond = trial_bond.get();
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](Bond *b)
                                    { return b->equal_to(bond); });
        return results == _bonds.end() ? false : true;
    }

    Bond *Topology::create_bond(Atom *itom, Atom *jtom)
    {
        AtomVec atoms = get_atoms();
        auto i = std::find_if(atoms.begin(), atoms.end(), [itom](Atom *a)
                              { return a->equal_to(itom); });
        auto j = std::find_if(atoms.begin(), atoms.end(), [jtom](Atom* a){return a->equal_to(jtom);});
        if (i == atoms.end() || j == atoms.end())
            throw KeyError("Cannot find atom");
        connect(std::distance(_atoms.begin(), i), std::distance(_atoms.begin(), j));

        _bonds.emplace_back(new Bond(itom, jtom));
        return _bonds.back();
    }

    Bond *Topology::create_bond(size_t itom_index, size_t jtom_index)
    {
        AtomVec atoms = get_atoms();
        Atom *itom = atoms[itom_index];
        Atom *jtom = atoms[jtom_index];
        connect(itom_index, jtom_index);
        _bonds.emplace_back(new Bond(itom, jtom));
        return _bonds.back();
    }

    void Topology::connect(size_t i, size_t j)
    {
        _graph.add_edge(i, j);
    }

    void Topology::check_connect(size_t i, size_t j)
    {
        if (i == j)
        {
            auto msg = "Cannot connect atom index " + std::to_string(i) + " to itself";
            throw ValueError(msg);
        }

        if (i > get_natoms() || j > get_natoms())
        {
            auto msg = "Cannot connect atom index " + std::to_string(i) + " to " + std::to_string(j) + " because one of them is out of range";
            throw IndexError(msg);
        }
    }

    Bond *Topology::get_bond(Atom *itom, Atom *jtom)
    {
        auto trial_bond = molcpp::create_bond(itom, jtom);
        Bond* bond = trial_bond.get();
        auto is_find_in_bonds = std::find_if(_bonds.begin(), _bonds.end(), [bond](Bond *b)
                                             { return b->equal_to(bond); });
        if (is_find_in_bonds == _bonds.end())
        {
            auto is_find_in_sub_topo = std::find_if(_topos.begin(), _topos.end(), [bond](Topology *t)
                                                    { return t->has_bond(bond); });
            if (is_find_in_sub_topo == _topos.end())
                throw KeyError("Cannot find bond");
            else
                return (*is_find_in_sub_topo)->get_bond(itom, jtom);
        }
        else
            return *is_find_in_bonds;
    }

    Bond *Topology::get_bond(size_t itom_index, size_t jtom_index)
    {
        // check_connect(itom_index, jtom_index);
        AtomVec atoms = get_atoms();
        Atom *itom = atoms[itom_index];
        Atom *jtom = atoms[jtom_index];
        return get_bond(itom, jtom);
    }

    BondVec Topology::get_bonds() const
    {
        BondVec tmp(_bonds);
        for (auto topo : _topos)
        {
            BondVec sub_bonds = topo->get_bonds();
            tmp.insert(tmp.end(), sub_bonds.begin(), sub_bonds.end());
        }
        return tmp;
    }

    size_t Topology::get_nbonds() const
    {
        size_t nbonds = _bonds.size();
        for (auto topo : _topos)
            nbonds += topo->get_nbonds();
        return nbonds;
    }

    size_t Topology::get_natoms() const
    {
        size_t natoms = _atoms.size();
        for (auto topo : _topos)
            natoms += topo->get_natoms();
        return natoms;
    }

    void Topology::del_bond(Bond *bond)
    {   
        size_t n = std::erase_if(_bonds, [bond](Bond *b)
                                 { return b->equal_to(bond); });
        if (n == 0)
        {
            for (auto topo : _topos)
            {
                size_t o_nbonds = topo->get_nbonds();
                topo->del_bond(bond);
                if (o_nbonds != topo->get_nbonds())
                    break;
            }
        }
    }

    void Topology::del_bond(Atom *itom, Atom *jtom)
    {
        auto bond = molcpp::create_bond(itom, jtom);
        del_bond(bond.get());
    }

    Topology *Topology::create_topology()
    {
        Topology *topo = new Topology();
        _topos.emplace_back(topo);
        return topo;
    }

    void Topology::add_topology(Topology* topo)
    {
        _topos.emplace_back(topo);
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

    void Topology::set_positions(const xt::xarray<double> &positions)
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
        auto atoms = get_atoms();
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

    BondConnect Topology::get_bond_connect()
    {
        return _graph.get_bonds();
    }

    AngleConnect Topology::get_angle_connect()
    {
        return _graph.get_angles();
    }

    DihedralConnect Topology::get_dihedral_connect()
    {
        return _graph.get_dihedrals();
    }

    std::unique_ptr<Topology> from_chemfiles(const chemfiles::Topology& chflTopo)
    {
        auto topo = create_topology();
        for (auto& chflAtom : chflTopo)
        {
            auto atom = from_chemfiles(chflAtom);
            topo->add_atom(atom.release());
        }

        for (auto& chflBond : chflTopo.bonds())
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
            chflTopo.add_bond(std::get<0>(bond), std::get<1>(bond));
        }
        return chflTopo;
    }

    std::unique_ptr<Topology> create_topology()
    {
        return std::make_unique<Topology>();
    }

}