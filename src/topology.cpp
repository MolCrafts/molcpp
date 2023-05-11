#include "topology.h"

namespace molcpp
{
    // Topology::Topology(const chemfiles::Topology &chflTopology)
    // {
    //     _atoms.reserve(chflTopology.size());
    //     _bonds.reserve(chflTopology.bonds().size());
    //     // get atoms
    //     for (auto chflatom : chflTopology)
    //     {
    //         auto mpatom = new_atom();

    //         mpatom->set("name", chflatom.name());
    //         mpatom->set("type", chflatom.type());
    //         mpatom->set("mass", chflatom.mass());
    //         mpatom->set("charge", chflatom.charge());
    //         if (chflatom.full_name()) mpatom->set("full_name", chflatom.full_name().value());
    //         if (chflatom.vdw_radius()) mpatom->set("vdw_radius", chflatom.vdw_radius().value());
    //         if (chflatom.covalent_radius()) mpatom->set("covalent_radius", chflatom.covalent_radius().value());
    //         if (chflatom.atomic_number()) mpatom->set("atomic_number", static_cast<int>(chflatom.atomic_number().value()));

    //         this->add_atom(mpatom);
    //     }
    //     // get bonds
    //     for (auto chflbond : chflTopology.bonds())
    //     {
    //         auto mpabond = new_bond(chflbond[0], chflbond[1]);
    //         this->add_bond(mpabond);
    //     }
    // }

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

    // factory function

    TopologyPtr new_topology()
    {
        return std::make_shared<Topology>();
    }

}