#include <doctest/doctest.h>
#include "vec3.hpp"

TEST_SUITE("vec3") {
  TEST_CASE("testing the vec3 addition operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    auto v5 = v1 + v2;
    CHECK(v5.getX() == doctest::Approx(5.5));
    CHECK(v5.getY() == doctest::Approx(7.7));
    CHECK(v5.getZ() == doctest::Approx(9.9));

    auto v6 = v3 + v4;
    CHECK(v6.getX() == 5);
    CHECK(v6.getY() == 7);
    CHECK(v6.getZ() == 9);

    auto v7 = v1 + v3;
    CHECK(v7.getX() == doctest::Approx(2.1));
    CHECK(v7.getY() == doctest::Approx(4.2));
    CHECK(v7.getZ() == doctest::Approx(6.3));

    auto v8 = v4 + v2;
    CHECK(v8.getX() == doctest::Approx(8.4));
    CHECK(v8.getY() == doctest::Approx(10.5));
    CHECK(v8.getZ() == doctest::Approx(12.6));

    auto v9 = v1 + 2.2;
    CHECK(v9.getX() == doctest::Approx(3.3));
    CHECK(v9.getY() == doctest::Approx(4.4));
    CHECK(v9.getZ() == doctest::Approx(5.5));

    auto v10 = v3 + 2;
    CHECK(v10.getX() == 3);
    CHECK(v10.getY() == 4);
    CHECK(v10.getZ() == 5);

    auto v11 = 3.1 + v1;
    CHECK(v11.getX() == doctest::Approx(4.2));
    CHECK(v11.getY() == doctest::Approx(5.3));
    CHECK(v11.getZ() == doctest::Approx(6.4));

    auto v12 = 3 + v3;
    CHECK(v12.getX() == 4);
    CHECK(v12.getY() == 5);
    CHECK(v12.getZ() == 6);

    auto v13 = v1 + 2;
    CHECK(v13.getX() == doctest::Approx(3.1));
    CHECK(v13.getY() == doctest::Approx(4.2));
    CHECK(v13.getZ() == doctest::Approx(5.3));

    auto v14 = v3 + 2.2;
    CHECK(v14.getX() == doctest::Approx(3.2));
    CHECK(v14.getY() == doctest::Approx(4.2));
    CHECK(v14.getZ() == doctest::Approx(5.2));

    auto v15 = 3 + v1;
    CHECK(v15.getX() == doctest::Approx(4.1));
    CHECK(v15.getY() == doctest::Approx(5.2));
    CHECK(v15.getZ() == doctest::Approx(6.3));

    auto v16 = 3.1 + v3;
    CHECK(v16.getX() == doctest::Approx(4.1));
    CHECK(v16.getY() == doctest::Approx(5.1));
    CHECK(v16.getZ() == doctest::Approx(6.1));

    auto v17 = v1 + v2 + v3 + v4 + 1.1;
    CHECK(v17.getX() == doctest::Approx(11.6));
    CHECK(v17.getY() == doctest::Approx(15.8));
    CHECK(v17.getZ() == doctest::Approx(20));
  }

  TEST_CASE("testing the vec3 subtraction operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    auto v5 = v1 - v2;
    CHECK(v5.getX() == doctest::Approx(-3.3));
    CHECK(v5.getY() == doctest::Approx(-3.3));
    CHECK(v5.getZ() == doctest::Approx(-3.3));

    auto v6 = v3 - v4;
    CHECK(v6.getX() == -3);
    CHECK(v6.getY() == -3);
    CHECK(v6.getZ() == -3);

    auto v7 = v1 - v3;
    CHECK(v7.getX() == doctest::Approx(0.1));
    CHECK(v7.getY() == doctest::Approx(0.2));
    CHECK(v7.getZ() == doctest::Approx(0.3));

    auto v8 = v4 - v2;
    CHECK(v8.getX() == doctest::Approx(-0.4));
    CHECK(v8.getY() == doctest::Approx(-0.5));
    CHECK(v8.getZ() == doctest::Approx(-0.6));

    auto v9 = v1 - 2.2;
    CHECK(v9.getX() == doctest::Approx(-1.1));
    CHECK(v9.getY() == doctest::Approx(0));
    CHECK(v9.getZ() == doctest::Approx(1.1));

    auto v10 = v3 - 2;
    CHECK(v10.getX() == -1);
    CHECK(v10.getY() == 0);
    CHECK(v10.getZ() == 1);

    auto v11 = 3.1 - v1;
    CHECK(v11.getX() == doctest::Approx(2));
    CHECK(v11.getY() == doctest::Approx(0.9));
    CHECK(v11.getZ() == doctest::Approx(-0.2));

    auto v12 = 3 - v3;
    CHECK(v12.getX() == 2);
    CHECK(v12.getY() == 1);
    CHECK(v12.getZ() == 0);

    auto v13 = v1 - 2;
    CHECK(v13.getX() == doctest::Approx(-0.9));
    CHECK(v13.getY() == doctest::Approx(0.2));
    CHECK(v13.getZ() == doctest::Approx(1.3));

    auto v14 = v3 - 2.2;
    CHECK(v14.getX() == doctest::Approx(-1.2));
    CHECK(v14.getY() == doctest::Approx(-0.2));
    CHECK(v14.getZ() == doctest::Approx(0.8));

    auto v15 = 3 - v1;
    CHECK(v15.getX() == doctest::Approx(1.9));
    CHECK(v15.getY() == doctest::Approx(0.8));
    CHECK(v15.getZ() == doctest::Approx(-0.3));

    auto v16 = 3.1 - v3;
    CHECK(v16.getX() == doctest::Approx(2.1));
    CHECK(v16.getY() == doctest::Approx(1.1));
    CHECK(v16.getZ() == doctest::Approx(0.1));

    auto v17 = -v1;
    CHECK(v17.getX() == doctest::Approx(-1.1));
    CHECK(v17.getY() == doctest::Approx(-2.2));
    CHECK(v17.getZ() == doctest::Approx(-3.3));

    auto v18 = -v3;
    CHECK(v18.getX() == -1);
    CHECK(v18.getY() == -2);
    CHECK(v18.getZ() == -3);
  }

  TEST_CASE("testing the vec3 multiplication operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    auto v5 = v1 * v2;
    CHECK(v5.getX() == doctest::Approx(4.84));
    CHECK(v5.getY() == doctest::Approx(12.1));
    CHECK(v5.getZ() == doctest::Approx(21.78));

    auto v6 = v3 * v4;
    CHECK(v6.getX() == 4);
    CHECK(v6.getY() == 10);
    CHECK(v6.getZ() == 18);

    auto v7 = v1 * v3;
    CHECK(v7.getX() == doctest::Approx(1.1));
    CHECK(v7.getY() == doctest::Approx(4.4));
    CHECK(v7.getZ() == doctest::Approx(9.9));

    auto v8 = v4 * v2;
    CHECK(v8.getX() == doctest::Approx(17.6));
    CHECK(v8.getY() == doctest::Approx(27.5));
    CHECK(v8.getZ() == doctest::Approx(39.6));

    auto v9 = v1 * 2.2;
    CHECK(v9.getX() == doctest::Approx(2.42));
    CHECK(v9.getY() == doctest::Approx(4.84));
    CHECK(v9.getZ() == doctest::Approx(7.26));

    auto v10 = v3 * 2;
    CHECK(v10.getX() == 2);
    CHECK(v10.getY() == 4);
    CHECK(v10.getZ() == 6);

    auto v11 = 3.1 * v1;
    CHECK(v11.getX() == doctest::Approx(3.41));
    CHECK(v11.getY() == doctest::Approx(6.82));
    CHECK(v11.getZ() == doctest::Approx(10.23));

    auto v12 = 3 * v3;
    CHECK(v12.getX() == 3);
    CHECK(v12.getY() == 6);
    CHECK(v12.getZ() == 9);

    auto v13 = v1 * 2;
    CHECK(v13.getX() == doctest::Approx(2.2));
    CHECK(v13.getY() == doctest::Approx(4.4));
    CHECK(v13.getZ() == doctest::Approx(6.6));

    auto v14 = v3 * 2.2;
    CHECK(v14.getX() == doctest::Approx(2.2));
    CHECK(v14.getY() == doctest::Approx(4.4));
    CHECK(v14.getZ() == doctest::Approx(6.6));

    auto v15 = 3 * v1;
    CHECK(v15.getX() == doctest::Approx(3.3));
    CHECK(v15.getY() == doctest::Approx(6.6));
    CHECK(v15.getZ() == doctest::Approx(9.9));

    auto v16 = 3.1 * v3;
    CHECK(v16.getX() == doctest::Approx(3.1));
    CHECK(v16.getY() == doctest::Approx(6.2));
    CHECK(v16.getZ() == doctest::Approx(9.3));

    auto v17 = v1 * v2 * v3 * v4 * 1.1;
    CHECK(v17.getX() == doctest::Approx(21.296));
    CHECK(v17.getY() == doctest::Approx(133.1));
    CHECK(v17.getZ() == doctest::Approx(431.244));
  }

  TEST_CASE("testing the vec3 division operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    auto v5 = v1 / v2;
    CHECK(v5.getX() == doctest::Approx(0.25));
    CHECK(v5.getY() == doctest::Approx(0.4));
    CHECK(v5.getZ() == doctest::Approx(0.5));

    auto v6 = v4 / v3;
    CHECK(v6.getX() == doctest::Approx(4));
    CHECK(v6.getY() == doctest::Approx(2));
    CHECK(v6.getZ() == doctest::Approx(2));

    auto v7 = v1 / v3;
    CHECK(v7.getX() == doctest::Approx(1.1));
    CHECK(v7.getY() == doctest::Approx(1.1));
    CHECK(v7.getZ() == doctest::Approx(1.1));

    auto v8 = v4 / v2;
    CHECK(v8.getX() == doctest::Approx(0.9090909091));
    CHECK(v8.getY() == doctest::Approx(0.9090909091));
    CHECK(v8.getZ() == doctest::Approx(0.9090909091));

    auto v9 = v1 / 2.2;
    CHECK(v9.getX() == doctest::Approx(0.5));
    CHECK(v9.getY() == doctest::Approx(1));
    CHECK(v9.getZ() == doctest::Approx(1.5));

    auto v10 = v3 / 2;
    CHECK(v10.getX() == 0);
    CHECK(v10.getY() == 1);
    CHECK(v10.getZ() == 1);

    auto v11 = 3.1 / v1;
    CHECK(v11.getX() == doctest::Approx(2.8181818181));
    CHECK(v11.getY() == doctest::Approx(1.4090909091));
    CHECK(v11.getZ() == doctest::Approx(0.9393939394));

    auto v12 = 3 / v3;
    CHECK(v12.getX() == 3);
    CHECK(v12.getY() == 1);
    CHECK(v12.getZ() == 1);

    auto v13 = v1 / 2;
    CHECK(v13.getX() == doctest::Approx(0.55));
    CHECK(v13.getY() == doctest::Approx(1.1));
    CHECK(v13.getZ() == doctest::Approx(1.65));

    auto v14 = v3 / 2.2;
    CHECK(v14.getX() == doctest::Approx(0.4545454545));
    CHECK(v14.getY() == doctest::Approx(0.9090909091));
    CHECK(v14.getZ() == doctest::Approx(1.3636363636));

    auto v15 = 3 / v1;
    CHECK(v15.getX() == doctest::Approx(2.7272727273));
    CHECK(v15.getY() == doctest::Approx(1.3636363636));
    CHECK(v15.getZ() == doctest::Approx(0.9090909091));

    auto v16 = 3.1 / v3;
    CHECK(v16.getX() == doctest::Approx(3.1));
    CHECK(v16.getY() == doctest::Approx(1.55));
    CHECK(v16.getZ() == doctest::Approx(1.0333333333));

    auto v17 = v1 / v2 / v3 / v4 / 1.1;
    CHECK(v17.getX() == doctest::Approx(0.0568182));
    CHECK(v17.getY() == doctest::Approx(0.0363636));
    CHECK(v17.getZ() == doctest::Approx(0.0252525));
  }

  TEST_CASE("testing the vec3 addition assignment operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    SUBCASE("") {
      v1 += v2;
      CHECK(v1.getX() == doctest::Approx(5.5));
      CHECK(v1.getY() == doctest::Approx(7.7));
      CHECK(v1.getZ() == doctest::Approx(9.9));
    }

    SUBCASE("") {
      v3 += v4;
      CHECK(v3.getX() == 5);
      CHECK(v3.getY() == 7);
      CHECK(v3.getZ() == 9);
    }

    SUBCASE("") {
      v1 += v3;
      CHECK(v1.getX() == doctest::Approx(2.1));
      CHECK(v1.getY() == doctest::Approx(4.2));
      CHECK(v1.getZ() == doctest::Approx(6.3));
    }

    SUBCASE("") {
      v4 += v2;
      CHECK(v4.getX() == 8);
      CHECK(v4.getY() == 10);
      CHECK(v4.getZ() == 12);
    }

    SUBCASE("") {
      v1 += 2.2;
      CHECK(v1.getX() == doctest::Approx(3.3));
      CHECK(v1.getY() == doctest::Approx(4.4));
      CHECK(v1.getZ() == doctest::Approx(5.5));
    }

    SUBCASE("") {
      v3 += 2;
      CHECK(v3.getX() == 3);
      CHECK(v3.getY() == 4);
      CHECK(v3.getZ() == 5);
    }
  }

  TEST_CASE("testing the vec3 subtraction assignment operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    SUBCASE("") {
      v1 -= v2;
      CHECK(v1.getX() == doctest::Approx(-3.3));
      CHECK(v1.getY() == doctest::Approx(-3.3));
      CHECK(v1.getZ() == doctest::Approx(-3.3));
    }

    SUBCASE("") {
      v3 -= v4;
      CHECK(v3.getX() == -3);
      CHECK(v3.getY() == -3);
      CHECK(v3.getZ() == -3);
    }

    SUBCASE("") {
      v1 -= v3;
      CHECK(v1.getX() == doctest::Approx(0.1));
      CHECK(v1.getY() == doctest::Approx(0.2));
      CHECK(v1.getZ() == doctest::Approx(0.3));
    }

    SUBCASE("") {
      v4 -= v2;
      CHECK(v4.getX() == 0);
      CHECK(v4.getY() == 0);
      CHECK(v4.getZ() == 0);
    }

    SUBCASE("") {
      v1 -= 2.2;
      CHECK(v1.getX() == doctest::Approx(-1.1));
      CHECK(v1.getY() == doctest::Approx(0));
      CHECK(v1.getZ() == doctest::Approx(1.1));
    }

    SUBCASE("") {
      v3 -= 2;
      CHECK(v3.getX() == -1);
      CHECK(v3.getY() == 0);
      CHECK(v3.getZ() == 1);
    }
  }

  TEST_CASE("testing the vec3 multiplication assignment operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    SUBCASE("") {
      v1 *= v2;
      CHECK(v1.getX() == doctest::Approx(4.84));
      CHECK(v1.getY() == doctest::Approx(12.1));
      CHECK(v1.getZ() == doctest::Approx(21.78));
    }

    SUBCASE("") {
      v3 *= v4;
      CHECK(v3.getX() == 4);
      CHECK(v3.getY() == 10);
      CHECK(v3.getZ() == 18);
    }

    SUBCASE("") {
      v1 *= v3;
      CHECK(v1.getX() == doctest::Approx(1.1));
      CHECK(v1.getY() == doctest::Approx(4.4));
      CHECK(v1.getZ() == doctest::Approx(9.9));
    }

    SUBCASE("") {
      v4 *= v2;
      CHECK(v4.getX() == 17);
      CHECK(v4.getY() == 27);
      CHECK(v4.getZ() == 39);
    }

    SUBCASE("") {
      v1 *= 2.2;
      CHECK(v1.getX() == doctest::Approx(2.42));
      CHECK(v1.getY() == doctest::Approx(4.84));
      CHECK(v1.getZ() == doctest::Approx(7.26));
    }

    SUBCASE("") {
      v3 *= 2;
      CHECK(v3.getX() == 2);
      CHECK(v3.getY() == 4);
      CHECK(v3.getZ() == 6);
    }
  }

  TEST_CASE("testing the vec3 division assignment operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(4.4, 5.5, 6.6);
    molcpp::Vec3<int> v3(1, 2, 3);
    molcpp::Vec3<int> v4(4, 5, 6);

    SUBCASE("") {
      v1 /= v2;
      CHECK(v1.getX() == doctest::Approx(0.25));
      CHECK(v1.getY() == doctest::Approx(0.4));
      CHECK(v1.getZ() == doctest::Approx(0.5));
    }

    SUBCASE("") {
      v4 /= v3;
      CHECK(v4.getX() == 4);
      CHECK(v4.getY() == 2);
      CHECK(v4.getZ() == 2);
    }

    SUBCASE("") {
      v1 /= v3;
      CHECK(v1.getX() == doctest::Approx(1.1));
      CHECK(v1.getY() == doctest::Approx(1.1));
      CHECK(v1.getZ() == doctest::Approx(1.1));
    }

    SUBCASE("") {
      v3 /= v1;
      CHECK(v3.getX() == 0);
      CHECK(v3.getY() == 0);
      CHECK(v3.getZ() == 0);
    }

    SUBCASE("") {
      v1 /= 2.2;
      CHECK(v1.getX() == doctest::Approx(0.5));
      CHECK(v1.getY() == doctest::Approx(1));
      CHECK(v1.getZ() == doctest::Approx(1.5));
    }

    SUBCASE("") {
      v3 /= 2;
      CHECK(v3.getX() == 0);
      CHECK(v3.getY() == 1);
      CHECK(v3.getZ() == 1);
    }
  }

  TEST_CASE("testing the vec3 uniary operator") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<int> v2(1, 2, 3);

    SUBCASE("") {
      v1 = -v1;
      CHECK(v1.getX() == doctest::Approx(-1.1));
      CHECK(v1.getY() == doctest::Approx(-2.2));
      CHECK(v1.getZ() == doctest::Approx(-3.3));
    }

    SUBCASE("") {
      v2 = -v2;
      CHECK(v2.getX() == -1);
      CHECK(v2.getY() == -2);
      CHECK(v2.getZ() == -3);
    }
  }

  TEST_CASE("testing the vec3 equility") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v2(1.1, 2.2, 3.3);
    molcpp::Vec3<double> v3(1.1, 2.2, 3.4);
    molcpp::Vec3<int> v4(1, 2, 3);
    molcpp::Vec3<int> v5(1, 2, 3);
    molcpp::Vec3<int> v6(1, 2, 4);

    CHECK(v1 == v2);
    CHECK(v4 == v5);
    CHECK(v1 != v3);
    CHECK(v4 != v6);
  }

  TEST_CASE("testing the vec3 function norm") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<int> v2(1, 2, 3);

    CHECK(v1.norm() == doctest::Approx(4.1158231255));
    CHECK(v2.norm() == doctest::Approx(3.7416573868));
  }

  TEST_CASE("testing the vec3 function product") {
    molcpp::Vec3<double> v1(1.1, 2.2, 3.3);
    molcpp::Vec3<int> v2(1, 2, 3);

    CHECK(v1.product() == doctest::Approx(7.986));
    CHECK(v2.product() == 6);
  }
}