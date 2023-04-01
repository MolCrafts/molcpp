#include "chemfiles.hpp"
#include <vector>
#include <iostream>

namespace molcpp
{

    void read(const std::string& filename)
    {

        chemfiles::Trajectory file(filename);
        chemfiles::Frame frame = file.read();
        std::cout << "Read " << frame.size() << " atoms" << std::endl;

    }

}