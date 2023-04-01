#include "utils.h"
#include "atom.h"
#include "bond.h"

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

}