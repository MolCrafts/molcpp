#include "utils.h"
#include "atom.h"
#include "bond.h"

namespace molcpp
{

    // test Atom class
    TEST(TestAtom, test_init)
    {
        auto a0 = Atom("a0");
        auto a1 = new_atom("a1");
        EXPECT_EQ(a0.get<std::string>("name"), "a0");
        EXPECT_EQ(a1->get<std::string>("name"), "a1");
    }

    TEST(TestAtom, test_has)
    {
        auto a1 = new_atom();
        a1->set("name", "C");

        EXPECT_TRUE(a1->has("name"));
        EXPECT_FALSE(a1->has("mass"));
    }

    TEST(TestAtom, test_set_get)
    {
        auto a1 = new_atom();
        a1->set("name", "C");
        a1->set("mass", 12.0);
        a1->set("charge", 1);

        EXPECT_EQ(a1->get<std::string>("name"), "C");
        EXPECT_EQ(a1->get<double>("mass"), 12.0);
        EXPECT_EQ(a1->get<int>("charge"), 1);
        EXPECT_EQ(a1->get<int>("unknown", 1), 1);
    }

    TEST(TestAtom, test_nbrs)
    {
        auto a1 = new_atom();
        auto a2 = new_atom();
        auto a3 = new_atom();
        auto bond12 = new_bond(a1, a2);
        auto bond13 = new_bond(a1, a3);
        auto bond23 = new_bond(a2, a3);
        a1->add_bond(bond12);
        a2->add_bond(bond12);
        a1->add_bond(bond13);
        a3->add_bond(bond13);
        a2->add_bond(bond23);
        a3->add_bond(bond23);

        EXPECT_TRUE(a1->is_nbr(a2));
        EXPECT_TRUE(a2->is_nbr(a3));
        EXPECT_TRUE(a3->is_nbr(a1));

        EXPECT_EQ(a1->get_nbrs().size(), 2);
        EXPECT_EQ(a2->get_nbrs().size(), 2);
        EXPECT_EQ(a3->get_nbrs().size(), 2);

        a1->del_bond(bond12);
        a1->del_bond(bond13);

        EXPECT_FALSE(a1->is_nbr(a2));
        EXPECT_FALSE(a1->is_nbr(a3));
        EXPECT_EQ(a1->get_nbrs().size(), 0);
    }

    TEST(TestAtom, test_has_bond)
    {
        auto a1 = new_atom();
        auto a2 = new_atom();
        auto b1 = new_bond(a1, a2);

        a1->add_bond(b1);
        EXPECT_TRUE(a1->has_bond(b1));
    }

    TEST(TestAtom, test_equality)
    {
        auto a1 = new_atom();
        auto a2 = new_atom();

        EXPECT_TRUE(a1->equal_to(a1));
        EXPECT_FALSE(a1->equal_to(a2));

        auto a3 = Atom();
        auto a4 = Atom();
        EXPECT_TRUE(a3.equal_to(a3));
        EXPECT_FALSE(a3.equal_to(a4));
        EXPECT_TRUE(a3 == a3);
        EXPECT_FALSE(a3 == a4);
    }

    TEST(TestAtom, test_from_chemfiles)
    {
        auto chflAtom = chemfiles::Atom("tAtom", "C");
        chflAtom.set_mass(12.0);
        chflAtom.set_charge(1.0);
        chflAtom.set("full_name", "testAtom");
        auto atom = new_atom(chflAtom);
        EXPECT_EQ(atom->get<std::string>("name"), "tAtom");
        EXPECT_EQ(atom->get<std::string>("type"), "C");
        EXPECT_EQ(atom->get<double>("mass"), 12.0);
        EXPECT_EQ(atom->get<double>("charge"), 1.0);
        EXPECT_EQ(atom->get<std::string>("full_name"), "testAtom");
    }

    TEST(TestAtom, test_pos)
    {
        auto atom = new_atom();
        EXPECT_EQ(atom->get_position(), Vector3D(0, 0, 0));

        atom->set_position({1.0, 2.0, 3.0});
        EXPECT_EQ(atom->get_position(), Vector3D(1, 2, 3));
    }
}