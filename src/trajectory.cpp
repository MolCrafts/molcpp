#include "trajectory.h"

namespace molcpp
{

    Trajectory::Trajectory(std::string path, char mode = 'r', const std::string& format = "") : _fileHandler(chemfiles::Trajectory(path, mode, format))
    {
    }

    Frame Trajectory::read()
    {
        chemfiles::Frame frame = _fileHandler.read();
        return Frame(frame);
    }

    Frame Trajectory::read_step(size_t step)
    {
        chemfiles::Frame frame = _fileHandler.read_step(step);
        return Frame(frame);
    }

    void Trajectory::close()
    {
        _fileHandler.close();
    }

    bool Trajectory::done()
    {
        return _fileHandler.done();
    }

}
