#pragma once
#include "algo.h"
#include "error.h"
#include <map>
#include <set>
#include <vector>

namespace molcpp
{


class Graph
{

    using BondIdx = std::tuple<size_t, size_t>;
    using AngleIdx = std::tuple<size_t, size_t, size_t>;
    using DihedralIdx = std::tuple<size_t, size_t, size_t, size_t>;

    using BondConnects = std::vector<BondIdx>;
    using AngleConnects = std::vector<AngleIdx>;
    using DihedralConnects = std::vector<DihedralIdx>;
    using index = size_t;

  public:
    void add_node(index node)
    {
        _adj[node] = std::set<index>();
    }

    void add_edge(index from, index to)
    {
        _adj[from].insert(to);
        _adj[to].insert(from);
    }

    void del_edge(index from, index to)
    {
        _adj[from].erase(to);
        _adj[to].erase(from);
    }

    void del_node(index node)
    {
        for (auto &nbrs : _adj[node])
        {
            _adj[nbrs].erase(node);
        }
        _adj.erase(node);
    }

    std::vector<index> get_nodes()
    {
        std::vector<index> nodes(_adj.size());
        for (auto &[node, _] : _adj)
        {
            nodes.push_back(node);
        }
        return nodes;
    }

    std::map<index, std::set<index>> get_adj()
    {
        return _adj;
    }

    std::set<index> &get_adj_of(index node)
    {
        return _adj[node];
    }

    bool has_node(index node)
    {
        return _adj.find(node) != _adj.end();
    }

    bool has_edge(index from, index to)
    {
        bool a_side = _adj[from].find(to) != _adj[from].end();
        bool b_side = _adj[to].find(from) != _adj[to].end();
        if (a_side && b_side)
        {
            return true;
        }
        else
        {
            throw InternalError("Graph is not bi-directional for edge " + std::to_string(from) + " " +
                                std::to_string(to));
        }
    }

    void add_subgraph(Graph &subgraph)
    {
        for (auto &node : subgraph.get_nodes())
        {
            add_node(node);
        }
        for (auto &[from, tos] : subgraph.get_adj())
        {
            for (auto &to : tos)
            {
                add_edge(from, to);
            }
        }
    }

    void del_subgraph(Graph &subgraph)
    {
        for (auto &node : subgraph.get_nodes())
        {
            del_node(node);
        }
        for (auto &[from, tos] : subgraph.get_adj())
        {
            for (auto &to : tos)
            {
                del_edge(from, to);
            }
        }
    }

    BondConnects get_bonds()
    {
        size_t nbonds = 0;
        for (auto &[from, tos] : _adj)
        {
            nbonds += tos.size();
        }
        BondConnects bonds;
        bonds.reserve(nbonds);
        for (auto &[from, tos] : _adj)
        {
            for (auto &to : tos)
            {
                if (from < to)
                {
                    bonds.push_back(std::make_tuple(from, to));
                }
            }
        }
        return bonds;
    }

    AngleConnects get_angles()
    {
        size_t nangles = 0;
        for (auto &[i, tos] : _adj)
        {
            nangles += C(tos.size(), 2);
        }
        AngleConnects angles;
        angles.reserve(nangles);
        for (auto &[j, edge] : _adj)
        {
            for (auto &i : edge)
            {
                for (auto &k : edge)
                {
                    if (i < k)
                    {
                        angles.push_back(std::make_tuple(i, j, k));
                    }
                }
            }
        }
        return angles;
    }

    DihedralConnects get_dihedrals()
    {
        DihedralConnects dihedrals;
        for (auto &[j, edge] : _adj)
        {
            for (auto &k : edge)
            {
                if (j > k)
                    continue;
                for (auto &i : edge)
                {
                    if (i == k)
                        continue;
                    for (auto &l : _adj[k])
                    {
                        if (l == j)
                            continue;

                        dihedrals.push_back(std::make_tuple(i, j, k, l));
                    }
                }
            }
        }
        return dihedrals;
    }

  private:
    std::map<index, std::set<index>> _adj;
};
} // namespace molcpp