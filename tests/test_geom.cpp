#include <doctest/doctest.h>
#include "geom.hpp"

#include "approx.hpp"
#include "mat3.hpp"
#include "vec3.hpp"

// Ref:
// https://www.vcalc.com/wiki/vector-rotation
// https://www.andre-gaschler.com/rotationconverter/

namespace molpack {
TEST_SUITE("geom") {
  TEST_CASE("rotate with matrix") {
    Vec3<double> v{1, 0, 0};
    Mat3 rot = Mat3<double>(0, -1, 0, 1, 0, 0, 0, 0, 1);
    Vec3 r = rotate(v, rot);
    CHECK(r.getX() == doctest::Approx(0));
    CHECK(r.getY() == doctest::Approx(1));
    CHECK(r.getZ() == doctest::Approx(0));
  }

  TEST_CASE("rotate with aixs-angle") {
    Vec3<double> v{1, 0, 0};
    Vec3<double> axis{0, 0, 1};
    Vec3 r = rotate(v, axis, 90.);
    CHECK(r.getX() == doctest::Approx(0));
    CHECK(r.getY() == doctest::Approx(1));
    CHECK(r.getZ() == doctest::Approx(0));
  }

  TEST_CASE("rotate with axis-angle1") {
    Vec3<double> v{1, 2, 3};
    Vec3<double> axis{2, 1, 0};
    Vec3 r = rotate(v, axis, 45.);
    CHECK(r.getX() == doctest::Approx(2.12441923));
    CHECK(r.getY() == doctest::Approx(-0.24883846));
    CHECK(r.getZ() == doctest::Approx(3.07000364));
  }

  TEST_CASE("rotate with axis-angle2") {
    Vec3<double> v{2, -1, 4};
    Vec3<double> axis{0, 0, 1};
    Vec3 r = rotate(v, axis, 90.);
    CHECK(r.getX() == doctest::Approx(1));
    CHECK(r.getY() == doctest::Approx(2));
    CHECK(r.getZ() == doctest::Approx(4));
  }

  TEST_CASE("rotate with axis-angle3") {
    Vec3<double> v{3, 2, 1};
    Vec3<double> axis{1, 2, 1};
    Vec3 r = rotate(v, axis, 30.);
    CHECK(r.getX() == doctest::Approx(2.77670901));
    CHECK(r.getY() == doctest::Approx(2.49756469));
    CHECK(r.getZ() == doctest::Approx(0.22816162));
  }

  TEST_CASE("rotate with axis-angle4") {
    Vec3<double> v{0, 1, 0};
    Vec3<double> axis{1, 0, 0};
    Vec3 r = rotate(v, axis, 90.);
    CHECK(r.getX() == doctest::Approx(0));
    CHECK(r.getY() == doctest::Approx(0));
    CHECK(r.getZ() == doctest::Approx(1));
  }

  TEST_CASE("rotate with Euler angle") {
    Vec3<double> v{1, 0, 0};
    Vec3<double> r = rotate(v, 0., 0., 90.);
    CHECK(r.getX() == doctest::Approx(0));
    CHECK(r.getY() == doctest::Approx(1));
    CHECK(r.getZ() == doctest::Approx(0));
  }
}
}  // namespace molpack