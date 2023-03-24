#pragma once

#include "graph.h"

namespace MolCpp
{
    class Atom;
    using AtomPtr = std::shared_ptr<Atom>;
    using AtomVec = std::vector<AtomPtr>;
    class Bond;
    using BondPtr = std::shared_ptr<Bond>;
    using BondVec = std::vector<BondPtr>;

    class Bond : protected Edge
    {
    public:
        Bond(AtomPtr bgn, AtomPtr end) : Edge{std::static_pointer_cast<Node>(bgn), std::static_pointer_cast<Node>(end)} {}
        AtomPtr get_itom() const { return std::static_pointer_cast<Atom>(get_bgn()); }
        AtomPtr get_jtom() const { return std::static_pointer_cast<Atom>(get_end()); }
    };

}
