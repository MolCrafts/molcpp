#include "cellList.h"

namespace molcpp
{
    CellList::CellList(Cell *cell, double cell_width) : _cell{cell}
    {
        if (cell_width <= 0)
        {
            throw ValueError("Cell width must be positive");
        }
        Vector3D lengths = cell->get_lengths();
        double x = lengths[0];
        double y = lengths[1];
        double z = lengths[2];

        reset(
            static_cast<size_t>(std::ceil(x / cell_width)),
            static_cast<size_t>(std::ceil(y / cell_width)),
            static_cast<size_t>(std::ceil(z / cell_width)));
    }

    void CellList::reset(size_t ncell_x, size_t ncell_y, size_t ncell_z)
    {
        _ncell_x = ncell_x;
        _ncell_y = ncell_y;
        _ncell_z = ncell_z;
        _cellListArray.resize(ncell_x);
        for (size_t i = 0; i < ncell_x; ++i)
        {
            _cellListArray[i].resize(ncell_y);
            for (size_t j = 0; j < ncell_y; ++j)
            {
                _cellListArray[i][j].resize(ncell_z);
            }
        }
    }

    void CellList::add_atom(Atom *atom)
    {
        Vector3D pos = atom->get<Vector3D>("position");
        size_t i = static_cast<size_t>(std::floor(pos[0] / _ncell_x));
        size_t j = static_cast<size_t>(std::floor(pos[1] / _ncell_y));
        size_t k = static_cast<size_t>(std::floor(pos[2] / _ncell_z));
        _cellListArray[i][j][k].push_back(atom);
    }

    void CellList::add_atoms(AtomVec atoms)
    {
        for (auto atom : atoms)
        {
            add_atom(atom);
        }
    }
}