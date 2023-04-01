#include "utils.h"
#include "forcefield.h"

TEST(TestAtomType, test_init)
{

    auto at1 = molcpp::AtomType("C");
    auto at2 = molcpp::AtomType("C");
    auto at3 = molcpp::AtomType("H");

    EXPECT_EQ(at1, at2);
    EXPECT_NE(at1, at3);

}

TEST(TestAtomTypeManager, test_init)
{

    auto avec = molcpp::AtomTypeManager();
    auto at1 = avec.def("C");
    EXPECT_EQ(at1->get_name(), "C");
    EXPECT_EQ(avec.get_ntypes(), 1);
    auto at2 = avec.def("H");
    EXPECT_EQ(at2->get_name(), "H");
    
}

TEST(TestForceField, test_def)
{

}