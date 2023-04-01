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
        auto atom = create_atom();
        EXPECT_TRUE(topology->add_atom(atom));
        EXPECT_TRUE(topology->has_atom(atom));
        EXPECT_FALSE(topology->add_atom(atom));

        auto atom2 = topology->create_atom();
        // EXPECT_TRUE(topology->has_atom(atom2));

    }

    // TEST(TestTopology, test_bond_manage)
    // {
            
    //     auto topology = create_topology();
    //     auto atom1 = create_atom();
    //     auto atom2 = create_atom();
    //     auto bond1 = create_bond(atom1, atom2);
    //     EXPECT_TRUE(topology->add_bond(bond1));
    //     EXPECT_TRUE(topology->has_bond(bond1));
    //     // EXPECT_THROW(topology->add_bond(bond1), std::runtime_error);

    //     auto bond2 = topology->create_bond(atom1, atom2);
    //     EXPECT_TRUE(topology->has_bond(bond2));

    //     auto bond3 = topology->create_bond(atom2, atom1);
    //     EXPECT_TRUE(topology->has_bond(bond3));

    //     auto bond4 = topology->create_bond(0, 1);
    //     EXPECT_TRUE(topology->has_bond(bond4));
    // }

}