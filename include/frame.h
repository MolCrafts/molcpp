#pragma once

#include <cstddef>
#include <vector>
#include "atom.h"
#include "topology.h"
#include "itemtype.h"
#include "box.h"
#include "algo.h"
#include "dict.h"
namespace molcpp
{

    class Frame
    {
    public:
        /**
         * @brief Construct an empty frame
         *
         */
        Frame(size_t timestep = 0);

        Frame(const chemfiles::Frame&);

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
        Topology* get_topology() const;

        /**
         * @brief Set the topology object
         *
         */
        void set_topology(Topology* topology);

        /**
         * @brief Get a property by key
         *
         * @tparam T
         * @param key
         * @return T
         */
        template <typename T>
        std::vector<T> get(const std::string &key)
        {
            return _topology->get<T>(key);
        };

        void set(const std::string&, const std::vector<AtomProperty>&);

        void set_cell(Cell*);

        void set_cell(Vector3D lengths, Vector3D titles = {0, 0, 0});

        Cell* get_cell() const;

    private:
        size_t _timestep;
        Box* _box;
        Topology* _topology;
    };

    std::unique_ptr<Frame> create_frame();
    std::unique_ptr<Frame> from_chemfiles(const chemfiles::Frame &);

    chemfiles::Frame to_chemfiles(Frame*);

}
