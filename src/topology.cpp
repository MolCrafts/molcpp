#include "topology.h"

namespace molcpp
{
    Topology::Topology()
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

    AtomPtr Topology::new_atom()
    {
        AtomPtr atom = molcpp::new_atom();
        add_atom(atom);
        return atom;
    }

    bool Topology::del_atom(AtomPtr atom)
    {
        if (has_atom(atom))
        {
            _atoms.erase(std::find(_atoms.begin(), _atoms.end(), atom));
            return true;
        }
        else
        {
            return false;
        }
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
            if (has_atom(bond->get_itom()) && has_atom(bond->get_jtom()))
            {
                _bonds.push_back(bond);
                return true;
            }
            else
            {
                LOG_ERROR("Atom not found");
                throw std::runtime_error("Atom not found");
            }
        }
    }

    bool Topology::has_bond(BondPtr bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b)
                                    { return *b == *bond; });
        return results == _bonds.end() ? false : true;
    }

    BondPtr Topology::new_bond(AtomPtr itom, AtomPtr jtom)
    {
        BondPtr bond = molcpp::new_bond(itom, jtom);
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
        return new_bond(_atoms[itom_index], _atoms[jtom_index]);
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

    void Topology::set(const std::string& key, const xt::xarray<AtomProperty>& value)
    {
        if (value.size() != get_natoms()) 
            throw ValueError("The size of the value array must be equal to the number of atoms");

        for (size_t i = 0; i < get_natoms(); i++)
        {
            _atoms[i]->set(key, value[i]);
        }
    }

    // factory function

    TopologyPtr new_topology()
    {
        return std::make_shared<Topology>();
    }

    TopologyPtr new_topology(const chemfiles::Topology& chflTopo)
    {
        auto topo = new_topology();
        for (auto chflAtom : chflTopo)
        {
            auto atom = new_atom(chflAtom);
            topo->add_atom(atom);
        }

        auto atoms = topo->get_atoms();
        for (auto chflBond: chflTopo.bonds())
        {
            auto at0 = atoms[chflBond[0]];
            auto at1 = atoms[chflBond[1]];   
            auto bond = new_bond(at0, at1);
            topo->add_bond(bond);
        }
        return topo;
    }

}