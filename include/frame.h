#ifndef FRAME_H
#define FRAME_H

#include <chemfiles.hpp>
#include <vector>
#include "xtensor/xtensor.hpp"
#include "xtensor/xarray.hpp"
#include "xtensor/xadapt.hpp"
#include "atom.h"
#include "topology.h"

namespace molcpp
{
    class Frame
    {
        public:
            Frame() = delete;
            Frame(const chemfiles::Frame&);
            size_t get_natoms() const { return _topology.get_natoms(); }
            size_t get_nbonds() const { return _topology.get_nbonds(); }
            size_t get_current_step() const { return _current_step; }
            xt::xarray<double> get_xyz() const { return _xyz; }
            Topology get_topology() const { return _topology; }

        private:
            // Cell
            size_t _current_step;
            Topology _topology;
            xt::xarray<double> _xyz;

    };

}

#endif // FRAME_H