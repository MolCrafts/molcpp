#include "frame.h"

namespace molcpp
{
    Frame::Frame() : _timestep(0), _topology(nullptr)
    {

    }

    // Frame(const chemfiles::Frame&)

    size_t Frame::get_natoms() const
    {
        return _topology->get_natoms();
    }

    size_t Frame::get_nbonds() const
    {
        return _topology->get_nbonds();
    }

    size_t Frame::get_timestep() const
    {
        return _timestep;
    }

    void Frame::set_timestep(size_t timestep)
    {
        _timestep = timestep;
    }

    const TopologyPtr& Frame::get_topology() const
    {
        return _topology;
    }

    void Frame::set_topology(TopologyPtr topology)
    {
        _topology = topology;
    }


}