#pragma once

#include <chemfiles.hpp>
#include <vector>
// #include "xtensor/xtensor.hpp"
// #include "xtensor/xarray.hpp"
// #include "xtensor/xadapt.hpp"
#include "atom.h"
#include "topology.h"

namespace molcpp
{
    class Frame
    {
        public:
            /**
             * @brief Construct an empty frame
             * 
             */
            Frame();

            /**
             * @brief Construct a new Frame from Chemfiles::Frame
             * 
             */
            Frame(const chemfiles::Frame&);
            size_t get_natoms() const;
            size_t get_nbonds() const;
            size_t get_timestep() const; 
            Topology& get_topology();

        private:
            size_t _timestep;
            Topology _topology;
    };

    using FramePtr = std::shared_ptr<Frame>;

}
