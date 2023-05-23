#include "utils.h"
#include "cell.h"

namespace molcpp
{
    TEST(TestCell, test_init)
    {
        Cell cell1;
        EXPECT_EQ(cell1.get_lengths(), Vector({1, 1, 1}));
        EXPECT_EQ(cell1.get_tilts(), Vector({0, 0, 0}));
        EXPECT_EQ(cell1.get_angles(), Vector({90, 90, 90}));
        EXPECT_EQ(cell1.get_volume(), 1);

        Cell cell2({1, 2, 3}, {90, 90, 90});
        EXPECT_EQ(cell2.get_lengths(), Vector({1, 2, 3}));
        EXPECT_TRUE(xt::allclose(cell2.get_tilts(), Vector({0, 0, 0})));
        EXPECT_EQ(cell2.get_angles(), Vector({90, 90, 90}));
        EXPECT_EQ(cell2.get_volume(), 6);

        Cell cell3({1, 1, 1}, {45, 45, 45});
        EXPECT_EQ(cell3.get_lengths(), Vector({1, 1, 1}));
        EXPECT_TRUE(xt::allclose(cell3.get_tilts(), Vector({0.707, 0.707, 0.293}), 1e-3)) << cell3.get_tilts();
        EXPECT_EQ(cell3.get_angles(), Vector({45, 45, 45}));
        EXPECT_FLOAT_EQ(cell3.get_volume(), 0.45508987);

    }

    TEST(TestCell, test_orth_wrap)
    {

        Cell cell({2, 2, 2});
        Matrix points = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {-0.5, -0.5, -0.5}, {-1.5, -1.5, -1.5}};
        Matrix expected = {{0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {1.5, 1.5, 1.5}, {0.5, 0.5, 0.5}};

        EXPECT_TRUE(xt::allclose(cell.wrap(points), expected)) << cell.wrap(points);

    }

    TEST(TestCell, test_tric_wrap)
    {
            
        Cell cell({2, 2, 2}, {45, 45, 45});
        Matrix points = {{2, 1, 0}};
        Matrix expected = {{2, 1, 0}};  // TODO: need more tests

        EXPECT_TRUE(xt::allclose(cell.wrap(points), expected)) << cell.wrap(points);
    
    }

    TEST(TestCell, test_to_chemfiles)
    {
        auto cell = new_cell({2, 2, 2}, {90, 90, 90});
        chemfiles::UnitCell chem_cell = to_chemfiles(cell);
        auto expected_lengths = chemfiles::Vector3D(2, 2, 2);
        auto expected_angles = chemfiles::Vector3D(90, 90, 90);
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