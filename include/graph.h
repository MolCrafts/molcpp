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
    using NodeVec = std::vector<std::shared_ptr<Node>>;
    using EdgeVec = std::vector<std::shared_ptr<Edge>>;
    using GraphVec = std::vector<std::shared_ptr<Graph>>;
    using ThreeBodyIndex = std::vector<std::array<size_t, 3>>;

    class Node
    {

        public:
            Node(): _parent{nullptr}, _edges{} {}
            int get_nedges() const { return _edges.size(); }
            void set_parent(std::shared_ptr<Graph> parent) { _parent = parent; }
            EdgeVec get_edges() const { return _edges; }
            bool add_edge(std::shared_ptr<Edge>);
            bool has_edge(std::shared_ptr<Edge>);
            void del_edge(std::shared_ptr<Edge>);
            void del_edge(Edge*);
            NodeVec get_neighbors();

        protected:
            std::shared_ptr<Graph> _parent;
            EdgeVec _edges;

    };


    class Edge
    {
        public:
            Edge(): _parent{nullptr}, _bgn{nullptr}, _end{nullptr} {}
            Edge(std::shared_ptr<Node> begin, std::shared_ptr<Node> end):_parent{nullptr}, _bgn{begin}, _end{end} {

            }
            ~Edge();
            std::shared_ptr<Node> get_bgn() const { return _bgn; }
            std::shared_ptr<Node> get_end() const { return _end; }
            void set_parent(std::shared_ptr<Graph> parent) { _parent = parent; }

        protected:
            std::shared_ptr<Graph> _parent;
            std::shared_ptr<Node> _bgn;
            std::shared_ptr<Node> _end;

    };


    class Graph
    {
        public:
            Graph(): _parent{nullptr}, _nodes{}, _edges{}, _subgraphs{} {};
            std::shared_ptr<Node> new_node();
            std::shared_ptr<Edge> new_edge(size_t, size_t);
            std::shared_ptr<Edge> new_edge(std::shared_ptr<Node>, std::shared_ptr<Node>);
            std::shared_ptr<Graph> new_subgraph();
            bool del_node(std::shared_ptr<Node>);
            bool del_node(size_t);
            bool del_edge(std::shared_ptr<Edge>);
            NodeVec get_nodes();
            EdgeVec get_edges();
            size_t get_nnodes();
            size_t get_nedges();
            size_t get_local_index(std::shared_ptr<Node> node);
            void set_parent(std::shared_ptr<Graph> parent) { _parent = parent; }

            ThreeBodyIndex find_three_bodies();

        protected:
            std::shared_ptr<Graph> _parent;
            NodeVec _nodes;
            EdgeVec _edges;
            GraphVec _subgraphs;

    };

}

#endif  // GRAPH_H