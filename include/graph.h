#pragma once

#include <vector>
#include <array>
#include "algo.h"
#include <memory>
#include "utils.h"
#include "mplog.h"

namespace MolCpp
{

    class Graph;
    class Edge;
    class Node;
    using NodePtr = std::shared_ptr<Node>;
    using EdgePtr = std::shared_ptr<Edge>;
    using GraphPtr = std::shared_ptr<Graph>;
    using NodeVec = std::vector<NodePtr>;
    using EdgeVec = std::vector<EdgePtr>;
    using GraphVec = std::vector<GraphPtr>;
    using ThreeBodyIndex = std::vector<std::array<size_t, 3>>;

    class Node
    {

    public:

        Node() : _edges{} {}
        EdgeVec get_edges() const { return _edges; }
        int get_nedges() const { return _edges.size(); }

        bool add_edge(EdgePtr);
        bool has_edge(EdgePtr);
        bool del_edge(EdgePtr);
        NodeVec get_neighbors();

    protected:

    private:
        EdgeVec _edges;

    };

    class Edge
    {
    public:
        Edge() : _bgn{nullptr}, _end{nullptr} {}
        Edge(NodePtr begin, NodePtr end) : _bgn{begin}, _end{end} {}

        NodePtr get_bgn() const { return _bgn; }
        NodePtr get_end() const { return _end; }
        void set_bgn(NodePtr bgn) { _bgn = bgn; }
        void set_end(NodePtr end) { _end = end; }

    protected:

    private:
        NodePtr _bgn;
        NodePtr _end;
    };

    class Graph
    {
    public:

        Graph() : _nodes{}, _edges{}, _subgraphs{} {};

        bool add_node(NodePtr node);
        bool add_edge(EdgePtr edge);
        bool add_subgraph(GraphPtr graph);

        NodePtr new_node();
        EdgePtr new_edge(size_t, size_t);
        EdgePtr new_edge(NodePtr, NodePtr);
        GraphPtr new_subgraph();

        bool has_node(NodePtr);
        bool has_edge(EdgePtr);
        bool has_subgraph(GraphPtr);

        bool del_node(NodePtr);
        bool del_node(size_t);
        bool del_edge(EdgePtr);

        NodeVec get_nodes();
        EdgeVec get_edges();
        GraphVec get_subgraphs();

        size_t get_nnodes();
        size_t get_nedges();
        size_t get_nsubgraphs();

        size_t get_local_index(NodePtr node);

        ThreeBodyIndex find_three_bodies();

    private:
        NodeVec _nodes;
        EdgeVec _edges;
        GraphVec _subgraphs;

    };

}
