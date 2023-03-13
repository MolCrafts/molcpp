#include "utils.h"
#include "graph.h"

TEST(TestGraph, test_init)
{

    MolCpp::Graph graph;
    auto n1 = graph.new_node();
    auto n2 = graph.new_node();
    auto n3 = graph.new_node();
    graph.new_edge(0, 1);
    graph.new_edge(1, 2);
    graph.new_edge(2, 0);

    EXPECT_EQ(graph.get_nnodes(), 3);
    EXPECT_EQ(graph.get_nedges(), 3);

    EXPECT_EQ(n1->get_neighbors().size(), 2);
    EXPECT_EQ(n2->get_neighbors().size(), 2);
    EXPECT_EQ(n3->get_neighbors().size(), 2);

    auto t = graph.find_three_bodies();
    EXPECT_EQ(t.size(), 3);
}

TEST(TestEdge, test_delete_Edge)
{

    auto graph = new MolCpp::Graph();
    auto n1 = graph->new_node();
    auto n2 = graph->new_node();
    auto e1 = graph->new_edge(n1, n2);

    EXPECT_EQ(n1->get_nedges(), 1);
    EXPECT_EQ(n2->get_nedges(), 1);

    graph->del_edge(e1);

    EXPECT_EQ(n1->get_nedges(), 0);
    EXPECT_EQ(n2->get_nedges(), 0);

    delete graph;

}

TEST(TestGraph, test_subgraph_reduce)
{
    auto graph = new MolCpp::Graph();

    auto subgraph = graph->new_subgraph();
    subgraph->new_node();
    subgraph->new_node();
    subgraph->new_node();
    subgraph->new_edge(0, 1);
    subgraph->new_edge(1, 2);
    subgraph->new_edge(2, 0);

    EXPECT_EQ(graph->get_nnodes(), 3);
    EXPECT_EQ(graph->get_nedges(), 3);

}

TEST(TestGraph, test_subgraph_linkage)
{

    auto graph = new MolCpp::Graph();
    auto subgraph = graph->new_subgraph();

    auto n1 = subgraph->new_node();
    auto n2 = subgraph->new_node();
    auto n3 = subgraph->new_node();
    subgraph->new_edge(n1, n2);
    subgraph->new_edge(n2, n3);
    subgraph->new_edge(n3, n1);

    auto n4 = graph->new_node();
    graph->new_edge(n4, n1);

    EXPECT_EQ(graph->get_nnodes(), 4);
    EXPECT_EQ(graph->get_nedges(), 4);
    EXPECT_EQ(n1->get_neighbors().size(), 3);
    EXPECT_EQ(graph->find_three_bodies().size(), 5);
}