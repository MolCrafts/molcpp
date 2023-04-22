#include "frame.h"

namespace molcpp
{

    Frame::Frame(size_t current_step, const Topology& topology): _current_step(current_step), _topology(topology)
    {
        std::vector<size_t> shape = {topology.get_natoms(), 3};
        _xyz = xt::zeros<double>(shape);
    }

    Frame::Frame(const chemfiles::Frame& chflFrame): _current_step(chflFrame.step()), _topology(chflFrame.topology())
    {

    }

}