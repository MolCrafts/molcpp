#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <array>
#include <algo.h>
#include <memory>

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
        Node() : _parent{nullptr}, _edges{} {}
        int get_nedges() const { return _edges.size(); }
        void set_parent(GraphPtr parent) { _parent = parent; }
        EdgeVec get_edges() const { return _edges; }
        bool add_edge(EdgePtr);
        bool has_edge(EdgePtr);
        void del_edge(EdgePtr);
        void del_edge(Edge *);
        NodeVec get_neighbors();

    protected:
        GraphPtr _parent;
        EdgeVec _edges;
    };

    class Edge
    {
    public:
        Edge() : _parent{nullptr}, _bgn{nullptr}, _end{nullptr} {}
        Edge(NodePtr begin, NodePtr end) : _parent{nullptr}, _bgn{begin}, _end{end}
        {
        }
        ~Edge();
        NodePtr get_bgn() const { return _bgn; }
        NodePtr get_end() const { return _end; }
        void set_parent(GraphPtr parent) { _parent = parent; }

    protected:
        GraphPtr _parent;
        NodePtr _bgn;
        NodePtr _end;
    };

    class Graph
    {
    public:
        Graph() : _parent{nullptr}, _nodes{}, _edges{}, _subgraphs{} {};
        void add_node(NodePtr node) { _nodes.push_back(node); };
        void add_edge(EdgePtr edge) { _edges.push_back(edge); };
        void add_subgraph(GraphPtr graph) { _subgraphs.push_back(graph); };
        NodePtr new_node();
        EdgePtr new_edge(size_t, size_t);
        bool add_node(size_t);
        EdgePtr new_edge(NodePtr, NodePtr);
        GraphPtr new_subgraph();

        bool del_node(NodePtr);
        bool del_node(size_t);
        bool del_edge(EdgePtr);
        NodeVec get_nodes();
        EdgeVec get_edges();
        size_t get_nnodes();
        size_t get_nedges();
        size_t get_local_index(NodePtr node);
        void set_parent(GraphPtr parent) { _parent = parent; }

        ThreeBodyIndex find_three_bodies();

    protected:
        GraphPtr _parent;
        NodeVec _nodes;
        EdgeVec _edges;
        GraphVec _subgraphs;
    };

}

#endif // GRAPH_H