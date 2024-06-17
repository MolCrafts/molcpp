#include <catch2/catch_test_macros.hpp>
#include <initializer_list>
#include <xtensor/xarray.hpp>

#include "molcore/space.hpp"
#include "xtensor/xio.hpp"
#include <iostream>

namespace molcore
{

TEST_CASE("Test Box", "test_box_init")
{

    const double box_length = 10.0;

    auto box = Box();
    CHECK(box.get_style() == Box::Style::INFINITE);

    std::initializer_list<std::initializer_list<double>> orth_matrix = {
        {box_length,        0.0,        0.0},
        {       0.0, box_length,        0.0},
        {       0.0,        0.0, box_length}
    };
    box = Box(orth_matrix);
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);

    auto xarray = xt::xarray<double>(orth_matrix);
    box = Box(xarray);
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);

    auto xtensor_fixed = xt::xtensor_fixed<double, xt::xshape<3, 3>>(xarray);
    box = Box(xtensor_fixed);
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);

    auto xtensor = xt::xtensor<double, 2>(xarray);
    box = Box(xtensor);
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);

    xt::xarray<double> lengths = {box_length, box_length, box_length};
    xt::xarray<double> orth_angles = {90.0, 90.0, 90.0};
    xt::xarray<double> tric_angles = {60.0, 60.0, 60.0};
    xt::xarray<double> tilts = {1.0, 2.0, 3.0};
    box = Box::set_lengths_angles(lengths, orth_angles);
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);
    box = Box::set_lengths_angles(lengths, tric_angles);
    CHECK(box.get_style() == Box::Style::TRICLINIC);
    // box = Box::set_lengths_tilts(lengths, tilts);
}

} // namespace molcore