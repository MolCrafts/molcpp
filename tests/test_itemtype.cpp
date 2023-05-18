#include "utils.h"
#include "itemtype.h"

#include <map>
namespace molcpp
{

    TEST(TestAtomType, test_constructor)
    {
        auto a1 = AtomType("C");
        EXPECT_EQ(a1.get_name(), "C");
    }

    TEST(TestAtomType, test_get_name)
    {
        auto a1 = AtomType("C");
        EXPECT_EQ(a1.get_name(), "C");
    }

    TEST(TestAtomType, test_equal_to)
    {
        auto a1 = AtomType("C");
        AtomType& a2 = a1;
        auto a3 = new_atomtype("H");
        EXPECT_TRUE(a1.equal_to(a2));
        EXPECT_FALSE(a1.equal_to(*a3));
        EXPECT_TRUE(a1 == a2);
        EXPECT_FALSE(a1 != a2);
    }

    TEST(TestAtomType, test_set_get)
    {
        std::map<int, int> m = {{1, 2}, {3, 4}};
        auto a1 = AtomType("C"); 
        a1.set("mass", 12.011);
        EXPECT_EQ(a1.get<double>("mass"), 12.011);
        a1["charge"] = 0.0;
        EXPECT_EQ(a1["charge"].get<double>(), 0.0);
    }

    TEST(TestAtomTypeManager, test_init)
    {
        auto avec = molcpp::AtomTypeManager();
    }

    TEST(TestAtomTypeManager, test_def_get)
    {
        auto avec = molcpp::AtomTypeManager();
        auto at1 = avec.def("C");
        EXPECT_EQ(at1->get_name(), "C");
        EXPECT_EQ(avec.get_ntypes(), 1);
        auto at2 = avec.def("H");
        EXPECT_EQ(at2->get_name(), "H");
        EXPECT_EQ(avec.get_ntypes(), 2);

        EXPECT_TRUE(avec.get("H").has_value());
        EXPECT_TRUE(avec.get("C").has_value());
    }

    TEST(TestBondType, test_constructor)
    {
        auto a1 = new_atomtype("C");
        auto a2 = new_atomtype("H");
        auto b1 = BondType("C-H", a1, a2);
        EXPECT_EQ(b1.get_name(), "C-H");

        // test get i/jtype
        EXPECT_EQ(b1.get_itype(), a1);
        EXPECT_EQ(b1.get_jtype(), a2);
    }

    TEST(TestBondType, test_equal_to)
    {
        auto a1 = new_atomtype("C");
        auto a2 = new_atomtype("H");
        auto b1 = BondType("C-H", a1, a2);
        auto b2 = BondType("C-H", a1, a2);
        auto b3 = BondType("C-H", a2, a1);
        EXPECT_TRUE(b1.equal_to(b2));
        EXPECT_TRUE(b1.equal_to(b3));
        EXPECT_TRUE(b1 == b2);
        EXPECT_FALSE(b1 != b3);
    }

    TEST(TestBondType, test_set_get)
    {
        auto a1 = new_atomtype("C");
        auto a2 = new_atomtype("H");
        auto b1 = BondType("C-H", a1, a2);
        b1.set("k", 100.0);
        EXPECT_EQ(b1.get<double>("k"), 100.0);
        b1["r0"] = 1.0;
        EXPECT_EQ(b1["r0"].get<double>(), 1.0);
    }

    TEST(TestBondTypeManager, test_init)
    {
        auto bvec = molcpp::BondTypeManager();

    }
    
    TEST(TestBondTypeManager, test_set_get)
    {
        auto bvec = molcpp::BondTypeManager();
        auto a1 = new_atomtype("C");
        auto a2 = new_atomtype("H");
        auto b1 = bvec.def("C-H", a1, a2);
        EXPECT_EQ(bvec.get_ntypes(), 1);
        EXPECT_EQ(bvec.get("C-H"), b1);
        EXPECT_EQ(bvec.get(a1, a2), b1);
        EXPECT_EQ(bvec.get(a2, a1), b1);
    }

}