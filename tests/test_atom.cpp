#include "utils.h"
#include "atom.h"

namespace molcpp
{

    // test Atom class
    TEST(TestAtom, test_constructor)
    {
        auto a0 = Atom("a0");
        EXPECT_EQ(a0.get<std::string>("name"), "a0");
    }

    TEST(TestAtom, test_copy_constructor)
    {
        auto a0 = Atom("a0");
        a0.set("mass", 12.0);
        a0.set("str", "string");
        auto a1 = Atom(a0);
        EXPECT_EQ(a1.get<std::string>("name"), "a0");
        EXPECT_EQ(a1.get<double>("mass"), 12.0);
        EXPECT_EQ(a1.get<std::string>("str"), "string");
    }

    TEST(TestAtom, test_move_constructor)
    {
        auto a0 = Atom("a0");
        a0.set("mass", 12.0);
        a0.set("str", "string");
        auto a1 = Atom(std::move(a0));
        EXPECT_FALSE(a0.has("name"));
        EXPECT_EQ(a1.get<std::string>("name"), "a0");
        EXPECT_EQ(a1.get<double>("mass"), 12.0);
        EXPECT_EQ(a1.get<std::string>("str"), "string");
    }

    TEST(TestAtom, test_has)
    {
        auto a1 = Atom();
        a1.set("name", "C");
        EXPECT_TRUE(a1.has("name"));
        EXPECT_FALSE(a1.has("mass"));
    }

    TEST(TestAtom, test_set_get)
    {
        auto a1 = Atom();
        a1.set("name", "C");
        a1.set("mass", 12.0);
        a1.set("charge", 1);

        EXPECT_EQ(a1.get<std::string>("name"), "C");
        EXPECT_EQ(a1.get<double>("mass"), 12.0);
        EXPECT_EQ(a1.get<int>("charge"), 1);
        EXPECT_EQ(a1.get<int>("unknown", 1), 1);
    }

    TEST(TestAtom, test_equality)
    {
        auto a1 = Atom();
        auto a2 = Atom();

        EXPECT_TRUE(a1.equal_to(a1));
        EXPECT_FALSE(a1.equal_to(a2));

        Atom& a3 = a1;
        Atom& a4 = a2;
        EXPECT_TRUE(a3.equal_to(a3));
        EXPECT_FALSE(a3.equal_to(a4));
        EXPECT_TRUE(a3 == a3);
        EXPECT_FALSE(a3 == a4);
    }

    TEST(TestAtom, test_raw_ptr_equality)
    {
        auto a1 = create_atom();
        auto a2 = create_atom();

        EXPECT_TRUE(a1->equal_to(a1.get()));
        EXPECT_FALSE(a1->equal_to(a2.get()));
    }

    TEST(TestAtom, test_from_chemfiles)
    {
        auto chflAtom = chemfiles::Atom("tAtom", "C");
        chflAtom.set_mass(12.0);
        chflAtom.set_charge(1.0);
        chflAtom.set("full_name", "testAtom");
        auto atom = from_chemfiles(chflAtom);
        EXPECT_EQ(atom->get<std::string>("name"), "tAtom");
        EXPECT_EQ(atom->get<std::string>("type"), "C");
        EXPECT_EQ(atom->get<double>("mass"), 12.0);
        EXPECT_EQ(atom->get<double>("charge"), 1.0);
        EXPECT_EQ(atom->get<std::string>("full_name"), "testAtom");
    }

    TEST(TestAtom, test_pos)
    {
        auto atom = Atom();
        EXPECT_EQ(atom.get_position(), Vector3D(0, 0, 0));

        atom.set_position({1.0, 2.0, 3.0});
        EXPECT_EQ(atom.get_position(), Vector3D(1, 2, 3));
    }
}