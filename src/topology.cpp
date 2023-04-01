#include "topology.h"

namespace molcpp
{

    bool Topology::add_atom(AtomPtr atom)
    {
        if (has_atom(atom)) return false;
        else _atoms.push_back(atom);
        return true;
    }

    bool Topology::has_atom(AtomPtr atom)
    {
        return std::find(_atoms.begin(), _atoms.end(), atom) != _atoms.end();
    }

    AtomPtr Topology::create_atom()
    {
        AtomPtr atom = molcpp::create_atom();  // using atom.h create_atom()
        add_atom(atom);
        return atom;
    }

    bool Topology::add_bond(BondPtr bond)
    {
        if (has_bond(bond))
        {
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

    BondPtr Topology::create_bond(AtomPtr itom, AtomPtr jtom)
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
            LOG_ERROR("Bond already exists");
            throw std::runtime_error("Bond already exists");
        }
    }

    BondPtr Topology::create_bond(size_t itom_index, size_t jtom_index)
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

}