#include "topology.h"

namespace molcpp
{
    Topology::Topology() : _atoms{}, _bonds{}, _bondConnect{}
    {
    }

    bool Topology::add_atom(AtomPtr atom)
    {
        if (has_atom(atom))
            return false;
        else
            _atoms.push_back(atom);
        return true;
    }

    bool Topology::has_atom(AtomPtr atom)
    {
        return std::find(_atoms.begin(), _atoms.end(), atom) != _atoms.end();
    }

    AtomPtr Topology::new_atom(const std::string &name)
    {
        AtomPtr atom = molcpp::new_atom(name);
        add_atom(atom);
        return atom;
    }

    bool Topology::del_atom(AtomPtr atom)
    {

        auto result = std::find(_atoms.begin(), _atoms.end(), atom);
        if (result != _atoms.end())
        {
            _atoms.erase(result);
            return true;
        }
        else
            return false;
    }

    const AtomVec &Topology::get_atoms() const
    {
        return _atoms;
    }

    bool Topology::add_bond(BondPtr bond)
    {
        if (has_bond(bond))
        {
            LOG_WARNING("Bond already exists");
            return false;
        }
        else
        {
            _bonds.push_back(bond);
            return true;
        }
    }

    bool Topology::has_bond(BondPtr bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b)
                                    { return *b == *bond; });
        return results == _bonds.end() ? false : true;
    }

    BondPtr Topology::new_bond(const AtomPtr &itom, const AtomPtr &jtom)
    {
        BondPtr bond = molcpp::new_bond(itom, jtom);
        size_t itom_index =
            std::find_if(_atoms.begin(), _atoms.end(), [itom](const AtomPtr atom)
                            { return *atom == *itom; }) -
            _atoms.begin();

        size_t jtom_index =
            std::find_if(_atoms.begin(), _atoms.end(), [jtom](const AtomPtr atom)
                            { return *atom == *jtom; }) -
            _atoms.begin();
        if (itom_index < _atoms.size() && jtom_index < _atoms.size())
        {
            connect(itom_index, jtom_index);
        }
        else
        {
            throw KeyError("Atom not found");
        }

        if (add_bond(bond))
        {
            itom->add_bond(bond);
            jtom->add_bond(bond);

            return bond;
        }
        else
        {
            throw KeyError("Bond already exists");
        }
    }

    BondPtr Topology::new_bond(size_t itom_index, size_t jtom_index)
    {
        BondPtr bond = molcpp::new_bond(_atoms.at(itom_index), _atoms.at(jtom_index));
        if(add_bond(bond)) connect(itom_index, jtom_index);
        else throw KeyError("Bond already exists");
        return bond;
    }

    void Topology::connect(size_t i, size_t j)
    {
        if (i == j) 
        {
            auto msg = "Cannot connect atom index " + std::to_string(i) + " to itself";
            throw ValueError(msg);
        }
        _bondConnect.emplace_back(std::initializer_list<size_t>{i, j});
    }

    const BondPtr Topology::get_bond(const AtomPtr &itom, const AtomPtr &jtom) const
    {
        auto result = std::find_if(_bonds.begin(), _bonds.end(), [itom, jtom](BondPtr bond)
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

    bool Topology::del_bond(BondPtr bond)
    {
        auto result = std::find(_bonds.begin(), _bonds.end(), bond);
        if (result != _bonds.end())
        {

            _bonds.erase(result);
            return true;
        }
        else
            return false;
    }

    bool Topology::del_bond(const AtomPtr &itom, const AtomPtr &jtom)
    {
        auto result = std::find_if(_bonds.begin(), _bonds.end(), [itom, jtom](BondPtr bond)
                                   { return bond->get_itom() == itom && bond->get_jtom() == jtom; });
        if (result != _bonds.end())
        {
            _bonds.erase(result);
            return true;
        }
        else
        {
            return false;
        }
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
        for (auto& atom : get_atoms())
        {
            atom->set_position(xt::row(positions, i));
            i++;
        }
    }

    const xt::xarray<double> Topology::get_positions() const
    {
        int natoms = get_natoms();
        xt::xarray<double> positions = xt::zeros<double>({natoms, 3});
        int i = 0;
        for (auto& atom : get_atoms())
        {
            xt::row(positions, i) = atom->get_position();
            i++;
        }
        return positions;
    }

    // factory function

    TopologyPtr new_topology()
    {
        return std::make_shared<Topology>();
    }

    TopologyPtr new_topology(const chemfiles::Topology &chflTopo)
    {
        auto topo = new_topology();
        for (auto chflAtom : chflTopo)
        {
            auto atom = new_atom(chflAtom);
            topo->add_atom(atom);
        }

        auto atoms = topo->get_atoms();
        for (auto chflBond : chflTopo.bonds())
        {
            topo->new_bond(chflBond[0], chflBond[1]);
        }
        return topo;
    }

    chemfiles::Topology to_chemfiles(const TopologyPtr &topo)
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

}