#include "utils.h"
#include "atom.h"
#include "bond.h"

namespace molcpp
{

    // test Atom class
    TEST(TestAtom, test_init)
    {
        // create an atom and return shared_ptr
        auto a1 = create_atom();

    }

    TEST(TestAtom, test_set_get)
    {
        auto a1 = create_atom();
        a1->set("name", "C");
        a1->set("mass", 12.0);
        a1->set("charge", 1);
        // (*a1)["name"] = "C";
        // (*a1)["mass"] = 12.0;
        // (*a1)["charge"] = 1;

        // EXPECT_EQ((*a1)["name"].get<std::string>(), "C");
        // EXPECT_EQ((*a1)["mass"].get<double>(), 12.0);
        // EXPECT_EQ((*a1)["charge"].get<int>(), 1);

        // a1->set("name", "H");
        // a1->set("mass", 1.008);
        // a1->set("charge", 0);

        // EXPECT_EQ(a1->get("name").get<std::string>(), "H");
        // EXPECT_EQ(a1->get("mass").get<double>(), 1.008);
        // EXPECT_EQ(a1->get("charge").get<int>(), 0);

    }

    TEST(TestAtom, test_nbrs)
    {
        auto a1 = create_atom();
        auto a2 = create_atom();
        auto a3 = create_atom();
        auto bond12 = create_bond(a1, a2);
        auto bond13 = create_bond(a1, a3);
        auto bond23 = create_bond(a2, a3);
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


}