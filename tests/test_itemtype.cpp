#include "utils.h"
#include "itemtype.h"

namespace molcpp
{
TEST(TestItemType, test_atomtype)
{
    // auto at1 = create_atomtype("C");
    // EXPECT_EQ(at1->get_name(), "C");
    // auto at2 = create_atomtype("C");
    // EXPECT_EQ(*at1, *at2);
    auto a1 = AtomType("C");
    auto a2 = AtomType("C");
    EXPECT_EQ(a1, a2);
}
}