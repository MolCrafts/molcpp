#include "utils.h"
#include "graph.h"

namespace MolCpp
{
    TEST(TestNode, test_init)
    {
        Node node;
        EXPECT_EQ(node.get_nedges(), 0);
    }

    TEST(TestNode, test_crud_edge)
    {
        NodePtr node = std::make_shared<Node>();
        NodePtr node1 = std::make_shared<Node>();
        EdgePtr edge = std::make_shared<Edge>(node, node1);
        node->add_edge(edge);
        EXPECT_EQ(node->get_nedges(), 1);
        EXPECT_TRUE(node->has_edge(edge));

        node->del_edge(edge);
        EXPECT_EQ(node->get_nedges(), 0);
        EXPECT_FALSE(node->has_edge(edge));
    }

    TEST(TestNode, test_get_neighbors)
    {
        NodePtr node = std::make_shared<Node>();
        NodePtr node1 = std::make_shared<Node>();
        NodePtr node2 = std::make_shared<Node>();
        NodePtr node3 = std::make_shared<Node>();
        EdgePtr edge1 = std::make_shared<Edge>(node1, node);
        EdgePtr edge2 = std::make_shared<Edge>(node2, node);
        EdgePtr edge3 = std::make_shared<Edge>(node3, node);
        node->add_edge(edge1);
        node->add_edge(edge2);
        node->add_edge(edge3);
        NodeVec nbrs = node->get_neighbors();
        EXPECT_EQ(nbrs.size(), 3);
    }

    TEST(TestEdge, test_init)
    {
        Edge edge;
        EXPECT_EQ(edge.get_bgn(), nullptr);
        EXPECT_EQ(edge.get_end(), nullptr);
    }

    TEST(TestEdge, test_crud_bgn)
    {
        Edge edge;
        NodePtr node = std::make_shared<Node>();
        edge.set_bgn(node);
        EXPECT_EQ(edge.get_bgn(), node);
    }

    TEST(TestGraph, test_init)
    {
        Graph graph;
        EXPECT_EQ(graph.get_nnodes(), 0);
        EXPECT_EQ(graph.get_nedges(), 0);
    }

    TEST(TestGraph, test_crud_node)
    {
        Graph graph;
        NodePtr node = std::make_shared<Node>();
        graph.add_node(node);
        EXPECT_EQ(graph.get_nnodes(), 1);
        EXPECT_TRUE(graph.has_node(node));

        graph.del_node(node);
        EXPECT_EQ(graph.get_nnodes(), 0);
        EXPECT_FALSE(graph.has_node(node));

    }

    TEST(TestGraph, test_crud_edge)
    {
        Graph graph;
        NodePtr node1 = std::make_shared<Node>();
        NodePtr node2 = std::make_shared<Node>();
        EdgePtr edge = std::make_shared<Edge>(node1, node2);
        EXPECT_TRUE(graph.add_edge(edge));
        EXPECT_EQ(graph.get_nedges(), 1);
        EXPECT_TRUE(graph.has_edge(edge));

        EXPECT_TRUE(graph.del_edge(edge));
        EXPECT_EQ(graph.get_nedges(), 0);
        EXPECT_FALSE(graph.has_edge(edge));
    }

}