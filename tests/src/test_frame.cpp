#include "doctest/doctest.h"
#include "molcpp/frame.hpp"
#include "molcpp/block_map.hpp"
#include "molcpp/block.hpp"

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

using namespace molcpp;

TEST_CASE("TestFrame") {
    SUBCASE("test_add_and_get_block") {
        // Create a Frame and add Blocks
        Frame frame;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        frame.add_block("block1", block1);
        frame.add_block("block2", block2);

        // Retrieve and check Blocks
        CHECK(frame.get_block("block1").data() == data1);
        CHECK(frame.get_block("block2").data() == data2);
    }

    SUBCASE("test_remove_block") {
        // Create a Frame and add a Block
        Frame frame;
        xt::xarray<double> data = {{1.0, 2.0}, {3.0, 4.0}};
        Block block = Block::from_data(data, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        frame.add_block("block", block);
        CHECK(frame.get_block("block").data() == data);

        // Remove the Block
        frame.remove_block("block");
        CHECK_THROWS_AS(frame.get_block("block"), std::out_of_range);
    }

    SUBCASE("test_block_names") {
        // Create a Frame and add Blocks
        Frame frame;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        frame.add_block("block1", block1);
        frame.add_block("block2", block2);

        // Check block names
        auto names = frame.block_names();
        CHECK(std::find(names.begin(), names.end(), "block1") != names.end());
        CHECK(std::find(names.begin(), names.end(), "block2") != names.end());
    }

    SUBCASE("test_sel_and_isel") {
        // Create a Frame and add Blocks
        Frame frame;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        frame.add_block("block1", block1);
        frame.add_block("block2", block2);

        // Perform selection
        auto selected = frame.sel({{"x", 1}});
        CHECK(selected.get_block("block1").data() == xt::xarray<double>{3.0, 4.0});
        CHECK(selected.get_block("block2").data() == xt::xarray<double>{7.0, 8.0});

        // Perform index selection
        auto indexed = frame.isel({{"y", 0}});
        CHECK(indexed.get_block("block1").data() == xt::xarray<double>{1.0, 3.0});
        CHECK(indexed.get_block("block2").data() == xt::xarray<double>{5.0, 7.0});
    }

    SUBCASE("test_metadata") {
        // Create a Frame and set metadata
        Frame frame;
        frame.attrs["description"] = "Test Frame";
        frame.attrs["version"] = "1.0";

        // Check metadata
        CHECK(frame.attrs["description"] == "Test Frame");
        CHECK(frame.attrs["version"] == "1.0");
    }

    SUBCASE("test_operator_access") {
        // Create a Frame and add Blocks
        Frame frame;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        frame.add_block("block1", block1);
        frame.add_block("block2", block2);

        // Access blocks using operator[]
        CHECK(frame["block1"].data() == data1);
        CHECK(frame["block2"].data() == data2);
    }
}
