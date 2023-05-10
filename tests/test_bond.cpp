#include "utils.h"
#include "atom.h"
#include "bond.h"
#include "itemtype.h"

namespace molcpp{

    // test case for Bond class
    TEST(TestBond, test_init)
    {
        auto a1 = new_atom();
        auto a2 = new_atom();
        auto b1 = new_bond(a1, a2);
    }

    TEST(TestBond, test_get_ends)
    {
        auto a1 = new_atom();
        auto a2 = new_atom();
        auto b1 = new_bond(a1, a2);

        EXPECT_EQ(b1->get_itom(), a1);
        EXPECT_EQ(b1->get_jtom(), a2);
    }

    TEST(TestBond, test_bondtype)
    {
        auto at = new_atomtype("C");
        auto a1 = new_atom(at);
        auto a2 = new_atom(at);
        auto b1 = new_bond(a1, a2);

        auto bt = new_bondtype("C-C", a1->get_type(), a2->get_type());
        b1->set_type(bt);

        EXPECT_EQ(b1->get_bondtype(), bt);
        EXPECT_EQ(b1->get_itom()->get_type(), bt->get_itype());
        EXPECT_EQ(b1->get_jtom()->get_type(), bt->get_jtype());
    }

    TEST(TestBond, test_equlity)
    {            
        auto a1 = new_atom();
        auto a2 = new_atom();
        auto b1 = new_bond(a1, a2);
        auto b2 = new_bond(a1, a2);
        auto b3 = new_bond(a2, a1);

        EXPECT_TRUE(*b1 == *b2);
        EXPECT_TRUE(*b1 == *b3);
        EXPECT_TRUE(*b2 == *b3);
    }

    TEST(TestBond, test_set_get)
    {
        auto a1 = new_atom();
        auto a2 = new_atom();
        auto b1 = new_bond(a1, a2);

        b1->set("order", 1);
        b1->set("length", 1.0);
        b1->set("force", 1.0);

        EXPECT_EQ(b1->get<int>("order"), 1);
        EXPECT_EQ(b1->get<double>("length"), 1.0);
        EXPECT_EQ(b1->get<double>("force"), 1.0);
    }

}