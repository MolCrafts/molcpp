#include "utils.h"
#include "atom.h"
#include "bond.h"
#include "itemtype.h"

namespace molcpp{

    // test case for Bond class
    TEST(TestBond, test_init)
    {

        auto a1 = create_atom();
        auto a2 = create_atom();
        auto b1 = create_bond(a1, a2);

    }

    TEST(TestBond, test_eq)
    {
            
        auto a1 = create_atom();
        auto a2 = create_atom();
        auto b1 = create_bond(a1, a2);
        auto b2 = create_bond(a1, a2);
        auto b3 = create_bond(a2, a1);

        EXPECT_TRUE(*b1 == *b2);
        EXPECT_TRUE(*b1 == *b3);
        EXPECT_TRUE(*b2 == *b3);
    
    }

    TEST(TestBond, test_bondtype)
    {
        auto at = create_atomtype("C");
        auto a1 = create_atom(at);
        auto a2 = create_atom(at);
        auto b1 = create_bond(a1, a2);

        auto bt = create_bondtype("C-C", a1->get_type(), a2->get_type());
        b1->set_type(bt);

        EXPECT_EQ(b1->get_itom()->get_type(), bt->get_itype());
        EXPECT_EQ(b1->get_jtom()->get_type(), bt->get_jtype());
    }

}