#pragma once

#include <chemfiles.hpp>
#include <vector>
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
            return _topology->get<T>(key);
        };

        void set(const std::string&, const xt::xarray<AtomProperty>&);

        void set_positions(const xt::xarray<double>&);

        const xt::xarray<double> get_positions() const;

    private:
        size_t _timestep;
        TopologyPtr _topology;
    };

    using FramePtr = std::shared_ptr<Frame>;
    using FrameVec = std::vector<FramePtr>;

    FramePtr new_frame();
    FramePtr new_frame(const chemfiles::Frame &);

    chemfiles::Frame save_frame(const FramePtr &);

}
