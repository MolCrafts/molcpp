#include "atom.h"

namespace MolCpp
{

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