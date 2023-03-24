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
            bool add_bond(BondPtr bond) { return add_edge(std::static_pointer_cast<Edge>(bond)); }
            bool has_bond(BondPtr bond) { return has_edge(std::static_pointer_cast<Edge>(bond)); }
            bool del_bond(BondPtr bond) { return del_edge(std::static_pointer_cast<Edge>(bond)); }
            BondVec get_bonds() const;
            size_t get_nbonds() const { return get_nedges(); }


        protected:

        private:
            

    };

}
