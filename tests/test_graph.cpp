#include "utils.h"
#include "graph.h"
namespace molcpp
{
    TEST(TestGraph, test_constructor)
    {
        auto g = Graph();
    }

    TEST(TestGraph, test_add_node)
    {
        auto g = Graph();
        g.add_node(0);
        EXPECT_TRUE(g.has_node(0));
        EXPECT_FALSE(g.has_node(1));
    }

    TEST(TestGraph, test_has_node)
    {
        auto g = Graph();
        g.add_node(0);
        EXPECT_TRUE(g.has_node(0));
        EXPECT_FALSE(g.has_node(1));
    }

    TEST(TestGraph, test_del_node)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.del_node(1);
        EXPECT_TRUE(g.has_node(0));
        EXPECT_FALSE(g.has_node(1));
        EXPECT_TRUE(g.has_node(2));
    }

    TEST(TestGraph, test_add_edge)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(0, 1);
        EXPECT_TRUE(g.has_edge(0, 1));
        EXPECT_TRUE(g.has_edge(1, 0));
        EXPECT_FALSE(g.has_edge(0, 2));
        EXPECT_FALSE(g.has_edge(1, 2));
    }

    TEST(TestGraph, test_has_edge)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(0, 1);
        EXPECT_TRUE(g.has_edge(0, 1));
        EXPECT_TRUE(g.has_edge(1, 0));
        EXPECT_FALSE(g.has_edge(0, 2));
        EXPECT_FALSE(g.has_edge(1, 2));
    }

    TEST(TestGraph, test_del_edge)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        g.del_edge(0, 1);
        EXPECT_FALSE(g.has_edge(0, 1));
        EXPECT_TRUE(g.has_edge(0, 2));
        g.del_edge(0, 2);
        EXPECT_FALSE(g.has_edge(0, 2));
    }

    TEST(TestGraph, test_get_bonds)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        g.add_edge(1, 2);
        auto bonds = g.get_bonds();
        EXPECT_EQ(bonds.size(), 3);
        EXPECT_TRUE(std::find(bonds.begin(), bonds.end(), std::make_tuple(0, 1)) != bonds.end());
        EXPECT_TRUE(std::find(bonds.begin(), bonds.end(), std::make_tuple(0, 2)) != bonds.end());
        EXPECT_TRUE(std::find(bonds.begin(), bonds.end(), std::make_tuple(1, 2)) != bonds.end());
    }

    TEST(TestGraph, test_get_angles)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        g.add_edge(1, 2);
        auto angles = g.get_angles();
        EXPECT_EQ(angles.size(), 3);
        EXPECT_TRUE(std::find(angles.begin(), angles.end(), std::make_tuple(1, 0, 2)) != angles.end());
        EXPECT_TRUE(std::find(angles.begin(), angles.end(), std::make_tuple(0, 1, 2)) != angles.end());
        EXPECT_TRUE(std::find(angles.begin(), angles.end(), std::make_tuple(0, 2, 1)) != angles.end());
    }

    TEST(TestGraph, test_get_dihedrals)
    {
        auto g = Graph();
        g.add_node(0);
        g.add_node(1);
        g.add_node(2);
        g.add_node(3);
        g.add_edge(0, 1);
        g.add_edge(1, 2);
        g.add_edge(2, 3);
        g.add_edge(0, 3);
        auto dihedrals = g.get_dihedrals();
        EXPECT_EQ(dihedrals.size(), 4);
        EXPECT_TRUE(std::find(dihedrals.begin(), dihedrals.end(), std::make_tuple(3, 0, 1, 2)) != dihedrals.end());
        EXPECT_TRUE(std::find(dihedrals.begin(), dihedrals.end(), std::make_tuple(0, 1, 2, 3)) != dihedrals.end());
        EXPECT_TRUE(std::find(dihedrals.begin(), dihedrals.end(), std::make_tuple(1, 2, 3, 0)) != dihedrals.end());
        EXPECT_TRUE(std::find(dihedrals.begin(), dihedrals.end(), std::make_tuple(1, 0, 3, 2)) != dihedrals.end());
    }
}