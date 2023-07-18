#pragma once
#include "cellList.h"
#include "box.h"

namespace molcpp
{

    class NeighborList
    {
        using NeighborListArray = std::vector<std::vector<size_t>>;

        NeighborList(Box* box, double r_cutoff);

        ~NeighborList();

        void reset();

        void build(std::vector<Vector3D> &xyz);

        void update(std::vector<Vector3D> &xyz);

        private:

            Box* _box;
            CellList _cell_list;
            double _r_cutoff;
            NeighborListArray _neighborListArray;
    };

}
