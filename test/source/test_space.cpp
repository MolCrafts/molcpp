#include <catch2/catch_test_macros.hpp>
#include <xtensor/xarray.hpp>

#include "molcpp/space.hpp"

namespace molcpp
{

TEST_CASE("Test Box", "test_box_init")
{
    auto box = Box();
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);
    box = Box({10.0, 10.0, 10.0});
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);
    box = Box(xt::xarray<double>({10.0, 10.0, 10.0}));
    CHECK(box.get_style() == Box::Style::ORTHORHOMBIC);
}

} // namespace molcpp