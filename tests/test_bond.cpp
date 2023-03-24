#include "utils.h"
#include "bond.h"


// test case for Bond class
TEST(TestBond, test_bond)
{
    auto bgn = std::make_shared<MolCpp::Atom>();
    auto end = std::make_shared<MolCpp::Atom>();
    auto bond = std::make_shared<MolCpp::Bond>(bgn, end);
    EXPECT_EQ(bond->get_bgn(), bgn);
    EXPECT_EQ(bond->get_end(), end);
}

