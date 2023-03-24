#include "utils.h"
#include "graph.h"

namespace MolCpp
{
    TEST(TestNode, test_init)
    {
        Node node;
        EXPECT_EQ(node.get_nedges(), 0);
    }

    TEST(TestNode, test_add_edge)
    {
        Node node;
        EdgePtr edge = std::make_shared<Edge>();
        node.add_edge(edge);
        EXPECT_EQ(node.get_nedges(), 1);
        EXPECT_TRUE(node.has_edge(edge));

        node.del_edge(edge);
        EXPECT_EQ(node.get_nedges(), 0);
        EXPECT_FALSE(node.has_edge(edge));
    }
}