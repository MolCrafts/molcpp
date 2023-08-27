#include "approx.h"
#include "box.h"
#include "mat3.h"
#include "vec3.h"
#include <doctest/doctest.h>

namespace molcpp {
TEST_SUITE("TestBox") {
  TEST_CASE("test_init") {
    Box box1;
    CHECK_EQ(box1.get_lengths(), Vec3<double>(1, 1, 1));
    CHECK_EQ(box1.get_tilts(), Vec3<double>(0, 0, 0));
    CHECK_EQ(box1.get_angles(), Vec3<double>(90, 90, 90));
    CHECK_EQ(box1.get_volume(), 1);

    Box box2({1, 2, 3}, {90, 90, 90});
    CHECK_EQ(box2.get_lengths(), Vec3<double>(1, 2, 3));
    CHECK(approx_eq(box2.get_tilts(), Vec3<double>(0, 0, 0)));
    CHECK_EQ(box2.get_angles(), Vec3<double>(90, 90, 90));
    CHECK_EQ(box2.get_volume(), 6);

    Box box3({1, 1, 1}, {45, 45, 45});
    CHECK_EQ(box3.get_lengths(), Vec3<double>(1, 1, 1));
    CHECK(
        approx_eq(box3.get_tilts(), Vec3<double>(0.707, 0.707, 0.293), 1e-03));
    CHECK_EQ(box3.get_angles(), Vec3<double>(45, 45, 45));
    CHECK(approx_eq(box3.get_volume(), 0.45509, 1e-05));
  }

  TEST_CASE("test_orth_wrap") {

    Box box({2, 2, 2});
    std::vector<Vec3<double>> points = {{0.5, 0.5, 0.5},
                                        {1.5, 1.5, 1.5},
                                        {-0.5, -0.5, -0.5},
                                        {-1.5, -1.5, -1.5}};
    std::vector<Vec3<double>> expected = {
        {0.5, 0.5, 0.5}, {1.5, 1.5, 1.5}, {1.5, 1.5, 1.5}, {0.5, 0.5, 0.5}};
    auto wrapped_points = box.wrap(points);
    CHECK(std::equal(wrapped_points.begin(), wrapped_points.end(),
                     expected.begin()));
  }

  TEST_CASE("test_tric_wrap") {

    Box box({2, 2, 2}, {45, 45, 45});
    std::vector<Vec3<double>> points = {{2, 1, 0}};
    std::vector<Vec3<double>> expected = {{2, 1, 0}}; // TODO: need more tests
    auto wrapped_points = box.wrap(points);
    CHECK(std::equal(wrapped_points.begin(), wrapped_points.end(),
                     expected.begin()));
  }
}
} // namespace molcpp