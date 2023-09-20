#include "test_utils.h"

namespace molcpp
{

TEST_SUITE("TestDataLoader")
{
    TEST_CASE("test_load_traj")
    {
        DataReader reader(TEST_DATA_DIR / "lammps" / "polymer.lammpstrj", "LAMMPS");
        auto traj = reader.load_tral(0, 10, 1);
        CHECK_EQ(traj.get_nsteps(), 10);
    }

    TEST_CASE("test_load_frame")
    {
        auto traj = Trajectory(TEST_DATA_DIR / "lammps" / "polymer.lammpstrj");
        auto frame0 = traj.load_frame(0);
        auto frame500 = traj.load_frame(500);
        CHECK_EQ(frame0.get_timestep(), 0);
        CHECK_EQ(frame500.get_timestep(), 500);
    }

    TEST_CASE("test_load_single_frame")
    {
        auto traj = Trajectory(TEST_DATA_DIR / "xyz/methane.xyz", 'r', "XYZ");
        ;
        CHECK_EQ(traj.get_nsteps(), 1);
    }

    TEST_CASE("test_load_multiple_frame")
    {
        DataReader reader(TEST_DATA_DIR / "lammps/polymer.lammpstrj", 'r', "LAMMPS");
        auto traj = reader.load_traj();  // load all frames
        CHECK_EQ(traj.get_nsteps(), 42);
    }

    TEST_CASE("test_write_single_frame")
    {

        DataReader reader(TEST_DATA_DIR / "lammps-data/solvated.lmp", 'r', "LAMMPS Data");
        auto frame = reader.load_frame();  // load first frame
        CHECK_EQ(frame.get_timestep(), 1);

        // auto tempFile = TMP_DIR / "test_write_single_frame.pdb";
        // auto traj_out = Trajectory(tempFile, 'w', "PDB");
        // auto frame = traj_in.read_next();
        // traj_out.add_frame(frame);
        // traj_out.write();

        // auto traj_test = chemfiles::Trajectory(tempFile, 'r', "PDB");
        // auto _frame_out = traj_test.read();
        // CHECK_EQ(traj_test.nsteps(), 1);
    }
}

} // namespace molcpp