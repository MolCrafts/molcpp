#pragma once
#include "cellList.h"

namespace molcpp
{

    class NeighborList
    {
        using NeighborListArray = std::vector<std::vector<Atom*>>;

        public:
            NeighborList(Cell* cell, double r_cutoff);
            ~NeighborList();

            void build(AtomVec);
            void update(AtomVec);

        private:

            double r_cutoff;
            CellList _cellList;
            NeighborListArray _neighborListArray;
    };

}
