#include "utils.h"
#include "frame.h"

namespace molcpp
{

    TEST(TestFrame, test_init_frame)
    {
        Frame frame;
        EXPECT_EQ(frame.get_natoms(), 0);
        EXPECT_EQ(frame.get_nbonds(), 0);
        EXPECT_EQ(frame.get_timestep(), 0);
        EXPECT_EQ(frame.get_topology(), nullptr);
    }

    TEST(TestFrame, test_set_get_topo)
    {
        Frame frame;
        TopologyPtr topo = new_topology();
        frame.set_topology(topo);
        EXPECT_EQ(frame.get_topology(), topo);

    }



}