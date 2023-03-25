#include "utils.h"
#include "atom.h"

namespace MolCpp
{

    TEST(TestAtom, test_init)
    {
        auto atom = std::make_shared<Atom>();
        EXPECT_EQ(atom->get_nbonds(), 0);

    }

    TEST(TestAtom, test_crud_bond)
    {
        auto atom = std::make_shared<Atom>();
        auto atom1 = std::make_shared<Atom>();
        auto bond = std::make_shared<Bond>(atom, atom1);
        atom->add_bond(bond);
        EXPECT_EQ(atom->get_nbonds(), 1);
        EXPECT_TRUE(atom->has_bond(bond));
        EXPECT_EQ(atom->get_bonds().size(), 1);

        atom->del_bond(bond);
        EXPECT_EQ(atom->get_nbonds(), 0);
        EXPECT_FALSE(atom->has_bond(bond));
    }

}