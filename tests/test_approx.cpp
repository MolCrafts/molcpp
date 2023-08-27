#include <doctest/doctest.h>

#include "approx.h"
#include "mat3.h"
#include "vec3.h"

namespace molcpp
{
TEST_SUITE("Approx utils")
{

    TEST_CASE("Test Scalar")
    {

        // default eps is 1e-12
        CHECK(approx_eq(1.0, 1.0));
        CHECK(approx_eq(1.0, 1.0 + 1e-13));
        CHECK(approx_eq(1.0, 1.0 - 1e-13));
        CHECK(!approx_eq(1.0, 1.0 + 1e-10));
        CHECK(!approx_eq(1.0, 1.0 - 1e-10));
    }

    TEST_CASE("Test Vector")
    {
        Vec3<double> A = Vec3<double>(1.0, 2.0, 3.0);
        Vec3<double> B = Vec3<double>(1.0, 2.0, 3.0);
        Vec3<double> C = Vec3<double>(1.0 + 1e-13, 2.0 + 1e-13, 3.0 + 1e-13);
        Vec3<double> D = Vec3<double>(1.0 - 1e-13, 2.0 - 1e-13, 3.0 - 1e-13);
        Vec3<double> E = Vec3<double>(1.0 + 1e-10, 2.0 + 1e-10, 3.0 + 1e-10);
        Vec3<double> F = Vec3<double>(1.0 - 1e-10, 2.0 - 1e-10, 3.0 - 1e-10);

        CHECK(approx_eq(A, B));
        CHECK(approx_eq(A, C));
        CHECK(approx_eq(A, D));
        CHECK(!approx_eq(A, E));
        CHECK(!approx_eq(A, F));
    }

    TEST_CASE("Test Matrix")
    {
        Mat3<double> A = Mat3<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
        Mat3<double> B = Mat3<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
        Mat3<double> C = Mat3<double>(1.0 + 1e-13, 2.0 + 1e-13, 3.0 + 1e-13, 4.0 + 1e-13, 5.0 + 1e-13, 6.0 + 1e-13,
                                      7.0 + 1e-13, 8.0 + 1e-13, 9.0 + 1e-13);
        Mat3<double> D = Mat3<double>(1.0 - 1e-13, 2.0 - 1e-13, 3.0 - 1e-13, 4.0 - 1e-13, 5.0 - 1e-13, 6.0 - 1e-13,
                                      7.0 - 1e-13, 8.0 - 1e-13, 9.0 - 1e-13);
        Mat3<double> E = Mat3<double>(1.0 + 1e-10, 2.0 + 1e-10, 3.0 + 1e-10, 4.0 + 1e-10, 5.0 + 1e-10, 6.0 + 1e-10,
                                      7.0 + 1e-10, 8.0 + 1e-10, 9.0 + 1e-10);
        Mat3<double> F = Mat3<double>(1.0 - 1e-10, 2.0 - 1e-10, 3.0 - 1e-10, 4.0 - 1e-10, 5.0 - 1e-10, 6.0 - 1e-10,
                                      7.0 - 1e-10, 8.0 - 1e-10, 9.0 - 1e-10);

        CHECK(approx_eq(A, B));
        CHECK(approx_eq(A, C));
        CHECK(approx_eq(A, D));
        CHECK(!approx_eq(A, E));
        CHECK(!approx_eq(A, F));
    }
}
} // namespace molcpp