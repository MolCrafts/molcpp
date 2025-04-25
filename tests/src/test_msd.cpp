#include "doctest/doctest.h"
#include "molcpp/compute.hpp"
#include <xtensor/xbuilder.hpp>
#include <xtensor/xmanipulation.hpp>
using namespace molcpp;

TEST_CASE("TestMSD")
{
    auto xyz = xt::xarray<double>{{{1, 0, 0}}};
    auto direct_msd_kernel = MSDCompute(MSDCompute::MSDStyle::DIRECT);
    CHECK(direct_msd_kernel.compute(xyz).get("direct_msd")(0) == 0);

    xyz = xt::repeat(xyz, 10, 0);
    CHECK(direct_msd_kernel.compute(xyz).get("direct_msd")(0) == 0);

    // xyz[:, 0, 0] == np.arange(10)

    xyz = xt::zeros<double>({10, 1, 3});
    xt::view(xyz, xt::all(), 0, 0) = xt::arange(10);
    CHECK(xt::allclose(xt::view(direct_msd_kernel.compute(xyz).get("direct_msd"), xt::all(), 0, 0),
                       xt::pow(xt::arange<double>(10), 2.0)));
}