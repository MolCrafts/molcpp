#pragma once

#include "graph.h"
#include "forcefield.h"

namespace molcpp
{

    namespace cg
    {

        class Atom : protected Node
        {
            public:
                Atom() : Node {} {}

                bool add_bond(BondPtr);
                bool has_bond(BondPtr);
                bool del_edge(BondPtr);
                AtomVec get_neighbors();

            private:
                std::string _typename;
                AtomTypePtr _type;


        }

    }

}