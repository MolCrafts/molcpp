#include "trajectory.h"

namespace molcpp
{
    Trajectory::Trajectory()
    {

    }

    bool Trajectory::add_frame(Frame* frame)
    {
        _frames.push_back(frame);
        return true;
    }

    size_t Trajectory::get_nsteps() const
    {
        return _frames.size();
    }

    Frame* Trajectory::get_step(size_t step) 
    {
        auto result = std::find_if(_frames.begin(), _frames.end(), [step](Frame* frame)
                                    { return frame->get_timestep() == step; });
        if (result == _frames.end())
        {
            throw KeyError("No such step");
        }
        else
        {
            return *result;
        }
    }

    Frame* Trajectory::get_by_index(size_t index)
    {
        if (index >= _frames.size())
        {
            throw IndexError("Index out of range");
        }
        else
        {
            return _frames[index];
        }
    }

    FrameVec Trajectory::get_frames() const
    {
        return _frames;
    }

    void Trajectory::load(std::string path, char mode, const std::string &format)
    {
        auto _traj = chemfiles::Trajectory(path, mode, format);
        auto _nsteps = _traj.nsteps();

        for (size_t i = 0; i < _nsteps; i++)
        {
            auto _frame = _traj.read();
            auto _frame_ptr = from_chemfiles(_frame);
            _frames.push_back(_frame_ptr.release());
        }

    }

    void Trajectory::write(std::string path, const std::string& format)
    {
        auto _traj = chemfiles::Trajectory(path, 'w', format);
        for (auto _frame : _frames)
        {
            auto chflFrame = to_chemfiles(_frame);
            _traj.write(chflFrame);
        }
    }

    std::unique_ptr<Trajectory> new_trajectory()
    {
        return std::make_unique<Trajectory>();
    }

    std::unique_ptr<Trajectory> new_trajectory(chemfiles::Trajectory& chflTraj)
    {
        auto _traj = new_trajectory();
        auto _nsteps = chflTraj.nsteps();

        for (size_t i = 0; i < _nsteps; i++)
        {
            auto _frame = chflTraj.read();
            auto _frame_ptr = from_chemfiles(_frame);
            _traj->add_frame(_frame_ptr.release());
        }

        return _traj;
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