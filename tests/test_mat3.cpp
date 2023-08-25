#include <doctest/doctest.h>
#include "approx.hpp"
#include "vec3.hpp"
#include "mat3.hpp"

namespace molcpp {
TEST_SUITE("mat3") {
  // TEST_CASE("Negate Matrix") {
  //   Mat3<double> A = Mat3<double>(2, 4, 9, 1, -67, 8, 9, 78.9, 65);

  //   Mat3<double> B = Mat3<double>(-2, -4, -9, -1, 67, -8, -9, -78.9, -65);

  //   CHECK(A == (-B));
  //   CHECK(B == (-A));
  // }

  TEST_CASE("Matrix-Scalar Addition")
  {
    Mat3<double> A = Mat3<double>(2, 4, 9, 1, -67, 8, 9, 78.9, 65);
    
    auto B = A + 0;
  }

  // TEST_CASE("Matrix-Matrix Addition") {
  //   auto A = Mat3<double>(2, 4, 9, 1, -67, 8, 9, 78.9, 65);
  //   auto Z = Mat3<double>::zero();
  //   CHECK((A + Z) == A);
  //   CHECK((Z + A) == A);
  //   CHECK((A - Z) == A);
  //   CHECK((Z - A) == (-A));

  //   auto C = Mat3<double>(2, 4, 9, 1, -6, 8, -3, 9, 5);

  //   auto D = Mat3<double>(4, 8, 18, 2, -73, 16, 6, 87.9, 70);

  //   auto E = Mat3<double>(0, 0, 0, 0, -61, 0, 12, 69.9, 60);

  //   CHECK((A + C) == D);
  //   CHECK((C + A) == D);
  //   CHECK((A - C) == E);
  //   CHECK((C - A) == (-E));

  //   CHECK((A += C) == D);
  //   CHECK(A == D);
  //   CHECK((A -= (C + C)) == E);
  //   CHECK(A == E);
  // }

  // TEST_CASE("Matrix-Scalar Multiplication and Division") {
  //   auto A = Mat3<double>(2, 4, 9, 1, -67, 8, 9, 78.9, 65);
  //   CHECK(A * 1 == A);
  //   CHECK(1 * A == A);
  //   CHECK(A / 1 == A);

  //   auto C = Mat3<double>(4, 8, 18, 2, -134, 16, 18, 157.8, 130);

  //   auto D = Mat3<double>(1, 2, 4.5, 0.5, -33.5, 4, 4.5, 39.45, 32.5);

  //   CHECK(A * 2 == C);
  //   CHECK(2 * A == C);
  //   CHECK(A / 2 == D);

  //   CHECK((A *= 2) == C);
  //   CHECK(A == C);
  //   CHECK((A /= 4) == D);
  //   CHECK(A == D);
  // }

  // TEST_CASE("Matrix-Matrix Multiplications") {
  //   auto A = Mat3<double>(2, 4, 9, 1, -67, 8, 9, 78.9, 65);
  //   auto I = Mat3<double>::unit();
  //   CHECK((A.dot(I)) == A);
  //   CHECK((I.dot(A)) == A);

  //   auto C = Mat3<double>(2, 4, 9, 1, -6, 8, -3, 9, 5);
  //   auto D = Mat3<double>(7, -1, 0, 2, 0, 4, 2, 8, -6);

  //   auto E = Mat3<double>(40, 70, -38, 11, 63, -72, 7, 43, 6);
  //   auto F = Mat3<double>(13, 34, 55, -8, 44, 38, 30, -94, 52);

  //   CHECK((C.dot(D)) == E);
  //   CHECK((D.dot(C)) == F);
  // }

  // TEST_CASE("Matrix-Vector Multiplications") {
  //   auto A = Mat3<double>(2, 4, 9, 1, -6, 8, -3, 9, 5);
  //   auto I = Mat3<double>::unit();
  //   auto v = Vec3<double>(7, -9, 2);

  //   CHECK((I.dot(v)) == v);
  //   CHECK((A.dot(v)) == Vec3<double>(-4, 77, -92));
  // }

  // TEST_CASE("Inversion") {
  //   auto A = Mat3<double>(10, 2, 5, -1, 12, 8, 0.2, 8, 16);

  //   CHECK(A.determinant() == 1263.2);

  //   auto B = A.invert();
  //   CHECK(approx_eq(B,
  //                   Mat3<double>(0.10132995566814439, 0.00633312222925902, -0.03483217226092463,
  //                                 0.01393286890436985, 0.12587080430652312, -0.06728942368587713,
  //                                 -0.00823305889803673, -0.063014566181127288, 0.09658011399620011),
  //                   1e-9));

  //   auto I = Mat3<double>::unit();
  //   CHECK(approx_eq((A.dot(B)), I, 1e-9));

  //   CHECK_THROWS_MESSAGE(Mat3<double>::zero().invert(), "this matrix is not invertible");
  // }

  // TEST_CASE("Transposition") {
  //   auto A = Mat3<double>(3, 0, 5, 1, 2, 6, 2, 0, 1);
  //   auto transposed = Mat3<double>(3, 1, 2, 0, 2, 0, 5, 6, 1);
  //   CHECK(A.transpose() == transposed);
  // }
}}