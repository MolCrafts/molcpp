#include "utils.h"
#include "forcefield.h"
#include "atom.h"
#include "bond.h"

namespace molcpp
{
    TEST(TestForceField, test_init)
    {
        auto ff = ForceField();
    }

    TEST(TestForceField, test_def_atoms)
    {
        auto ff = ForceField();
        ff.def_atomtype("C");
        EXPECT_EQ(ff.get_natomtypes(), 1);
    }

    TEST(TestForceField, test_def_bonds)
    {
        auto ff = ForceField();
        auto at = ff.def_atomtype("C");
        ff.def_bondtype("C-C", at, at);
        EXPECT_EQ(ff.get_nbondtypes(), 1);
    }


    TEST(TestForceField, test_match_atom)
    {
        auto ff = ForceField();
        auto at = ff.def_atomtype("C");
        at->set("mass", 12.011);

        auto atom1 = create_atom();
        atom1->set("type", "C");
        bool isMatch = ff.match_atom(atom1.get());
        EXPECT_TRUE(isMatch);
        EXPECT_EQ(atom1->get<double>("mass"), 12.011);
    }

    TEST(TestForceField, test_match_bond)
    {
        auto ff = ForceField();
        auto at = ff.def_atomtype("C");
        at->set("charge", 0.0);
        at->set("mass", 12.011);
        auto bt = ff.def_bondtype("C-C", at, at);
        bt->set("k", 1000.0);
        bt->set("r0", 1.0);

        auto atom1 = create_atom();
        auto atom2 = create_atom();
        atom1->set_type(at);
        atom2->set_type(at);
        auto bond = create_bond(atom1.get(), atom1.get());

        bool isMatch = ff.match_bond(bond.get());
        EXPECT_TRUE(isMatch);
        EXPECT_EQ(bond->get<double>("k"), 1000.0);
        EXPECT_EQ(bond->get<double>("r0"), 1.0);
    }
}