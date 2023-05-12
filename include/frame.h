#pragma once

#include <chemfiles.hpp>
#include <vector>
#include "xtensor/xarray.hpp"
#include "xtensor/xadapt.hpp"
#include "atom.h"
#include "topology.h"
#include "itemtype.h"

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
        void set_timestep(size_t);

        /**
         * @brief Get the topology object
         *
         * @return Topology&
         */
        const TopologyPtr &get_topology() const;

        /**
         * @brief Set the topology object
         *
         */
        void set_topology(const TopologyPtr &topology);

        /**
         * @brief Get a property by key
         *
         * @tparam T
         * @param key
         * @return T
         */
        template <typename T>
        xt::xarray<T> get(const std::string &key)
        {
            std::vector<T> _tmp;
            auto atoms = _topology->get_atoms();
            for(size_t i = 0; i < get_natoms(); i++)
            {
                _tmp.push_back(atoms[i]->get<T>(key));
            }
            return xt::adapt(_tmp);
        };

    private:
        size_t _timestep;
        TopologyPtr _topology;
    };

    using FramePtr = std::shared_ptr<Frame>;
    using FrameVec = std::vector<FramePtr>;

    FramePtr new_frame();
    FramePtr new_frame(const chemfiles::Frame &);

}
