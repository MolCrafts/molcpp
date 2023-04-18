#include "utils.h"
#include "forcefield.h"

namespace molcpp
{

    TEST(TestForceField, test_def)
    {

        auto ff = ForceField();
        auto at = ff.def_atomtype("C");
        (*at)["mass"] = 12.011;
        auto bt = ff.def_bondtype("C-C", at, at);
        (*bt)["k"] = 1000.0;
        (*bt)["r0"] = 1.0;
    }

    TEST(TestForceField, test_match_atom)
    {
        auto ff = ForceField();
        auto at = ff.def_atomtype("C");
        (*at)["type"] = "C";
        (*at)["mass"] = 12.011;

        auto atom1 = create_atom();
        atom1->set_type("C");
        bool isMatch = ff.match_atom(atom1);
        EXPECT_TRUE(isMatch);
        EXPECT_EQ((*atom1)["mass"].get<double>(), 12.011);
    }

    TEST(TestForceField, test_match_bond)
    {
        auto ff = ForceField();
        auto at = ff.def_atomtype("C");
        (*at)["type"] = "C";
        (*at)["mass"] = 12.011;
        auto bt = ff.def_bondtype("C-C", at, at);
        (*bt)["k"] = 1000.0;
        (*bt)["r0"] = 1.0;

        auto atom1 = create_atom("C");
        auto atom2 = create_atom("C");
        auto bond = create_bond(atom1, atom2);
        bool isMatch = ff.match_bond(bond);
        EXPECT_TRUE(isMatch);
        EXPECT_EQ((*bond)["k"].get<double>(), 1000.0);
        EXPECT_EQ((*bond)["r0"].get<double>(), 1.0);
    }
}