#include "neighborList.h"

namespace molcpp
{

    NeighborList::NeighborList(Cell *cell, double r_cutoff) : r_cutoff(r_cutoff)
    {
        if (r_cutoff <= 0)
        {
            throw ValueError("Cutoff radius must be positive");
        }

        _cellList = CellList(cell, r_cutoff * 2);
        _neighborListArray = NeighborListArray();
    }

    NeighborList::~NeighborList()
    {
    }

    void NeighborList::build(AtomVec atoms)
    {
        _neighborListArray.resize(atoms.size());
        // estimate atom density and # of neighbor of an atom
        double _approx_density = atoms.size() / _cellList.get_ncells();
        size_t _approx_nneighbors = static_cast<size_t>(4 * _approx_density * 4 * M_PI * r_cutoff * r_cutoff * r_cutoff / 3);
        std::for_each(_neighborListArray.begin(), _neighborListArray.end(), [](auto &vec)
                      { vec.reserve(_approx_nneighbors); });

        update(atoms);
    }

    void NeighborList::update(AtomVec atoms)
    {
        _cellList.reset();
        _cellList.add_atoms(atoms);
        for (size_t x = 0; x < _cellList.get_ncell_x(); ++x)
        {
            for (size_t y = 0; y < _cellList.get_ncell_y(); ++y)
            {
                for (size_t z = 0; z < _cellList.get_ncell_z(); ++z)
                {
                    auto cell = _cellList.get_vicinity(x, y, z);
                    for (auto atom : cell)
                    {
                        Vector3D pos = atom->get<Vector3D>("position");
                        for (auto neighbor : cell)
                        {
                            if (atom == neighbor)
                            {
                                continue;
                            }
                            Vector3D neighbor_pos = neighbor->get<Vector3D>("position");
                            Vector3D diff = pos - neighbor_pos;
                            if (diff.norm() < r_cutoff)
                            {
                                _neighborListArray[atom->get_id()].push_back(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }

}