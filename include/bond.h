#ifndef BOND_H
#define BOND_H

#include "graph.h"
#include "atom.h"

namespace MolCpp
{
    class Bond : public Edge
    {
        public:
            Bond(AtomPtr begin, AtomPtr end) : Edge{begin, end}, _bgn{begin}, _end{end} {}
            ~Bond() = default;

            AtomPtr get_bgn() const { return _bgn; }
            AtomPtr get_end() const { return _end; }

        private:
            AtomPtr _bgn, _end;

        
    };
    using BondPtr = std::shared_ptr<Bond>;

}

#endif // BOND_H