#include "bond.h"

namespace MolCpp
{

    Bond::Bond(AtomPtr begin, AtomPtr end) : Edge(std::static_pointer_cast<Node>(begin);, std::static_pointer_cast<Node>(end);)
    {
    }

}