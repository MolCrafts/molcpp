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
        _cellListArray.reserve(ncell_x);
        for (size_t i = 0; i < ncell_x; ++i)
        {
            _cellListArray[i].reserve(ncell_y);
            for (size_t j = 0; j < ncell_y; ++j)
            {
                _cellListArray[i][j].reserve(ncell_z);
            }
        }
    }

    void CellList::reset()
    {
        reset(_ncell_x, _ncell_y, _ncell_z);
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

    size_t CellList::get_ncells()
    {
        return _ncell_x * _ncell_y * _ncell_z;
    }

    size_t CellList::get_ncell_x()
    {
        return _ncell_x;
    }

    size_t CellList::get_ncell_y()
    {
        return _ncell_y;
    }

    size_t CellList::get_ncell_z()
    {
        return _ncell_z;
    }

    std::vector<Atom*> CellList::get_vicinity(size_t x, size_t y, size_t z)
    {
        std::vector<Atom*> vicinity;
        auto pbc = _cell->get_periodic();
        for (size_t i = x - 1; i <= x + 1; ++i)
        {
            if (i < 0 || i >= _ncell_x)
            {
                if (pbc[0]) i = (i + _ncell_x) % _ncell_x;
                else continue;
            }
            for (size_t j = y - 1; j <= y + 1; ++j)
            {
                if (j < 0 || j >= _ncell_y)
                {
                    if (pbc[1]) j = (j + _ncell_y) % _ncell_y;
                    else continue;
                }
                for (size_t k = z - 1; k <= z + 1; ++k)
                {
                    if (k < 0 || k >= _ncell_z)
                    {
                        if (pbc[2]) k = (k + _ncell_z) % _ncell_z;
                        else continue;
                    }
                    vicinity.insert(vicinity.end(), _cellListArray[i][j][k].begin(), _cellListArray[i][j][k].end());
                }
            }
        }
        return vicinity;
    }

    std::unique_ptr<CellList> create_cellList(Cell *cell, double cell_width)
    {
        return std::make_unique<CellList>(cell, cell_width);
    }
}