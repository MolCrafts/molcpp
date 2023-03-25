#include "atom.h"
#include "bond.h"

namespace MolCpp
{

    bool Atom::add_bond(BondPtr bond)
    {
        return add_edge(std::dynamic_pointer_cast<Edge>(bond));
    }

    bool Atom::has_bond(BondPtr bond) 
    { return has_edge(std::dynamic_pointer_cast<Edge>(bond)); }

    bool Atom::del_bond(BondPtr bond)
    { return del_edge(std::dynamic_pointer_cast<Edge>(bond)); }

    BondVec Atom::get_bonds() const
    {
        BondVec _bonds;
        _bonds.reserve(get_nbonds());
        for (const auto edge : get_edges())
        {
            _bonds.push_back(std::static_pointer_cast<Bond>(edge));
        }
        return _bonds;
    }

}