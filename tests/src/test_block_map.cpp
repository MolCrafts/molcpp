#include "doctest/doctest.h"
#include "molcpp/block_map.hpp"
#include "molcpp/block.hpp"

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

using namespace molcpp;

TEST_CASE("TestBlockMap") {
    SUBCASE("test_add_and_get_block") {
        // Create a BlockMap and add Blocks
        BlockMap block_map;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        block_map.add_block("block1", block1);
        block_map.add_block("block2", block2);

        // Retrieve and check Blocks
        CHECK(block_map.get_block("block1").data() == data1);
        CHECK(block_map.get_block("block2").data() == data2);
    }

    SUBCASE("test_remove_block") {
        // Create a BlockMap and add a Block
        BlockMap block_map;
        xt::xarray<double> data = {{1.0, 2.0}, {3.0, 4.0}};
        Block block = Block::from_data(data, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        block_map.add_block("block", block);
        CHECK(block_map.get_block("block").data() == data);

        // Remove the Block
        block_map.remove_block("block");
        CHECK_THROWS_AS(block_map.get_block("block"), std::out_of_range);
    }

    SUBCASE("test_block_names") {
        // Create a BlockMap and add Blocks
        BlockMap block_map;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        block_map.add_block("block1", block1);
        block_map.add_block("block2", block2);

        // Check block names
        auto names = block_map.block_names();
        CHECK(std::find(names.begin(), names.end(), "block1") != names.end());
        CHECK(std::find(names.begin(), names.end(), "block2") != names.end());
    }

    SUBCASE("test_sel_and_isel") {
        // Create a BlockMap and add Blocks
        BlockMap block_map;
        xt::xarray<double> data1 = {{1.0, 2.0}, {3.0, 4.0}};
        xt::xarray<double> data2 = {{5.0, 6.0}, {7.0, 8.0}};
        Block block1 = Block::from_data(data1, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});
        Block block2 = Block::from_data(data2, {"x", "y"}, {xt::xarray<int>{0, 1}, xt::xarray<int>{0, 1}});

        block_map.add_block("block1", block1);
        block_map.add_block("block2", block2);

        // Perform selection
        auto selected = block_map.sel({{"x", 1}});
        CHECK(selected.get_block("block1").data() == xt::xarray<double>{3.0, 4.0});
        CHECK(selected.get_block("block2").data() == xt::xarray<double>{7.0, 8.0});

        // Perform index selection
        auto indexed = block_map.isel({{"y", 0}});
        CHECK(indexed.get_block("block1").data() == xt::xarray<double>{1.0, 3.0});
        CHECK(indexed.get_block("block2").data() == xt::xarray<double>{5.0, 7.0});
    }

    SUBCASE("test_metadata") {
        // Create a BlockMap and set metadata
        BlockMap block_map;
        block_map.attrs["description"] = "Test BlockMap";
        block_map.attrs["version"] = "1.0";

        // Check metadata
        CHECK(block_map.attrs["description"] == "Test BlockMap");
        CHECK(block_map.attrs["version"] == "1.0");
    }
}
