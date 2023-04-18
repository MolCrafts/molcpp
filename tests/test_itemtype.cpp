#include "utils.h"
#include "itemtype.h"

namespace molcpp
{
    TEST(TestAtomType, test_atomtype)
    {
        auto a1 = AtomType("C");
        auto a2 = AtomType("C");
        EXPECT_EQ(a1, a2);
    }

    TEST(TestAtomType, test_set_get)
    {
        auto a1 = AtomType("C");
        a1.set("mass", 12.011);
        EXPECT_EQ(a1.get<double>("mass"), 12.011);
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

    TEST(TestBondType, test_set_get)
    {
        auto a1 = AtomType("C");
        a1.set("mass", 12.011);
        EXPECT_EQ(a1.get<double>("mass"), 12.011);
    }
}