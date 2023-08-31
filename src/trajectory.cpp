#include "trajectory.h"

namespace molcpp
{
Trajectory::Trajectory(std::string path, char mode, const std::string &format) : _chflTraj(path, mode, format)
{
}

void Trajectory::add_frame(const Frame &frame)
{
    size_t timestep = frame.get_timestep();
    _frames[timestep] = frame;
}

size_t Trajectory::get_nsteps() const
{
    return _chflTraj.nsteps();
}

Frame &Trajectory::read_step(size_t step)
{
    chemfiles::Frame _frame = _chflTraj.read_step(step);
    size_t timestep = _frame.step();
    _frames[timestep] = from_chemfiles(_frame);
    return _frames[timestep];
}

void Trajectory::write(std::string path, const std::string &format)
{
    chemfiles::Trajectory _traj = chemfiles::Trajectory(path, 'w', format);
    std::vector<size_t> steps;
    steps.reserve(_frames.size());

    std::transform(_frames.begin(), _frames.end(), std::back_inserter(steps),
                   [](const auto &frame) { return frame.first; });
    std::sort(steps.begin(), steps.end());
    for (auto step : steps)
    {
        _traj.write(to_chemfiles(_frames[step]));
    }
}

void Trajectory::close()
{
    _chflTraj.close();
}

} // namespace molcpp