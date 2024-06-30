#include "molcpp/topology.hpp"

namespace molcpp
{   

    Topology::Topology()
    {
    }

    Topology::~Topology()
    {
        igraph_destroy(&_graph);
    }

    void Topology::add_bond(idx_t i, idx_t j, id_t id)
    {
        _bonds.push_back(Bond{i, j, id});
    }

    void Topology::add_angle(idx_t i, idx_t j, idx_t k, id_t id)
    {
        _angles.push_back(Angle{i, j, k, id});
    }

    void Topology::concrete()
    {
        igraph_vector_int_t edges;
        igraph_vector_int_init(&edges, _bonds.size() * 2);
        for (size_t i = 0; i < _bonds.size(); ++i)
        {
            VECTOR(edges)[2 * i] = _bonds[i].i;
            VECTOR(edges)[2 * i + 1] = _bonds[i].j;
        }
        igraph_create(&_graph, &edges, 0, IGRAPH_UNDIRECTED);
        igraph_simplify(&_graph, true, true, NULL);

    }

} // namespace molcpp