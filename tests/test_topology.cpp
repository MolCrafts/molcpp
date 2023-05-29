#include "utils.h"
#include "topology.h"

namespace molcpp
{

    TEST(TestTopology, test_init)
    {
        auto topology = Topology();
    }

    TEST(TestTopology, test_atom_manage)
    {
        auto topology = create_topology();

        Atom* atom1 = topology->create_atom();
        EXPECT_TRUE(topology->has_atom(atom1));
        EXPECT_EQ(topology->get_natoms(), 1);

        // create atom in place
        Atom* atom2 = topology->create_atom();
        EXPECT_TRUE(topology->has_atom(atom2));

        // // test natoms
        EXPECT_EQ(topology->get_natoms(), 2);
        EXPECT_EQ(topology->get_atoms().size(), 2);

        // // delete atoms
        topology->del_atom(atom1);
        EXPECT_FALSE(topology->has_atom(atom1));
        EXPECT_EQ(topology->get_natoms(), 1);
        topology->del_atom(atom2);
        EXPECT_FALSE(topology->has_atom(atom2));
        EXPECT_EQ(topology->get_natoms(), 0);
    }

    TEST(TestTopology, test_bond_manage)
    {
        auto topology = create_topology();

        // create bond
        Atom* atom1 = topology->create_atom("atom1");
        Atom* atom2 = topology->create_atom("atom2");
        Bond* bond1 = topology->create_bond(atom1, atom2);

        Atom* atom3 = topology->create_atom("atom3");
        Atom* atom4 = topology->create_atom("atom4");
        Bond* bond2 = topology->create_bond(2, 3);

        // // test nbonds
        EXPECT_EQ(topology->get_nbonds(), 2);
        EXPECT_EQ(topology->get_bonds().size(), 2);

        // // delete bonds
        topology->del_bond(bond1);
        EXPECT_FALSE(topology->has_bond(bond1));
        EXPECT_EQ(topology->get_nbonds(), 1);
        topology->del_bond(atom3, atom4);
        EXPECT_FALSE(topology->has_bond(bond2));
        EXPECT_EQ(topology->get_nbonds(), 0);
    }

    TEST(TestSubTopo, test_atom_manage)
    {
        auto topology = create_topology();
        auto subtopo = topology->create_topology();

        Atom* atom1 = topology->create_atom();
        EXPECT_TRUE(topology->has_atom(atom1));
        EXPECT_EQ(topology->get_natoms(), 1);

        Atom* atom2 = subtopo->create_atom();
        EXPECT_TRUE(topology->has_atom(atom2));

        EXPECT_EQ(topology->get_natoms(), 2);

        topology->del_atom(atom1);
        EXPECT_FALSE(topology->has_atom(atom1));
        EXPECT_EQ(topology->get_natoms(), 1);
        topology->del_atom(atom2);
        EXPECT_FALSE(topology->has_atom(atom2));
        EXPECT_EQ(topology->get_natoms(), 0);
    }

    TEST(TestSubTopo, test_bond_manage)
    {
        auto topology = create_topology();
        auto subtopo = topology->create_topology();

        // 1 - 2 - 3 - 4
        Atom* atom1 = topology->create_atom("atom1");
        Atom* atom2 = topology->create_atom("atom2");
        Bond* bond1 = topology->create_bond(atom1, atom2);

        Atom* atom3 = subtopo->create_atom("atom3");
        Atom* atom4 = subtopo->create_atom("atom4");
        Bond* bond2 = subtopo->create_bond(atom3, atom4);

        Bond* bond3 = topology->create_bond(atom2, atom3);

        EXPECT_EQ(topology->get_nbonds(), 3);
        EXPECT_EQ(subtopo->get_nbonds(), 1);

        topology->del_bond(bond1);
        EXPECT_FALSE(topology->has_bond(bond1));
        EXPECT_EQ(topology->get_nbonds(), 2);

        topology->del_bond(bond2);
        EXPECT_FALSE(subtopo->has_bond(bond2));
        EXPECT_EQ(subtopo->get_nbonds(), 0);
        EXPECT_EQ(topology->get_nbonds(), 1);

        topology->del_bond(bond3);
        EXPECT_FALSE(topology->has_bond(bond3));
        EXPECT_EQ(topology->get_nbonds(), 0);
    }

    TEST(TestSubTopo, test_topo_manage)
    {
        auto top = create_topology();
        auto sub1 = create_topology();
        auto sub2 = create_topology();
        
        // 1 \       / 5
        // |   3 - 4   |
        // 2 /       \ 6

        Atom* atom1 = sub1->create_atom();
        Atom* atom2 = sub1->create_atom();
        Atom* atom3 = sub1->create_atom();
        sub1->create_bond(atom1, atom3);
        sub1->create_bond(atom2, atom3);
        sub1->create_bond(atom1, atom2);

        Atom* atom4 = sub2->create_atom();
        Atom* atom5 = sub2->create_atom();
        Atom* atom6 = sub2->create_atom();
        sub1->create_bond(atom4, atom5);
        sub1->create_bond(atom5, atom6);
        sub1->create_bond(atom6, atom4);

        sub1->create_bond(atom3, atom4);

        top->add_topology(sub1.release());
        top->add_topology(sub2.release());

        EXPECT_EQ(top->get_nbonds(), 7);

    }

    TEST(TestTopology, test_connect)
    {
        auto topology = create_topology();

        // add atom
        topology->create_atom("H");
        topology->create_atom("C");
        topology->create_atom("O");

        // add bond
        topology->create_bond(0, 1);
        topology->create_bond(1, 2);

        // test connect
        BondConnect bond_connect = topology->get_bond_connect();
        EXPECT_EQ(bond_connect.size(), 2);
        EXPECT_EQ(bond_connect[0], std::make_tuple(0, 1));
        EXPECT_EQ(bond_connect[1], std::make_tuple(1, 2));
    }

    TEST(TestTopology, test_set_get_positions)
    {
        auto topo = create_topology();
        topo->create_atom("H");
        topo->create_atom("C");
        auto positions = xt::xarray<double>({{1, 1, 1}, {2, 2, 2}});
        topo->set_positions(positions);
        xt::xarray<double> get_positions = topo->get_positions();

        EXPECT_EQ(get_positions.shape()[0], 2);
        EXPECT_EQ(get_positions.shape()[1], 3);
        EXPECT_EQ(xt::row(get_positions, 0), xt::xarray<double>({1, 1, 1}));
        EXPECT_EQ(xt::row(get_positions, 1), xt::xarray<double>({2, 2, 2}));
    }

    TEST(TestTopology, test_from_chemfiles)
    {
        auto frame = chemfiles::Frame(chemfiles::UnitCell({10, 10, 10}));
        frame.add_atom(chemfiles::Atom("H"), {1, 0, 0});
        frame.add_atom(chemfiles::Atom("O"), {0, 0, 0});
        frame.add_atom(chemfiles::Atom("H"), {0, 1, 0});

        frame.add_bond(0, 1);
        frame.add_bond(2, 1);

        std::unique_ptr<Topology> topo = from_chemfiles(frame.topology());

        EXPECT_EQ(topo->get_natoms(), 3);
        EXPECT_EQ(topo->get_nbonds(), 2);
    }

}