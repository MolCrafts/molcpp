#include "utils.h"
#include "topology.h"

namespace molcpp
{

    TEST(TestTopology, test_init)
    {
        auto topology = create_topology();
    }

    TEST(TestTopology, test_atom_manage)
    {

        auto topology = create_topology();
        auto atom1 = create_atom();
        EXPECT_TRUE(topology->add_atom(atom1));
        EXPECT_TRUE(topology->has_atom(atom1));
        EXPECT_FALSE(topology->add_atom(atom1));

        auto atom2 = topology->create_atom();
        EXPECT_TRUE(topology->has_atom(atom2));

    }

    TEST(TestTopology, test_bond_manage)
    {
            
        auto topology = create_topology();
        auto atom1 = create_atom();
        auto atom2 = create_atom();
        auto bond1 = create_bond(atom1, atom2);
        topology->add_atom(atom1);
        topology->add_atom(atom2);
        EXPECT_TRUE(topology->add_bond(bond1));
        EXPECT_TRUE(topology->has_bond(bond1));

        EXPECT_THROW(topology->create_bond(atom1, atom2), std::runtime_error);
        EXPECT_THROW(topology->create_bond(atom2, atom1), std::runtime_error);
        EXPECT_THROW(topology->create_bond(0, 1), std::runtime_error);
    }

}