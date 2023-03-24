#include "graph.h"

namespace MolCpp
{

    bool Node::add_edge(EdgePtr edge)
    {
        if (has_edge(edge))
        {
            return false;
        }
        else
        {
            _edges.push_back(edge);
            return true;
        }
    }

    bool Node::has_edge(EdgePtr edge)
    {
        for (const auto e : _edges)
        {
            if (e == edge)
            {
                return true;
            }
        }
        return false;
    }

    bool Node::del_edge(EdgePtr edge)
    {
        for (auto it = _edges.begin(); it != _edges.end(); ++it)
        {
            if (*it == edge)
            {
                _edges.erase(it);
                return true;
            }
        }
        return false;
    }

    NodeVec Node::get_neighbors()
    {
        NodeVec _nbrs;
        for (const auto edge : _edges)
        {
            if (edge->get_bgn().get() == this)
            {
                _nbrs.push_back(edge->get_end());
            }
            else if (edge->get_end().get() == this)
            {
                _nbrs.push_back(edge->get_bgn());
            }
        }
        return _nbrs;
    }

    bool Graph::add_node(NodePtr node)
    {
        if(has_node(node))
        {
            return false;
        }
        else
        {
            _nodes.push_back(node);
            return true;
        }

    }

    bool Graph::add_edge(EdgePtr edge)
    {
        if (has_node(edge->get_bgn()) == false) add_node(edge->get_bgn());
        if (has_node(edge->get_end()) == false) add_node(edge->get_end());
        if (has_edge(edge))
        {
            _edges.push_back(edge);
            return true;
        }
        return false;
    }

    bool Graph::add_subgraph(GraphPtr graph)
    {
        if (has_subgraph(graph))
        {
            return false;
        }
        else
        {
            _subgraphs.push_back(graph);
            return true;
        }
    }

    NodePtr Graph::new_node()
    {
        auto node = std::make_shared<Node>();
        _nodes.push_back(node);
        return node;
    }

    EdgePtr Graph::new_edge(size_t bgn_idx, size_t end_idx)
    {
        auto bgn = _nodes.at(bgn_idx);
        auto end = _nodes.at(end_idx);
        return this->new_edge(bgn, end);
    }

    EdgePtr Graph::new_edge(NodePtr bgn, NodePtr end)
    {
        if (bgn == nullptr || end == nullptr)
        {
            LOG_ERROR("Cannot create edge with null node");
        }

        if (bgn == end)
        {
            LOG_ERROR("Cannot create edge with same node");
        }

        if (has_node(bgn) == false) add_node(bgn);
        if (has_node(end) == false) add_node(end);
        auto new_edge = std::make_shared<Edge>(bgn, end);
        bgn->add_edge(new_edge);
        end->add_edge(new_edge);
        _edges.push_back(new_edge);
        return new_edge;
    }

    GraphPtr Graph::new_subgraph()
    {
        auto graph = std::make_shared<Graph>();
        _subgraphs.push_back(graph);
        return graph;
    }

    bool Graph::has_node(NodePtr node)
    {
        for (const auto n : _nodes)
        {
            if (n == node)
            {
                return true;
            }
        }
        return false;
    }

    bool Graph::has_edge(EdgePtr edge)
    {
        for (const auto e : _edges)
        {
            if (e == edge)
            {
                return true;
            }
        }
        return false;
    }

    bool Graph::has_subgraph(GraphPtr graph)
    {
        for (const auto g : _subgraphs)
        {
            if (g == graph)
            {
                return true;
            }
        }
        return false;
    }

    bool Graph::del_node(size_t idx)
    {
        return del_node(_nodes.at(idx));
    }

    bool Graph::del_node(NodePtr node)
    {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            if (*it == node)
            {
                auto nbrs = node->get_neighbors();
                for (const auto nbr : nbrs)
                {
                    for (const auto edge : nbr->get_edges())
                    {
                        if (edge->get_bgn() == node || edge->get_end() == node)
                        {
                            del_edge(edge);
                        }
                    }
                }
                _nodes.erase(it);
                return true;
            }
        }
        return false;
    }

    bool Graph::del_edge(EdgePtr edge)
    {
        edge->get_bgn()->del_edge(edge);
        edge->get_end()->del_edge(edge);
        for (auto it = _edges.begin(); it != _edges.end(); ++it)
        {
            if (*it == edge)
            {
                _edges.erase(it);
                return true;
            }
        }
        return false;
    }

    NodeVec Graph::get_nodes()
    {
        NodeVec nodes = _nodes;
        for (auto subgraph : _subgraphs)
        {
            NodeVec subnodes = subgraph->get_nodes();
            nodes.insert(nodes.end(), subnodes.begin(), subnodes.end());
        }
        return nodes;
    }

    EdgeVec Graph::get_edges()
    {
        EdgeVec edges = _edges;
        for (auto subgraph : _subgraphs)
        {
            EdgeVec subedges = subgraph->get_edges();
            edges.insert(edges.end(), subedges.begin(), subedges.end());
        }
        return edges;
    }

    GraphVec Graph::get_subgraphs()
    {
        GraphVec subgraphs = _subgraphs;
        for (auto subgraph : _subgraphs)
        {
            GraphVec subsubgraphs = subgraph->get_subgraphs();
            subgraphs.insert(subgraphs.end(), subsubgraphs.begin(), subsubgraphs.end());
        }
        return subgraphs;
    }

    size_t Graph::get_nnodes()
    {

        size_t nnodes = _nodes.size();
        for (auto subgraph : _subgraphs)
        {
            nnodes += subgraph->get_nnodes();
        }
        return nnodes;
    }

    size_t Graph::get_nedges()
    {
        size_t nedges = _edges.size();
        for (auto subgraph : _subgraphs)
        {
            nedges += subgraph->get_nedges();
        }
        return nedges;
    }

    size_t Graph::get_nsubgraphs()
    {
        size_t nsubgraphs = _subgraphs.size();
        for (auto subgraph : _subgraphs)
        {
            nsubgraphs += subgraph->get_nsubgraphs();
        }
        return nsubgraphs;
    }

    size_t Graph::get_local_index(NodePtr node)
    {
        auto ans = find_in_container(get_nodes(), node);
        if (ans.has_value())
        {
            return ans.value();
        }
        else
        {
            throw std::runtime_error("Node not found in graph");
        }
    }

    ThreeBodyIndex Graph::find_three_bodies()
    {
        ThreeBodyIndex three_bodies;
        std::vector<size_t> nbr_indices;
        std::array<size_t, 3> three_body;

        auto nodes = get_nodes();

        for (auto node : get_nodes())
        {
            if (node->get_nedges() > 1)
            {
                three_body[1] = get_local_index(node);

                for (auto nbr : node->get_neighbors())
                {
                    nbr_indices.push_back(get_local_index(nbr));
                }

                auto combinations = combination(nbr_indices, 2);
                for (size_t i = 0; i < combinations.size(); i += 2)
                {
                    three_body[0] = combinations[i];
                    three_body[2] = combinations[i + 1];
                    three_bodies.push_back(three_body);
                }
            }
            nbr_indices.clear();
        }

        return three_bodies;
    }

}