#include "trajectory.h"

namespace molcpp
{
    Trajectory::Trajectory(std::string path, char mode, const std::string& format) : _chflTraj(path, mode, format)
    {

    }

    void Trajectory::add_frame(const Frame& frame)
    {
        size_t timestep = frame.get_timestep();
        _frames[timestep] = frame;
    }

    size_t Trajectory::get_nsteps() const
    {
        return _chflTraj.nsteps();
    }

    Frame& Trajectory::get_step(size_t step) 
    {
        chemfiles::Frame _frame = _chflTraj.read_step(step);
        size_t timestep = _frame.step();
        _frames[timestep] = from_chemfiles(_frame);
        return _frames[timestep];
    }

    void Trajectory::write(std::string path, const std::string& format)
    {
        chemfiles::Trajectory _traj = chemfiles::Trajectory(path, 'w', format);
        // for (auto& frame : _frames)
        // {
        //     _traj.write(to_chemfiles(frame.second));
        // }
    }

    void Trajectory::close()
    {
        _chflTraj.close();
    }

}