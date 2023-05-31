#include "utils.h"
#include "atom.h"
#include "bond.h"
#include "itemtype.h"

namespace molcpp{

    TEST(TestBond, test_init)
    {
        auto a1 = Atom("c1");
        auto a2 = Atom("c2");
        auto b1 = Bond(&a1, &a2);
    }

    TEST(TestBond, test_get_ends)
    {
        auto a1 = Atom("c1");
        auto a2 = Atom("c2");
        auto b1 = Bond(&a1, &a2);

        EXPECT_TRUE(b1.get_itom()->equal_to(a1));
        EXPECT_TRUE(b1.get_jtom()->equal_to(a2));
    }

    TEST(TestBond, test_raw_ptr)
    {
        auto a1 = create_atom("c1");
        auto a2 = create_atom("c2");
        auto b1 = create_bond(a1.get(), a2.get());

        a1->set("mass", 12.0);
        a2->set("charge", 1.23);
        EXPECT_EQ(b1->get_itom()->get<double>("mass"), 12.0);
        EXPECT_EQ(b1->get_jtom()->get<double>("charge"), 1.23);
    }

    TEST(TestBond, test_equlity)
    {            
        auto a1 = create_atom("c1");
        auto a2 = create_atom("c2");
        auto a3 = create_atom("c3");
        auto b1 = create_bond(a1.get(), a2.get());
        auto b2 = create_bond(a1.get(), a3.get());

        EXPECT_TRUE(b1->equal_to(b1.get()));
        EXPECT_FALSE(b1->equal_to(b2.get()));

        EXPECT_TRUE(b1.get() == b1.get());
    }

    TEST(TestBond, test_set_get)
    {
        auto a1 = Atom();
        auto a2 = Atom();
        auto b1 = Bond(&a1, &a2);

        b1.set("order", 1);
        b1.set("length", 1.0);
        b1.set("force", 1.0);

        EXPECT_EQ(b1.get<int>("order"), 1);
        EXPECT_EQ(b1.get<double>("length"), 1.0);
        EXPECT_EQ(b1.get<double>("force"), 1.0);
    }

}