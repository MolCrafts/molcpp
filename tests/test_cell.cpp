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

    TEST(TestCell, orth_wrap)
    {

        Cell cell({2, 2, 2});
        Matrix3D points = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {-0.5, -0.5, -0.5}, {-1.5, -1.5, -1.5}};
        Matrix3D expected = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {1.5, 1.5, 1.5}, {0.5, 0.5, 0.5}};

        EXPECT_TRUE(xt::allclose(cell.wrap(points), expected)) << cell.wrap(points);

    }

    TEST(TestCell, tric_wrap)
    {
            
        Cell cell({2, 2, 2}, {1, 1, 1});
        Matrix3D points = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {-0.5, -0.5, -0.5}, {-1.5, -1.5, -1.5}};
        Matrix3D expected = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {3.5, 2.5, 1.5}, {2.5, 1.5, 0.5}};

        EXPECT_TRUE(xt::allclose(cell.wrap(points), expected)) << cell.wrap(points);
    
    }
}