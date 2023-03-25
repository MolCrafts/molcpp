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


    class Atom : protected Node
    {

        public:
            Atom(): Node{} {}
            bool add_bond(BondPtr);
            bool has_bond(BondPtr bond);
            bool del_bond(BondPtr bond);
            BondVec get_bonds() const;
            size_t get_nbonds() const { return get_nedges(); }


        protected:

        private:
            

    };

}
