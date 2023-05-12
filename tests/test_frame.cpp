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
        EXPECT_EQ(frame->get<std::string>("name"),  xt::xarray<std::string>({"H", "O", "H"}));
    }

}