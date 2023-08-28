#pragma once

#include <vector>

#include <chemfiles.hpp>

#include "algo.h"
#include "box.h"
#include "config.h"
#include "connectivity.h"
#include "dict.h"
#include "graph.h"

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

    /** TODO:
     * @brief Get the topology object
     *
     * @return Topology&
     */
    // Topology* get_topology() const;

    /** TODO:
     * @brief Set the topology object
     *
     */
    // void set_topology(Topology* topology);

    template <typename T> void set(const std::string &key, const std::vector<std::optional<T>> &values = {})
    {
        _atom_properties[key] = values;
    }

    template<typename T> void set(const std::string& key, const std::vector<T>& values = {})
    {
        _atom_properties[key] = values;
    }

    template<typename T> T get(const std::string& key)
    {
        return _atom_properties.get<T>(key);
    }

    void add_bond(size_t i, size_t j, BondOrder order);

    // void add_angle(size_t i, size_t j, size_t k);

    // void add_dihedral(size_t i, size_t j, size_t k, size_t l);

    // void add_improper(size_t i, size_t j, size_t k, size_t l);

  private:
    size_t _timestep;
    Box *_box;
    Dict _atom_properties;
    Connectivity _connectivity;
};

Frame from_chemfiles(const chemfiles::Frame &);
// chemfiles::Frame to_chemfiles(const Frame &);

} // namespace molcpp
