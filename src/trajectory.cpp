#include "trajectory.h"

namespace molcpp
{
    Trajectory::Trajectory()
    {
        _is_open = false;
    }

    explicit Trajectory::Trajectory(std::string, char, const std::string &)
    {
        _is_open = true;
        // _frames.reserve(traj.nsteps());
        // for (size_t i = 0; i < traj.nsteps(); ++i)
        // {
        //     auto frame = new_frame();
        //     frame->set_timestep(i);
        //     frame->set_topology(new_topology());
        //     traj.read(frame->get_timestep(), *frame);
        //     _frames.push_back(frame);
        // }
    }

    bool Trajectory::add_frame(const FramePtr& frame)
    {
        _frames.push_back(frame);
        return true;
    }

    size_t Trajectory::get_nsteps() const
    {
        return _frames.size();
    }

    FramePtr& Trajectory::get_step(size_t step) 
    {
        auto result = std::find_if(_frames.begin(), _frames.end(), [step](FramePtr frame)
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

    FramePtr& Trajectory::get_by_index(size_t index)
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

    const FrameVec& Trajectory::get_frames() const
    {
        return _frames;
    }

    // void Trajectory::open(std::string path, char mode, const std::string &format)
    // {
    //     if (_is_open)
    //     {
    //         throw IOError("Trajectory is already open");
    //     }
    //     else
    //     {
    //         _is_open = true;
    //     }
    // }

    // void Trajectory::write()
    // {

    // }

    TrajectoryPtr new_trajectory()
    {
        return std::make_shared<Trajectory>();
    }

}