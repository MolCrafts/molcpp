#include "cellList.h"

namespace molcpp
{

    CellList::CellList(Cell *cell, double r_cutoff)
    {
        _cell = cell;
        _r_cutoff = r_cutoff;
        auto cell_length = cell->get_lengths();
        for (int i = 0; i < 3; i++)
        {
            _cell_length[i] = std::floorf(cell_length[i] / r_cutoff);
        }
    }

    size_t CellList::get_cell_index(std::array<size_t, 3> &cell_vector)
    {
        // c = cxLcyLcz + cyLcz + cz
        return cell_vector[0] * _cell_length[1] * _cell_length[2] + cell_vector[1] * _cell_length[2] + cell_vector[2];
    }

    std::array<size_t, 3> CellList::get_cell_vector(size_t cell_index)
    {
        // cx = c / (LcyLcz)
        // cy = (c / Lcz) - cxLcy or (c / Lcz) mod Lcy
        // cz = c mod Lcz
        std::array<size_t, 3> cell_vector;
        cell_vector[0] = cell_index / (_cell_length[1] * _cell_length[2]);
        cell_vector[1] = std::fmod((cell_index / _cell_length[2]), _cell_length[1]);
        cell_vector[2] = std::fmod(cell_index, _cell_length[2]);
        return cell_vector;
    }

    void CellList::build(std::vector<Vector3D> &xyz)
    {

        void reset();

        void update(std::vector<Vector3D> & xyz);
    }

    void CellList::update(std::vector<Vector3D> &xyz)
    {
        size_t n_atoms = xyz.size();
        _natoms += n_atoms;
        std::array<size_t, 3> xyz_cell_index;
        for (size_t i = 0; i < n_atoms; i++)
        {

            for (int j = 0; j < 3; ++j)
            {
                xyz_cell_index[i] = static_cast<size_t>(std::floorf(xyz[i][j] / _r_cutoff));
            }
            size_t cell_index = get_cell_index(xyz_cell_index);
            _lscl[i] = _head[cell_index];
            _head[cell_index] = i;
        }
    }

    void CellList::reset()
    {
        _natoms = 0;
        _head.resize(_cell_length[0] * _cell_length[1] * _cell_length[2], EMPTY);
        _lscl.resize(_natoms, EMPTY);
    }

}