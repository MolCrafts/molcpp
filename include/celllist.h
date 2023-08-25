#pragma once

#include <vector>
#include <array>
#include <cmath>

#include "error.h"
#include "vec3.hpp"
#include "box.h"

namespace molcpp
{

    class CellList
    {
        
    public:

        CellList(Box *box, double cell_width);

        size_t get_cell_index(Vec3<int>&) const;

        Vec3<int> get_cell_vector(size_t) const;

        void build(std::vector<Vec3<double>> &xyz);

        void update(std::vector<Vec3<double>> &xyz);

        void reset();

        size_t get_ncells();

        std::vector<size_t> get_atoms_in_cell(size_t cell_index) const;

        std::vector<size_t> get_neighbors(size_t cell_index) const;

    private:
        Box *_box;
        Vec3<double> _cell_length;
        size_t _natoms;
        double _r_cutoff;
        std::vector<size_t> _head;
        std::vector<size_t> _lscl;
        const size_t EMPTY = 0xffffffff;
    };

    std::unique_ptr<CellList> create_cellList(Box *box, double cell_width);
}

