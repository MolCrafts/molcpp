#include "doctest/doctest.h"
#include "molcpp/space.hpp"
#include "molcpp/types.hpp"

#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xio.hpp>

using namespace molcpp;

TEST_CASE("TestBoxUtils")
{
    SUBCASE("test_is_diagonal")
    {
        CHECK(is_diagonal(Mat3({
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        })));
        CHECK(!is_diagonal(Mat3({
            {1, 0, 1},
            {0, 1, 0},
            {0, 0, 1}
        })));
        CHECK(!is_diagonal(Mat3({
            {1, 0, 0},
            {0, 1, 0},
            {1, 0, 1}
        })));
        CHECK(is_diagonal(Mat3({
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        })));
    }

    SUBCASE("test_is_upper")
    {
        CHECK(is_upper_triangular(Mat3({
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        })));
        CHECK(is_upper_triangular(Mat3({
            {1, 0, 1},
            {0, 1, 0},
            {0, 0, 1}
        })));
        CHECK(!is_upper_triangular(Mat3({
            {1, 0, 0},
            {0, 1, 0},
            {1, 0, 1}
        })));
        CHECK(is_upper_triangular(Mat3({
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        })));
    }
}

TEST_CASE("TestBoxInit")
{

    SUBCASE("test_free")
    {

        auto free = Box();
        CHECK(free.get_style() == Box::Style::FREE);
        CHECK(free.get_lengths() == xt::zeros<double>({3}));
        CHECK(free.get_angles() == Vec3({90., 90., 90.}));
        CHECK(free.get_volume() == 0);
    }

    SUBCASE("test_orthogonal")
    {

        auto matrix = xt::diag(Vec3({10, 11, 12}));
        auto orth = Box(matrix);
        CHECK(orth.get_style() == Box::Style::ORTHOGONAL);
        CHECK(orth.get_lengths() == Vec3({10., 11., 12.}));
        CHECK(orth.get_volume() == 10 * 11 * 12);
    }

    SUBCASE("test_triclinic")
    {
        auto cell = Box::from_lengths_angles({10, 11, 12}, {90, 80, 120});
        CHECK(cell.get_style() == Box::TRICLINIC);
        CHECK(xt::allclose(cell.get_lengths(), Vec3({10, 11, 12}), 1e-4));
        CHECK(xt::allclose(cell.get_angles(), Vec3({90, 80, 120}), 1e-4));
        CHECK(xt::allclose(cell.get_volume(), 1119.9375925598192, 1e-12));

        auto matrix = cell.get_matrix();
        cell = Box(matrix);
        CHECK(cell.get_style() == Box::TRICLINIC);
        CHECK(xt::allclose(cell.get_lengths(), Vec3({10, 11, 12}), 1e-12));
        CHECK(xt::allclose(cell.get_angles(), Vec3({90, 80, 120}), 1e-12));
        CHECK(xt::allclose(cell.get_volume(), 1119.9375925598192, 1e-12));

        matrix = Mat3({
            {26.2553,  0.0000, -4.4843},
            { 0.0000, 11.3176,  0.0000},
            { 0.0000,  0.0000,  11.011}
        });

        cell = Box(matrix);
        CHECK(cell.get_style() == Box::TRICLINIC);
        CHECK(xt::allclose(cell.get_lengths(), Vec3({26.2553, 11.3176, 11.8892}), 1e-4));
        CHECK(xt::allclose(cell.get_angles(), Vec3({90, 112.159, 90}), 1e-4));
    }
}

TEST_CASE("TestErrors")
{
    SUBCASE("test_when_init")
    {
        auto message = "Lengths must >= 0";
        CHECK_THROWS_WITH(Box({-1, 1, 1}), message);
        CHECK_THROWS_WITH(Box({1, -1, 1}), message);
        CHECK_THROWS_WITH(Box({1, 1, -1}), message);

        message = "Angles can not <= 0°";
        CHECK_THROWS_WITH(Box::from_lengths_angles({1, 1, 1}, {-90, 90, 90}), message);
        CHECK_THROWS_WITH(Box::from_lengths_angles({1, 1, 1}, {90, -90, 90}), message);
        CHECK_THROWS_WITH(Box::from_lengths_angles({1, 1, 1}, {90, 90, -90}), message);
        CHECK_THROWS_WITH(Box::from_lengths_angles({1, 1, 1}, {0, 90, 90}), message);
        CHECK_THROWS_WITH(Box::from_lengths_angles({1, 1, 1}, {90, 0, 90}), message);
        CHECK_THROWS_WITH(Box::from_lengths_angles({1, 1, 1}, {90, 90, 0}), message);

        // bad matrix
        CHECK_THROWS_WITH(Box(Mat3({
                              {26.2553,   0.0000, -4.4843},
                              { 0.0000, -11.3176,  0.0000},
                              { 0.0000,   0.0000,  11.011}
        })),
                          "Matrix must be invertible");

        // TODO: Rotated cells are not supported
        // matrix = Mat3({
        //     {0, 0, 3},
        //     {5, 0, 0},
        //     {0, 1, 0}
        // });
        // CHECK_THROWS_WITH(Box(matrix), "orthorhombic cell must have their a vector along x axis, b vector along y
        // "
        //                                "axis and c vector along z axis");
    }

    SUBCASE("setting lengths & angles")
    {
        auto cell = Box();

        auto message = "Lengths must >= 0";
        CHECK_THROWS_WITH(cell.set_lengths({-10, 10, 10}), message);
        CHECK_THROWS_WITH(cell.set_lengths({10, -10, 10}), message);
        CHECK_THROWS_WITH(cell.set_lengths({10, 10, -10}), message);

        message = "Angles can not <= 0°";
        CHECK_THROWS_WITH(cell.set_angles({-90, 90, 90}), message);
        CHECK_THROWS_WITH(cell.set_angles({90, -90, 90}), message);
        CHECK_THROWS_WITH(cell.set_angles({90, 90, -90}), message);
        CHECK_THROWS_WITH(cell.set_angles({0, 90, 90}), message);
        CHECK_THROWS_WITH(cell.set_angles({90, 0, 90}), message);
        CHECK_THROWS_WITH(cell.set_angles({90, 90, 0}), message);

        message = "Angles can not >= 180°";
        CHECK_THROWS_WITH(cell.set_angles({180, 90, 90}), message);
        CHECK_THROWS_WITH(cell.set_angles({90, 180, 90}), message);
        CHECK_THROWS_WITH(cell.set_angles({90, 90, 190}), message);
    }
}

TEST_CASE("TestBoxOperator")
{
    SUBCASE("test_==")
    {
        auto cell = Box({10, 10, 10});
        CHECK(cell == Box({10, 10, 10}));
        CHECK(cell != Box({11, 10, 10}));

        CHECK(cell != Box());
        CHECK(cell != Box::from_lengths_angles({10, 10, 10}, {120, 90, 90}));
    }
}

TEST_CASE("TestBoxSetterGetter")
{
    SUBCASE("test_set_values")
    {
        auto cell = Box();

        cell.set_matrix(xt::diag(Vec3({10, 10, 10})));
        CHECK(cell.get_style() == Box::ORTHOGONAL);

        cell.set_lengths({10, 15, 20});
        CHECK(cell.get_lengths() == Vec3({10, 15, 20}));

        cell.set_lengths_angles({10, 10, 10}, {80, 80, 80});
        CHECK(cell.get_style() == Box::TRICLINIC);

        cell.set_angles({80, 120, 60});
        CHECK(xt::allclose(cell.get_angles(), Vec3({80, 120, 60}), 1e-12));
    }
}

TEST_CASE("TestBoxBoundary")
{
    SUBCASE("test_wrapping_vectors")
    {
        Box infinite;
        Box ortho({10, 11, 12});
        Box triclinic_algo({10, 11, 12});  // same as ortho, but using wrap_tric
        Box triclinic = Box::from_lengths_angles({10, 11, 12}, {90, 90, 80});
        Box tilted = Box::from_lengths_angles({10, 10, 10}, {140, 100, 100});
        auto v = Vec3({22.0, -15.0, 5.8});

        CHECK(infinite.wrap(v) == v);
        CHECK(xt::allclose(ortho.wrap(v), Vec3({2.0, -4.0, 5.8}), 1e-5));
        CHECK(xt::allclose(ortho.wrap(v), triclinic_algo.wrap_tric(v), 1e-5));
        CHECK(xt::allclose(triclinic.wrap(v), Vec3({3.91013, -4.16711, 5.8}), 1e-5));
        std::cout << triclinic.wrap(v) << std::endl;
        CHECK(xt::allclose(tilted.wrap(Vec3({6, 8, -7})), Vec3({4.26352, -0.08481, -1.37679}), 1e-5));
        std::cout << tilted.wrap(Vec3({6, 8, -7})) << std::endl;
    }
}