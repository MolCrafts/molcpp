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
}