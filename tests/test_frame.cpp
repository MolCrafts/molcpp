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
        auto topo = create_topology();
        frame.set_topology(topo.release());
    }

    TEST(TestFrame, test_set_get_positions)
    {
        Frame frame;
        auto topo = frame.get_topology();
        topo->create_atom();
        topo->create_atom();
        topo->create_atom();
        EXPECT_EQ(frame.get_natoms(), 3);
        frame.set_positions(xt::xarray<double>({{1, 0, 0}, {0, 0, 0}, {0, 1, 0}}));
        EXPECT_EQ(frame.get_positions(), xt::xarray<double>({{1, 0, 0}, {0, 0, 0}, {0, 1, 0}}));
    }

    TEST(TestFrame, test_from_chemfiles)
    {
        auto _frame = chemfiles::Frame(chemfiles::UnitCell({10, 10, 10}));

        _frame.add_atom(chemfiles::Atom("H"), {1, 0, 0});
        _frame.add_atom(chemfiles::Atom("O"), {0, 0, 0});
        _frame.add_atom(chemfiles::Atom("H"), {0, 1, 0});

        _frame.add_bond(0, 1);
        _frame.add_bond(2, 1);

        auto frame = from_chemfiles(_frame);
        // EXPECT_EQ(frame->get_natoms(), 3);
        // EXPECT_EQ(frame->get_nbonds(), 2);
        // EXPECT_EQ(frame->get<std::string>("name"), xt::xarray<std::string>({"H", "O", "H"}));
        // EXPECT_EQ(frame->get_positions(), xt::xarray<double>({{1, 0, 0}, {0, 0, 0}, {0, 1, 0}}));
    }

    TEST(TestFrame, test_to_chemfiles)
    {
        auto frame = create_frame();
        auto topo = frame->get_topology();
        topo->create_atom();
        topo->create_atom();
        topo->create_atom();
        EXPECT_EQ(frame->get_natoms(), 3);
        topo->create_bond(0, 1);
        topo->create_bond(0, 2);
        EXPECT_EQ(frame->get_nbonds(), 2);
        frame->set_cell(create_cell({10, 10, 10}).release());
        auto chflFrame = to_chemfiles(frame.get());
        EXPECT_EQ(chflFrame.size(), 3);
        EXPECT_EQ(chflFrame.topology().bonds().size(), 2);
    }

}