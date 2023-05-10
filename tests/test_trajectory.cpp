#include "utils.h"
#include "trajectory.h"

namespace molcpp{

    TEST(TestTrajectory, test_load_single_frame)
    {
        auto traj = Trajectory( TEST_DATA_DIR / "xyz/methane.xyz", 'r', "XYZ");
        EXPECT_EQ(traj.get_nsteps(), 1);
        traj.close();
    }

    TEST(TestTrajectory, test_load_multiple_frame)
    {
        auto traj = Trajectory( TEST_DATA_DIR / "lammps/polymer.lammpstrj", 'r', "LAMMPS");
        EXPECT_EQ(traj.get_nsteps(), 42);
        traj.close();
    }

}