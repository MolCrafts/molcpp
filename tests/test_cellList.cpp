#include "utils.h"
#include "box.h"
#include "cellList.h"
#include <gtest/gtest.h>

namespace molcpp
{
    TEST(TestCellList, test_init)
    {
        Box* box = new Box({10, 10, 10});
        CellList cellList(box, 3);
        EXPECT_EQ(cellList.get_ncells(), 27);
        EXPECT_EQ(cellList.get_atoms_in_cell(0).size(), 0);

        auto xyz = std::vector<Vector3D>{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {3, 3, 3}};

        cellList.build(xyz);
        EXPECT_EQ(cellList.get_atoms_in_cell(0).size(), 4);
    }

    TEST(TestCellList, test_homogenious)
    {
        auto _traj = chemfiles::Trajectory( TEST_DATA_DIR / "lammps-data/solvated.lmp", 'r', "LAMMPS-Data");

        auto _frame = _traj.read();
        auto positions = _frame.positions();
        auto Cell = _frame.cell();
        auto box = from_chemfiles(Cell);
        auto cellList = create_cellList(box.get(), 5);
        std::vector<Vector3D> xyz(positions.size());
        for (size_t i = 0; i < positions.size(); i++)
        {
            xyz[i] = {positions[i][0], positions[i][1], positions[i][2]};
        }
        cellList->build(xyz);

        auto ncells = cellList->get_ncells();
        EXPECT_EQ(ncells, 27);

        EXPECT_EQ(cellList->get_atoms_in_cell(0).size(), 4);

    }

    
}