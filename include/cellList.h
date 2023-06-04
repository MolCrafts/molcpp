#pragma once

#include "mperror.h"
#include "cell.h"
#include "atom.h"
#include "algo.h"

namespace molcpp
{

    class CellList
    {

        using cellListArray = std::vector<std::vector<std::vector<std::vector<Atom *>>>>;

    public:
        /**
         * @brief Construct a new Cell List:: Cell List object
         *
         * @param cell
         * @param cell_width Width of cells. If not provided, LinkCell will estimate a cell width based on the number of points and the box size, assuming a constant density of points in the box.
         */
        CellList(Cell *cell, double cell_width);

        void reset(size_t, size_t, size_t);

        void reset();

        void add_atom(Atom *);

        void add_atoms(AtomVec);

        size_t get_ncells();

        size_t get_ncell_x();

        size_t get_ncell_y();

        size_t get_ncell_z();

        std::vector<Atom*> get_vicinity(size_t, size_t, size_t);

    private:
        Cell *_cell;
        size_t _ncell_x, _ncell_y, _ncell_z;
        cellListArray _cellListArray;
    };

    std::unique_ptr<CellList> create_cellList(Cell *cell, double cell_width);
}