#include "doctest/doctest.h"
#include "molcpp/block.hpp"

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

using namespace molcpp;

TEST_CASE("TestBlock") {
    SUBCASE("test_creation") {
        // Create a Block with data and coordinates
        xt::xarray<double> data = {{1.0, 2.0}, {3.0, 4.0}};
        Block block = Block::from_data(data, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        // Check data and coordinates
        CHECK(block.data() == data);
        CHECK(block.coords("x") == xt::xarray<int>{0, 1});
        CHECK(block.coords("y") == xt::xarray<int>{0, 1});
    }

    SUBCASE("test_selection") {
        // Create a Block
        xt::xarray<double> data = {{1.0, 2.0}, {3.0, 4.0}};
        Block block = Block::from_data(data, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        // Select data by coordinate
        auto selected = block.sel({{"x", 1}});
        CHECK(selected.data() == xt::xarray<double>{3.0, 4.0});

        // Select data by index
        auto indexed = block.isel({{"y", 0}});
        CHECK(indexed.data() == xt::xarray<double>{1.0, 3.0});
    }

    SUBCASE("test_math_operations") {
        // Create two Blocks
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        // Perform addition
        auto result = block1 + block2;
        CHECK(result.data() == xt::xarray<double>{{6.0, 8.0}, {10.0, 12.0}});

        // Perform subtraction
        auto diff = block1 - block2;
        CHECK(diff.data() == xt::xarray<double>{{-4.0, -4.0}, {-4.0, -4.0}});
    }

    SUBCASE("test_metadata") {
        // Create a Block and set metadata
        Block block = Block::from_data(xt::xarray<double>{{1.0, 2.0}}, {"x"}, {xt::xarray<int>{0, 1}});
        block.attrs()["description"] = "Test Block";
        block.attrs()["unit"] = "m/s";

        // Check metadata
        CHECK(block.attrs()["description"] == "Test Block");
        CHECK(block.attrs()["unit"] == "m/s");
    }

    SUBCASE("test_aggregation") {
        // Create a Block
        xt::xarray<double> data = {{1.0, 2.0}, {3.0, 4.0}};
        Block block = Block::from_data(data, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        // Perform aggregation
        auto sum = block.sum("x");
        CHECK(sum.data() == xt::xarray<double>{4.0, 6.0});

        auto mean = block.mean("y");
        CHECK(mean.data() == xt::xarray<double>{1.5, 3.5});
    }

    SUBCASE("test_transpose") {
        // Create a Block
        xt::xarray<double> data = {{1.0, 2.0}, {3.0, 4.0}};
        Block block = Block::from_data(data, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        // Transpose the Block
        auto transposed = block.transpose({"y", "x"});
        CHECK(transposed.data() == xt::xarray<double>{{1.0, 3.0}, {2.0, 4.0}});
    }

    SUBCASE("test_broadcasting") {
        // Create two Blocks
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {10.0, 20.0};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"y"}, {xt::xarray<int>{0, 1}});

        // Perform broadcasting addition
        auto result = block1 + block2;
        CHECK(result.data() == xt::xarray<double>{{11.0, 22.0}, {13.0, 24.0}});
    }
}
