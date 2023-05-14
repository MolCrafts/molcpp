#include "utils.h"
#include "frame.h"

namespace molcpp
{

    TEST(TestFrame, test_init_frame)
    {
        Frame frame;
    }

    TEST(TestFrame, test_set_get_topo)
    {
        Frame frame;
        TopologyPtr topo = new_topology();
        frame.set_topology(topo);
        EXPECT_EQ(frame.get_topology(), topo);
    }

    TEST(TestFrame, test_from_chemfiles)
    {
        auto _frame = chemfiles::Frame(chemfiles::UnitCell({10, 10, 10}));

        _frame.add_atom(chemfiles::Atom("H"), {1, 0, 0});
        _frame.add_atom(chemfiles::Atom("O"), {0, 0, 0});
        _frame.add_atom(chemfiles::Atom("H"), {0, 1, 0});

        _frame.add_bond(0, 1);
        _frame.add_bond(2, 1);

        auto frame = new_frame(_frame);
        EXPECT_EQ(frame->get_natoms(), 3);
        EXPECT_EQ(frame->get_nbonds(), 2);
        EXPECT_EQ(frame->get<std::string>("name"), xt::xarray<std::string>({"H", "O", "H"}));
    }

    TEST(TestFrame, test_to_chemfiles)
    {
        auto frame = new_frame();
        auto topo = frame->get_topology();
        topo->new_atom();
        topo->new_atom();
        topo->new_atom();
        topo->new_bond(0, 1);
        topo->new_bond(1, 2);
        EXPECT_EQ(frame->get_natoms(), 3);
        EXPECT_EQ(frame->get_nbonds(), 2);
        frame->set_cell(Cell({2, 2, 2}, {1, 1, 1}));
        auto chflFrame = to_chemfiles(frame);
        EXPECT_EQ(chflFrame.size(), 3);
        EXPECT_EQ(chflFrame.topology().bonds().size(), 2);
    }

}