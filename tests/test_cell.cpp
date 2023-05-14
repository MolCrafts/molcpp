#include "utils.h"
#include "cell.h"

namespace molcpp
{
    TEST(TestCell, test_init)
    {
        Cell cell1;
        EXPECT_EQ(cell1.get_lengths(), Vector3D({0, 0, 0}));
        EXPECT_EQ(cell1.get_tilts(), Vector3D({0, 0, 0}));
        Cell cell2({1, 2, 3});
        EXPECT_EQ(cell2.get_lengths(), Vector3D({1, 2, 3}));
        EXPECT_EQ(cell2.get_tilts(), Vector3D({0, 0, 0}));
        Cell cell3({1, 2, 3}, {4, 5, 6});
        EXPECT_EQ(cell3.get_lengths(), Vector3D({1, 2, 3}));
        EXPECT_EQ(cell3.get_tilts(), Vector3D({4, 5, 6}));
    }
}