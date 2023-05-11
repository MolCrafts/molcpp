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



}