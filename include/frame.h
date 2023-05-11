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
            // Frame(const chemfiles::Frame&);
            
            /**
             * @brief Get the natoms object
             * 
             * @return size_t 
             */
            size_t get_natoms() const;

            /**
             * @brief Get the nbonds object
             * 
             * @return size_t 
             */
            size_t get_nbonds() const;

            /**
             * @brief Get the timestep object
             * 
             * @return size_t 
             */
            size_t get_timestep() const; 

            /**
             * @brief Set the timestep object
             * 
             */
            void set_timestep();

            /**
             * @brief Get the topology object
             * 
             * @return Topology& 
             */
            const TopologyPtr& get_topology() const;

            /**
             * @brief Set the topology object
             * 
             */
            void set_topology();

        private:
            size_t _timestep;
            TopologyPtr _topology;
    };

    using FramePtr = std::shared_ptr<Frame>;

}
