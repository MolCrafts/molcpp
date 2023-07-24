#pragma once

#include "mperror.h"
#include "box.h"
#include <array>
#include <cmath>

namespace molcpp
{

    class CellList
    {
        
    public:

        CellList(Box *box, double cell_width);

        size_t get_cell_index(std::array<size_t, 3>&) const;

        std::array<size_t, 3> get_cell_vector(size_t) const;

        void build(std::vector<Vector3D> &xyz);

        void update(std::vector<Vector3D> &xyz);

        void reset();

        size_t get_ncells();

        std::vector<size_t> get_atoms_in_cell(size_t cell_index) const;

        std::vector<size_t> get_neighbors(size_t cell_index) const;

    private:
        Box *_box;
        Vector3D _cell_length;
        size_t _natoms;
        double _r_cutoff;
        std::vector<size_t> _head;
        std::vector<size_t> _lscl;
        const size_t EMPTY = 0xffffffff;
    };

    std::unique_ptr<CellList> create_cellList(Box *box, double cell_width);
}

