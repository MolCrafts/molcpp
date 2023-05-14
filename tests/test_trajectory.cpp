#include "utils.h"
#include "trajectory.h"

namespace molcpp{

    TEST(TestTrajectory, test_init)
    {
        auto traj = Trajectory();
    }

    TEST(TestTrajectory, test_add_frame)
    {
        auto traj = Trajectory();
        auto frame = new_frame();
        traj.add_frame(frame);
        EXPECT_EQ(traj.get_nsteps(), 1);
    }

    TEST(TestTrajectory, test_get_step)
    {
        auto traj = new_trajectory();
        auto f0 = new_frame();
        auto f199 = new_frame();
        f0->set_timestep(0);
        f199->set_timestep(199);
        traj->add_frame(f0);
        traj->add_frame(f199);
        EXPECT_EQ(traj->get_step(0)->get_timestep(), 0);
        EXPECT_EQ(traj->get_step(199)->get_timestep(), 199);
    }

    TEST(TestTrajectory, test_get_by_index)
    {
        auto traj = new_trajectory();
        auto f0 = new_frame();
        auto f199 = new_frame();
        f0->set_timestep(0);
        f199->set_timestep(199);
        traj->add_frame(f0);
        traj->add_frame(f199);
        EXPECT_EQ(traj->get_by_index(0)->get_timestep(), 0);
        EXPECT_EQ(traj->get_by_index(1)->get_timestep(), 199);
    }

    TEST(TestTrajectory, test_load_single_frame)
    {
        auto _traj = chemfiles::Trajectory( TEST_DATA_DIR / "xyz/methane.xyz", 'r', "XYZ");
        auto traj = new_trajectory(_traj);
        EXPECT_EQ(traj->get_nsteps(), 1);
    }

    TEST(TestTrajectory, test_load_multiple_frame)
    {
        auto _traj = chemfiles::Trajectory( TEST_DATA_DIR / "lammps/polymer.lammpstrj", 'r', "LAMMPS");
        auto traj = new_trajectory(_traj);
        EXPECT_EQ(traj->get_nsteps(), 42);
    }

    TEST(TestTrajectory, test_write_single_frame)
    {
        auto _traj_in = chemfiles::Trajectory( TEST_DATA_DIR / "lammps-data/solvated.lmp", 'r', "LAMMPS Data");
        auto traj = new_trajectory(_traj_in);
        // write to tmp file
        auto tempDir = ::testing::TempDir();
        auto tempFile = tempDir + "test_write_single_frame.pdb";

        traj->write(tempFile, 'w', "PDB");
        auto _traj_out = chemfiles::Trajectory(tempFile, 'w', "PDB");
        auto _frame_out = _traj_out.read();
        EXPECT_EQ(_traj_out.nsteps(), 1);
        EXPECT_EQ(_frame_out.size(), 7772);
        EXPECT_EQ(_frame_out.topology().bonds().size(), 6248);
        // TODO : angles
    }

}