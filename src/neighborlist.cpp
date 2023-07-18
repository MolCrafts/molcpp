#include "neighborList.h"

namespace molcpp
{

    NeighborList::NeighborList(Box* box, double r_cutoff) : _box(box), _r_cutoff(r_cutoff), _cell_list(box, r_cutoff)
    {
        if (r_cutoff <= 0)
        {
            throw ValueError("Cutoff radius must be positive");
        }

    }

    NeighborList::~NeighborList()
    {
    }

    void NeighborList::reset()
    {
        _neighborListArray.clear();
    }

    void NeighborList::build(std::vector<Vector3D>& xyz)
    {
        size_t natoms = xyz.size();

        _neighborListArray.resize(natoms);

        _cell_list.build(xyz);

        update(xyz);

    }

    void NeighborList::update(std::vector<Vector3D>& xyz)
    {
        size_t n_cells = _cell_list.get_ncells();
        for (size_t cell_index = 0; cell_index < n_cells; ++cell_index)
        {
            for (size_t i : _cell_list.get_atoms_in_cell(cell_index))
            {
                for (auto neighbor : _cell_list.get_neighbors(cell_index))
                {
                    for (size_t j : _cell_list.get_atoms_in_cell(neighbor))
                    {
                        if (i < j) // Avoid double counting
                        {
                            Vector3D pos_i = xyz[i];
                            Vector3D pos_j = xyz[j];
                            double r = _box->calc_distance(pos_i, pos_j);
                            if (r < _r_cutoff)
                            {
                                _neighborListArray[i].push_back(j);
                                _neighborListArray[j].push_back(i);
                            }
                        }
                    }
                }
            }
        }
    }

}