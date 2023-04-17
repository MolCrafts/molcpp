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

    TEST(TestAtomTypeManager, test_init)
    {

        auto avec = molcpp::AtomTypeManager();
        auto at1 = avec.def("C");
        EXPECT_EQ(at1->get_name(), "C");
        EXPECT_EQ(avec.get_ntypes(), 1);
        auto at2 = avec.def("H");
        EXPECT_EQ(at2->get_name(), "H");

        EXPECT_TRUE(avec.get("H").has_value());
        EXPECT_TRUE(avec.get("C").has_value());
    }
}