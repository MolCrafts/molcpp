#include "utils.h"
#include "topology.h"

namespace molcpp
{

    TEST(TestTopology, test_init)
    {
        auto topology = new_topology();
    }

    TEST(TestTopology, test_atom_manage)
    {
        auto topology = new_topology();

        // add atom 
        auto atom1 = new_atom();
        topology->add_atom(atom1);
        EXPECT_TRUE(topology->has_atom(atom1));

        // create atom in place
        auto atom2 = topology->new_atom();
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
        auto topology = new_topology();

        // add bond           
        auto atom1 = new_atom("atom1");
        auto atom2 = new_atom("atom2");
        auto bond1 = new_bond(atom1, atom2);
        topology->add_atom(atom1);
        topology->add_atom(atom2);
        topology->add_bond(bond1);
        EXPECT_TRUE(topology->has_bond(bond1));

        // create bond in place
        auto atom3 = topology->new_atom("atom3");
        auto atom4 = topology->new_atom("atom4");
        auto bond2 = topology->new_bond(atom3, atom4);

        // test nbonds
        EXPECT_EQ(topology->get_nbonds(), 2);
        EXPECT_EQ(topology->get_bonds().size(), 2);

        // delete bonds
        EXPECT_TRUE(topology->del_bond(bond1));
        EXPECT_FALSE(topology->has_bond(bond1));
        EXPECT_TRUE(topology->del_bond(bond2));
        EXPECT_EQ(topology->get_nbonds(), 0);
    }

    TEST(TestTopology, test_connect)
    {
        auto topology = new_topology();

        // add atom 
        topology->new_atom("H");
        topology->new_atom("C");
        topology->new_atom("O");

        // add bond
        topology->new_bond(0, 1);
        topology->new_bond(1, 2);

        // test connect
        auto bond_connect = topology->get_bond_connect();
        EXPECT_EQ(bond_connect.size(), 2);
        EXPECT_EQ(bond_connect[0], std::vector<size_t>({0, 1}));
        EXPECT_EQ(bond_connect[1], std::vector<size_t>({1, 2}));
    }

    TEST(TestTopology, test_set_get_positions)
    {
        auto topo = new_topology();
        topo->new_atom("H");
        topo->new_atom("C");
        auto positions = xt::xarray<double>({ {0, 0, 0}, {1, 1, 1} });
        topo->set_positions(positions);
        xt::xarray<double> get_positions = topo->get_positions();

        EXPECT_EQ(get_positions.shape()[0], 2);
        EXPECT_EQ(get_positions.shape()[1], 3);
        EXPECT_EQ(xt::row(get_positions, 0), xt::xarray<double>({0, 0, 0}));
        EXPECT_EQ(xt::row(get_positions, 1), xt::xarray<double>({1, 1, 1}));
    }

    TEST(TestTopology, test_from_chemfiles)
    {
        auto frame = chemfiles::Frame(chemfiles::UnitCell({10, 10, 10}));
        frame.add_atom(chemfiles::Atom("H"), {1, 0, 0});
        frame.add_atom(chemfiles::Atom("O"), {0, 0, 0});
        frame.add_atom(chemfiles::Atom("H"), {0, 1, 0});

        frame.add_bond(0, 1);
        frame.add_bond(2, 1);

        auto topo = new_topology(frame.topology());

        EXPECT_EQ(topo->get_natoms(), 3);
        EXPECT_EQ(topo->get_nbonds(), 2);
    }

}