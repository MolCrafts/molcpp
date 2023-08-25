#include "celllist.h"

namespace molcpp
{

    CellList::CellList(Box *box, double r_cutoff) : _box(box), _r_cutoff(r_cutoff)
    {
        auto cell_length = box->get_lengths();
        for (int i = 0; i < 3; i++)
        {
            _cell_length[i] = std::floorf(cell_length[i] / r_cutoff);
        }
    }

    size_t CellList::get_cell_index(Vec3<int> &cell_vector) const
    {
        // c = cxLcyLcz + cyLcz + cz
        return cell_vector[0] * _cell_length[1] * _cell_length[2] + cell_vector[1] * _cell_length[2] + cell_vector[2];
    }

    Vec3<int> CellList::get_cell_vector(size_t cell_index) const
    {
        // cx = c / (LcyLcz)
        // cy = (c / Lcz) - cxLcy or (c / Lcz) mod Lcy
        // cz = c mod Lcz
        Vec3<int> cell_vector;
        cell_vector[0] = cell_index / (_cell_length[1] * _cell_length[2]);
        cell_vector[1] = std::fmod((cell_index / _cell_length[2]), _cell_length[1]);
        cell_vector[2] = std::fmod(cell_index, _cell_length[2]);
        return cell_vector;
    }

    void CellList::build(std::vector<Vec3<double>> &xyz)
    {

        void reset();

        void update(std::vector<Vec3<double>> & xyz);
    }

    void CellList::update(std::vector<Vec3<double>> &xyz)
    {
        size_t n_atoms = xyz.size();
        _natoms += n_atoms;
        Vec3<int> xyz_cell_index;
        xyz = _box->wrap(xyz);
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

    size_t CellList::get_ncells()
    {
        return _cell_length[0] * _cell_length[1] * _cell_length[2];
    }

    std::vector<size_t> CellList::get_atoms_in_cell(size_t cell_index) const
    {
        std::vector<size_t> atoms_in_cell;
        size_t atom_index = _head[cell_index];
        while (atom_index != EMPTY)
        {
            atoms_in_cell.push_back(atom_index);
            atom_index = _lscl[atom_index];
        }
        return atoms_in_cell;
    }

    std::vector<size_t> CellList::get_neighbors(size_t cell_index) const
    {
        std::vector<size_t> neighbors;
        Vec3<int> cell_vector = get_cell_vector(cell_index);
        for (size_t x = cell_vector[0] - 1; x <= cell_vector[0] + 1; x++)
        {
            for (size_t y = cell_vector[1] - 1; y <= cell_vector[1] + 1; y++)
            {
                for (size_t z = cell_vector[2] - 1; z <= cell_vector[2] + 1; z++)
                {
                    // periodic
                    if (x < 0)
                    {
                        x += _cell_length[0];
                    }
                    else if (x >= _cell_length[0])
                    {
                        x -= _cell_length[0];
                    }

                    if (y < 0)
                    {
                        y += _cell_length[1];
                    }
                    else if (y >= _cell_length[1])
                    {
                        y -= _cell_length[1];
                    }

                    if (z < 0)
                    {
                        z += _cell_length[2];
                    }
                    else if (z >= _cell_length[2])
                    {
                        z -= _cell_length[2];
                    }

                    Vec3<int> neighbor_cell_vector = {x, y, z};
                    size_t neighbor_cell_index = get_cell_index(neighbor_cell_vector);
                    if (neighbor_cell_index != cell_index)
                    {
                        neighbors.push_back(neighbor_cell_index);
                    }
                }
            }
        }

        return neighbors;
    }

}