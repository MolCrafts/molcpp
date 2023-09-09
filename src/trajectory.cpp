#include "trajectory.h"
#include "frame.h"
#include <chemfiles/Trajectory.hpp>
#include <cstddef>


namespace molcpp
{
Trajectory::Trajectory()
{
}

void Trajectory::add_frame(const Frame &frame)
{
    size_t timestep = frame.get_timestep();
    _frames[timestep] = frame;
}

std::vector<Frame> Trajectory::get_frames() const
{
    std::vector<Frame> frames(_frames.size());
    std::transform(_frames.begin(), _frames.end(), frames.begin(), [](auto& frame) {
        return frame.second;
    });
    return frames;
}

} // namespace molcpp