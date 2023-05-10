#include "trajectory.h"

namespace molcpp
{

    Trajectory::Trajectory(std::string path, char mode = 'r', const std::string& format = "") : _fileHandler(chemfiles::Trajectory(path, mode, format))
    {
    }

    // Frame Trajectory::read()
    // {
    //     chemfiles::Frame frame = _fileHandler.read();
    //     return Frame(frame);
    // }

    // Frame Trajectory::read_step(size_t step)
    // {
    //     chemfiles::Frame frame = _fileHandler.read_step(step);
    //     return Frame(frame);
    // }

    const std::string& Trajectory::path() const
    {
        return _fileHandler.path();
    }

    void Trajectory::close()
    {
        _fileHandler.close();
    }

    bool Trajectory::done() const
    {
        return _fileHandler.done();
    }

    size_t Trajectory::get_nsteps() const 
    {
        return _fileHandler.nsteps();
    }

}
