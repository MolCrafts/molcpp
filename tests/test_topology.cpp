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

        // add atom 
        auto atom1 = create_atom();
        EXPECT_TRUE(topology->add_atom(atom1));
        EXPECT_TRUE(topology->has_atom(atom1));
        EXPECT_FALSE(topology->add_atom(atom1));

        // create atom in place
        auto atom2 = topology->create_atom();
        EXPECT_TRUE(topology->has_atom(atom2));

        // test natoms
        EXPECT_EQ(topology->get_natoms(), 2);
        EXPECT_EQ(topology->get_atoms().size(), 2);

        // delete atoms
        EXPECT_TRUE(topology->del_atom(atom1));
        EXPECT_FALSE(topology->has_atom(atom1));
        EXPECT_TRUE(topology->del_atom(atom2));
        EXPECT_EQ(topology->get_natoms(), 0);
    }

    TEST(TestTopology, test_bond_manage)
    {
        auto topology = create_topology();

        // add bond           
        auto atom1 = create_atom();
        auto atom2 = create_atom();
        auto bond1 = create_bond(atom1, atom2);
        topology->add_atom(atom1);
        topology->add_atom(atom2);
        EXPECT_TRUE(topology->add_bond(bond1));
        EXPECT_TRUE(topology->has_bond(bond1));

        // Repeatedly adding elements
        EXPECT_THROW(topology->create_bond(atom1, atom2), KeyError);
        EXPECT_THROW(topology->create_bond(atom2, atom1), KeyError);
        EXPECT_THROW(topology->create_bond(0, 1), KeyError);

        // create bond in place
        auto atom3 = topology->create_atom();
        auto atom4 = topology->create_atom();
        auto bond2 = topology->create_bond(atom3, atom4);

        // test nbonds
        EXPECT_EQ(topology->get_nbonds(), 2);
        EXPECT_EQ(topology->get_bonds().size(), 2);

        // delete bonds
        EXPECT_TRUE(topology->del_bond(bond1));
        EXPECT_FALSE(topology->has_bond(bond1));
        EXPECT_TRUE(topology->del_bond(bond2));
        EXPECT_EQ(topology->get_nbonds(), 0);
    }

}