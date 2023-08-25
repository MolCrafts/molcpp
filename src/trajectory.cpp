#include "trajectory.h"
#include <memory>

namespace molcpp
{
    Trajectory::Trajectory(std::string path, char mode = 'r', const std::string& format = "") : _chflTraj(path, mode, format)
    {

    }

    void Trajectory::add_frame(std::unique_ptr<Frame> frame)
    {
        size_t timestep = frame->get_timestep();
        _frames[timestep] = frame;
    }

    size_t Trajectory::get_nsteps() const
    {
        return _chflTraj.nsteps();
    }

    Frame* Trajectory::get_step(size_t step) 
    {
        auto _frame = _chflTraj.read_step(step);
        auto _frame_ptr = from_chemfiles(_frame);
        return _frame_ptr.get();
    }

    void Trajectory::write(std::string path, const std::string& format)
    {
        auto _traj = chemfiles::Trajectory(path, 'w', format);
        for (auto _frame : _frames)
        {
            auto chflFrame = to_chemfiles(_frame.second.get());
            _traj.write(chflFrame);
        }
    }

    bool Trajectory::is_open()
    {
        return _chflTraj.is_open();
    }

    void Trajectory::close()
    {
        _chflTraj.close();
    }

    std::unique_ptr<Trajectory> new_trajectory(std::string path, char mode = 'r', const std::string& format = "")
    {
        return std::make_unique<Trajectory>(path, mode, format);
    }

    chemfiles::Trajectory to_chemfiles(Trajectory* traj, std::string path, char mode, const std::string &format)
    {
        auto _traj = chemfiles::Trajectory(path, mode, format);
        auto _frames = traj->get_frames();
        for (auto _frame : _frames)
        {
            auto chflFrame = to_chemfiles(_frame);
            _traj.write(chflFrame);
        }
        return _traj;
    }

}