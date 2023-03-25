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
        Bond(AtomPtr bgn, AtomPtr end);
        AtomPtr get_itom() const;
        AtomPtr get_jtom() const;
    };

}
