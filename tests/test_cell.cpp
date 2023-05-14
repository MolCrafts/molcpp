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

    TEST(TestCell, test_orth_wrap)
    {

        Cell cell({2, 2, 2});
        Matrix3D points = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {-0.5, -0.5, -0.5}, {-1.5, -1.5, -1.5}};
        Matrix3D expected = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {1.5, 1.5, 1.5}, {0.5, 0.5, 0.5}};

        EXPECT_TRUE(xt::allclose(cell.wrap(points), expected)) << cell.wrap(points);

    }

    TEST(TestCell, test_tric_wrap)
    {
            
        Cell cell({2, 2, 2}, {1, 1, 1});
        Matrix3D points = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {-0.5, -0.5, -0.5}, {-1.5, -1.5, -1.5}};
        Matrix3D expected = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {3.5, 2.5, 1.5}, {2.5, 1.5, 0.5}};

        EXPECT_TRUE(xt::allclose(cell.wrap(points), expected)) << cell.wrap(points);
    
    }

    TEST(TestCell, test_to_chemfiles)
    {
        Cell cell({2, 2, 2}, {1, 1, 1});
        chemfiles::UnitCell chem_cell = to_chemfiles(cell);
        auto expected_lengths = chemfiles::Vector3D(2, 2, 2);
        auto expected_angles = chemfiles::Vector3D(60, 60, 60);
        auto lengths = chem_cell.lengths();
        auto angles = chem_cell.angles();
        EXPECT_FLOAT_EQ(lengths[0], expected_lengths[0]);
        EXPECT_FLOAT_EQ(lengths[1], expected_lengths[1]);
        EXPECT_FLOAT_EQ(lengths[2], expected_lengths[2]);
        EXPECT_FLOAT_EQ(angles[0], expected_angles[0]);
        EXPECT_FLOAT_EQ(angles[1], expected_angles[1]);
        EXPECT_FLOAT_EQ(angles[2], expected_angles[2]);
    }
}