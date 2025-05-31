#ifndef MOLCPP_BLOCK_MAP_HPP
#define MOLCPP_BLOCK_MAP_HPP

#include "block.hpp"
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace molcpp {

class BlockMap {
private:
    std::unordered_map<std::string, Block> blocks_; // Map of named Blocks

public:
    // Add a Block to the BlockMap
    void add_block(const std::string& name, const Block& block) {
        if (blocks_.find(name) != blocks_.end()) {
            throw std::invalid_argument("Block with name " + name + " already exists.");
        }
        blocks_[name] = block;
    }

    // Access a Block by name
    Block& get_block(const std::string& name) {
        if (blocks_.find(name) == blocks_.end()) {
            throw std::out_of_range("Block with name " + name + " does not exist.");
        }
        return blocks_[name];
    }

    const Block& get_block(const std::string& name) const {
        if (blocks_.find(name) == blocks_.end()) {
            throw std::out_of_range("Block with name " + name + " does not exist.");
        }
        return blocks_.at(name);
    }

    // Remove a Block by name
    void remove_block(const std::string& name) {
        if (blocks_.find(name) == blocks_.end()) {
            throw std::out_of_range("Block with name " + name + " does not exist.");
        }
        blocks_.erase(name);
    }

    // List all Block names
    std::vector<std::string> block_names() const {
        std::vector<std::string> names;
        for (const auto& pair : blocks_) {
            names.push_back(pair.first);
        }
        return names;
    }

    // Perform a selection operation on all Blocks
    BlockMap sel(const std::unordered_map<std::string, int>& selectors) const {
        BlockMap result;
        for (const auto& [name, block] : blocks_) {
            result.add_block(name, block.sel(selectors));
        }
        return result;
    }

    // Perform an index selection operation on all Blocks
    BlockMap isel(const std::unordered_map<std::string, size_t>& indexers) const {
        BlockMap result;
        for (const auto& [name, block] : blocks_) {
            result.add_block(name, block.isel(indexers));
        }
        return result;
    }

    // Access metadata for the entire BlockMap
    std::unordered_map<std::string, std::string> attrs;
};

} // namespace molcpp

#endif // MOLCPP_BLOCK_MAP_HPP
