#pragma once

#include <tuple>
#include <vector>

#include <igraph.h>

#include "molcpp/export.hpp"
#include "molcpp/types.hpp"

namespace molcpp
{

using id_t = size_t;
using idx_t = size_t;

class MOLCPP_EXPORT Topology
{
  public:
    class Bond
    {
      public:
        Bond(idx_t i, idx_t j, id_t id) : i(std::min(i, j)), j(std::max(i, j)), id(id)
        {
        }
        bool operator==(const Topology::Bond &rhs)
        {
            return std::tie(rhs.i, rhs.j) == std::tie(i, j) || std::tie(rhs.i, rhs.j) == std::tie(j, i);
        }

        idx_t i;
        idx_t j;
        id_t id;
    };

    class Angle
    {
      public:
        Angle(idx_t i, idx_t j, idx_t k, id_t id) : i(std::min(i, k)), j(j), k(std::max(i, k)), id(id)
        {
        }

        idx_t i;
        idx_t j;
        idx_t k;
        id_t id;

        bool operator==(const Topology::Angle &rhs)
        {
            return std::tie(rhs.i, rhs.j, rhs.k) == std::tie(i, j, k) ||
                   std::tie(rhs.i, rhs.j, rhs.k) == std::tie(k, j, i);
        }
    };

    Topology();

    ~Topology();

    void add_bond(idx_t, idx_t, id_t);
    void add_angle(idx_t, idx_t, idx_t, id_t);

    void concrete();

    size_t get_n_bonds() const
    {
        return _bonds.size();
    }

    size_t get_n_angles() const
    {
        return _angles.size();
    }

    const std::vector<Bond> &get_bonds() const
    {
        return _bonds;
    }

    const std::vector<Angle> &get_angles() const
    {
        return _angles;
    }

    void del_bond(idx_t i, idx_t j)
    {
        auto bond_to_be_delete = Bond(i, j, 0);
        _bonds.erase(std::remove_if(_bonds.begin(), _bonds.end(),
                                    [bond_to_be_delete](Bond &b) { return b == bond_to_be_delete; }), _bonds.end());
    }

    void del_bond(id_t id)
    {
        _bonds.erase(std::remove_if(_bonds.begin(), _bonds.end(), [id](Bond &b) { return b.id == id; }), _bonds.end());
    }

    void del_angle(idx_t i, idx_t j, idx_t k)
    {
        auto angle_to_be_delete = Angle(i, j, k, 0);
        _angles.erase(std::remove_if(_angles.begin(), _angles.end(),
                                     [angle_to_be_delete](Angle &a) { return a == angle_to_be_delete; }));
    }

    void del_angle(id_t id)
    {
        _angles.erase(std::remove_if(_angles.begin(), _angles.end(), [id](Angle &a) { return a.id == id; }));
    }

  private:
    std::vector<Bond> _bonds;
    std::vector<Angle> _angles;
    igraph_t _graph;
};

} // namespace molcpp