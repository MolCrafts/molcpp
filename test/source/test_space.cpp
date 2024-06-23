#include <initializer_list>
#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xio.hpp>
#include "doctest/doctest.h"
#include "molcpp/space.hpp"

using namespace molcpp;

TEST_CASE("TestBoxInit")
{

    SUBCASE("test_infinite") {

        auto infinite = Box();
        CHECK(infinite.get_style() == Box::Style::INFINITE);
        CHECK(infinite.get_lengths() == xt::zeros<double>({3}));
        CHECK(infinite.get_angles() == xt::xarray<double>({90., 90., 90.}));
        CHECK(infinite.get_volume() == 0);

        auto matrix = xt::zeros<double>({3, 3});
        CHECK(Box(matrix) == Box());
        CHECK(Box::set_lengths_angles({0, 0, 0}, {90, 90, 90}) == Box());
        // TODO: set_lengths_tilts
    }

    SUBCASE("test_orthogonal") {

        auto matrix = xt::diag(xt::xarray<double>({10, 11, 12}));
        auto orth = Box(matrix);
        CHECK(orth.get_style() == Box::Style::ORTHOGONAL);
        std::cout << orth.get_matrix() << std::endl;
        std::cout << xt::diag(orth.get_matrix()) << std::endl;
        CHECK(orth.get_lengths() == xt::xarray<double>({10., 11., 12.}));
        CHECK(orth.get_volume() == 10 * 11 * 12);

    }
}
