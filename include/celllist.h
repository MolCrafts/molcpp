#pragma once

#include "mperror.h"
#include "cell.h"
#include <array>
#include <cmath>

namespace molcpp
{

    class CellList
    {
        const size_t EMPTY = 0xffffffff;
    public:

        CellList(Cell *cell, double cell_width);

        size_t get_cell_index(std::array<size_t, 3>&);

        std::array<size_t, 3> get_cell_vector(size_t);

        void build(std::vector<Vector3D> &xyz);

        void update(std::vector<Vector3D> &xyz);

        void reset();

    private:
        Cell *_cell;
        Vector3D _cell_length;
        size_t _natoms;
        double _r_cutoff;
        std::vector<size_t> _head;
        std::vector<size_t> _lscl;
    };

    std::unique_ptr<CellList> create_cellList(Cell *cell, double cell_width);
}

