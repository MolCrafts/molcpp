#include "atom.h"
#include "bond.h"

namespace MolCpp
{

    Bond::Bond(AtomPtr bgn, AtomPtr end) : Edge{std::dynamic_pointer_cast<Node>(bgn), std::dynamic_pointer_cast<Node>(end)} {}

    AtomPtr Bond::get_itom() const
    {
        return std::static_pointer_cast<Atom>(get_bgn());
    }

    AtomPtr Bond::get_jtom() const
    {
        return std::static_pointer_cast<Atom>(get_end());
    }

}