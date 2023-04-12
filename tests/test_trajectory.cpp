#include "utils.h"
#include "trajectory.h"

namespace fs = std::filesystem;

namespace molcpp{

    TEST(TestTrajctory, test_load_only_atoms)
    {
        auto traj = Trajectory( TEST_DATA_DIR / "xyz/methane.xyz", 'r', "XYZ");
        EXPECT_EQ(traj.nsteps(), 1);
        traj.close();
    }

}