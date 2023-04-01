#include "trajectory.h"

namespace molcpp
{

    explicit Trajectory::Trajectory(std::string path, char mode = 'r', const std::string& format = "xyz") : _fileHandler(chemfiles::Trajectory(path, mode, format))
    {
    }

    Frame read()
    {
        chemfiles::Frame frame = _fileHandler.read();
        return Frame(frame);
    }

    Frame read_step(size_t step)
    {
        chemfiles::Frame frame = _fileHandler.read_step(step);
        return Frame(frame);
    }

    void close()
    {
        _fileHandler.close();
    }

    bool done()
    {
        return _fileHandler.done();
    }

}
