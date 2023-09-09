#include "frame.h"
#include "test_utils.h"
#include "trajectory.h"

namespace molcpp
{

TEST_SUITE("Test Trajectory")
{

    TEST_CASE("test_init")
    {
        auto traj = Trajectory(TEST_DATA_DIR / "xyz" / "spaces.xyz");
    }

    TEST_CASE("test_add_frame")
    {
        auto traj = Trajectory(TMP_DIR / "test_add_frame.xyz", 'w', "xyz");
        auto frame = Frame();
        traj.add_frame(frame);
        CHECK_EQ(traj.get_nsteps(), 1);
    }

    TEST_CASE("test_read_step")
    {
        auto traj = Trajectory(TEST_DATA_DIR / "lammps" / "polymer.lammpstrj");
        auto frame0 = traj.read_step(0);
        auto frame500 = traj.read_step(500);
        CHECK_EQ(frame0.get_timestep(), 0);
        CHECK_EQ(frame500.get_timestep(), 500);

        auto traj2 = Trajectory();
        traj2.add_frame(frame0);
        traj2.add_frame(frame500);
        CHECK_EQ(traj2.get_nsteps(), 2);
        CHECK_EQ(traj2.get_step(0).get_timestep(), 0);
        CHECK_EQ(traj2.get_step(500).get_timestep(), 500);
    }

    TEST_CASE("test_load_single_frame")
    {
        auto traj = Trajectory(TEST_DATA_DIR / "xyz/methane.xyz", 'r', "XYZ");
        ;
        CHECK_EQ(traj.get_nsteps(), 1);
    }

    TEST_CASE("test_load_multiple_frame")
    {
        auto traj = Trajectory(TEST_DATA_DIR / "lammps/polymer.lammpstrj", 'r', "LAMMPS");
        CHECK_EQ(traj.get_nsteps(), 42);
    }

    TEST_CASE("test_write_single_frame")
    {

        auto traj_in = Trajectory(TEST_DATA_DIR / "lammps-data/solvated.lmp", 'r', "LAMMPS Data");
        CHECK_EQ(traj_in.get_nsteps(), 1);

        auto tempFile = TMP_DIR / "test_write_single_frame.pdb";
        auto traj_out = Trajectory(tempFile, 'w', "PDB");
        auto frame = traj_in.read_next();
        traj_out.add_frame(frame);
        traj_out.write();

        auto traj_test = chemfiles::Trajectory(tempFile, 'r', "PDB");
        auto _frame_out = traj_test.read();
        CHECK_EQ(traj_test.nsteps(), 1);
    }
}

} // namespace molcpp