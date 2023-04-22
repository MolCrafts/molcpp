#include "topology.h"

namespace molcpp
{
    Topology::Topology(size_t natoms, size_t nbonds = 0) : _atoms(natoms), _bonds(nbonds) 
    {

    }

    Topology::Topology(const chemfiles::Topology &chflTopology)
    {
        _atoms.reserve(chflTopology.size());
        // _bonds.reserve(chflTopology.bonds().size());
        // get atoms
        for (auto chflatom : chflTopology)
        {
            auto mpatom = create_atom();
    
            mpatom->set("name", chflatom.name());
            mpatom->set("type", chflatom.type());
            mpatom->set("mass", chflatom.mass());
            mpatom->set("charge", chflatom.charge());
            if (chflatom.full_name()) mpatom->set("full_name", chflatom.full_name().value());
            if (chflatom.vdw_radius()) mpatom->set("vdw_radius", chflatom.vdw_radius().value());
            if (chflatom.covalent_radius()) mpatom->set("covalent_radius", chflatom.covalent_radius().value());
            if (chflatom.atomic_number()) mpatom->set("atomic_number", static_cast<int>(chflatom.atomic_number().value()));

            this->add_atom(mpatom);
        }
        // get bonds
        // for (auto chflbond : chflTopology.bonds())
        // {
        //     auto mpabond = new_bond(chflbond[0], chflbond[1]);
        //     this->add_bond(mpabond);
        // }
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
        AtomPtr atom = molcpp::create_atom();
        if (add_atom(atom)) return atom;
        else throw std::runtime_error("Atom already exists");
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
        BondPtr bond = molcpp::create_bond(itom, jtom);
        if (add_bond(bond))
        {
            itom->add_bond(bond);
            jtom->add_bond(bond);
            return bond;
        }
        else
        {
            throw std::runtime_error("Bond already exists");
        }
    }

    BondPtr Topology::new_bond(size_t itom_index, size_t jtom_index)
    {
        return create_bond(_atoms[itom_index], _atoms[jtom_index]);
    }

    // bool Topology::del_bond(BondPtr bond)
    // {
    //     auto result = find_in_container<std::vector<BondPtr>, BondPtr>(_bonds, bond);
    //     if (result.has_value())
    //     {
    //         _bonds.erase(_bonds.begin() + result.value());
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    // factory function

    TopologyPtr create_topology()
    {
        return std::make_shared<Topology>();
    }

    TopologyPtr create_topology(size_t natoms, size_t nbonds = 0)
    {
        return std::make_shared<Topology>(natoms, nbonds);
    }

    TopologyPtr create_topology(const chemfiles::Topology &chflTopology)
    {
        return std::make_shared<Topology>(chflTopology);
    }

}