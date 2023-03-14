#ifndef BOND_H
#define BOND_H

#include "graph.h"
#include "atom.h"

namespace MolCpp
{

    class Bond : public Edge
    {
    public:
        Bond(AtomPtr, AtomPtr);

    private:
    };
    using BondPtr = std::shared_ptr<Bond>;

}

#endif // BOND_H