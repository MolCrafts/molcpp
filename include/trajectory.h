#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <string>
#include "frame.h"
#include <chemfiles.hpp>

namespace molcpp
{

class Trajectory
{

    public:
        Trajectory() = delete;
        explicit Trajectory(std::string, char, const std::string& );

        Frame read();
        Frame read_step(size_t step);
        const std::string& path() const {
            return _fileHandler.path();
        }
        void close();
        bool done();

    private:
        chemfiles::Trajectory _fileHandler;

};


}

#endif  // TRAJECTORY_H