#pragma once
#include <vector>
#include <map>
#include <set>
#include "algo.h"
namespace molcpp
{
    class Graph
    {
    public:
        void add_node(int node)
        {
            _nodes.insert(node);
        }

        void add_edge(int from, int to)
        {
            _edges[from].insert(to);
            _edges[to].insert(from);
        }

        void del_edge(int from, int to)
        {
            _edges[from].erase(to);
            _edges[to].erase(from);
        }

        void del_node(int node)
        {
            _nodes.erase(node);
            _edges.erase(node);
            for (auto &[from, tos] : _edges)
            {
                tos.erase(node);
            }
        }

        std::set<int> get_nodes()
        {
            return _nodes;
        }

        std::map<int, std::set<int>> get_edges()
        {
            return _edges;
        }

        std::vector<int> get_edges_of(int node)
        {
            std::vector<int> edges_vec;
            for (auto &edge : _edges[node])
            {
                edges_vec.push_back(edge);
            }
            return edges_vec;
        }

        bool has_node(int node)
        {
            return _nodes.find(node) != _nodes.end();
        }

        bool has_edge(int from, int to)
        {
            return _edges[from].find(to) != _edges[from].end();
        }

        void add_subgraph(Graph &subgraph)
        {
            for (auto &node : subgraph.get_nodes())
            {
                add_node(node);
            }
            for (auto &[from, tos] : subgraph.get_edges())
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
            for (auto &[from, tos] : subgraph.get_edges())
            {
                for (auto &to : tos)
                {
                    del_edge(from, to);
                }
            }
        }

        std::vector<std::tuple<int, int>> get_bonds()
        {
            size_t nbonds = 0;
            for (auto &[from, tos] : _edges)
            {
                nbonds += tos.size();
            }
            std::vector<std::tuple<int, int>> bonds;
            bonds.reserve(nbonds);
            for (auto &[from, tos] : _edges)
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

        std::vector<std::tuple<int, int, int>> get_angles()
        {
            size_t nangles = 0;
            for (auto &[i, tos] : _edges)
            {
                nangles += C(tos.size(), 2);
            }
            std::vector<std::tuple<int, int, int>> angles;
            angles.reserve(nangles);
            for (const auto &[j, edge] : _edges)
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

        std::vector<std::tuple<int, int, int, int>> get_dihedrals()
        {
            std::vector<std::tuple<int, int, int, int>> dihedrals;
            for (auto &[j, edge] : _edges)
            {
                for (auto &k : edge)
                {
                    if (j > k)
                        continue;
                    for (auto &i : edge)
                    {
                        if (i == k) continue;
                        for (auto &l : _edges[k])
                        {
                            if (l == j) continue;
                            
                                dihedrals.push_back(std::make_tuple(i, j, k, l));
                            
                        }
                    }
                }
            }
            return dihedrals;
        }

    private:
        std::set<int> _nodes;
        std::map<int, std::set<int>> _edges;
    };
}