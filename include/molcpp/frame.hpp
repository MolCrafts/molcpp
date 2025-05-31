#ifndef MOLCPP_FRAME_HPP
#define MOLCPP_FRAME_HPP

#include "molcpp/block_map.hpp"
#include <string>
#include <unordered_map>

namespace molcpp {

class Frame {
private:
    BlockMap block_map;
    std::unordered_map<std::string, std::string> metadata;

public:
    // Add a block to the frame
    void add_block(const std::string& name, const Block& block) {
        block_map.add_block(name, block);
    }

    // Remove a block from the frame
    void remove_block(const std::string& name) {
        block_map.remove_block(name);
    }

    // Retrieve a block by name
    const Block& get_block(const std::string& name) const {
        return block_map.get_block(name);
    }

    // List all block names
    std::vector<std::string> block_names() const {
        return block_map.block_names();
    }

    // Selection by coordinate
    Frame sel(const std::unordered_map<std::string, int>& coords) const {
        Frame selected_frame;
        for (const auto& name : block_map.block_names()) {
            selected_frame.add_block(name, block_map.get_block(name).sel(coords));
        }
        return selected_frame;
    }

    // Selection by index
    Frame isel(const std::unordered_map<std::string, int>& indices) const {
        Frame indexed_frame;
        for (const auto& name : block_map.block_names()) {
            indexed_frame.add_block(name, block_map.get_block(name).isel(indices));
        }
        return indexed_frame;
    }

    // Metadata access
    std::unordered_map<std::string, std::string>& attrs() {
        return metadata;
    }

    const std::unordered_map<std::string, std::string>& attrs() const {
        return metadata;
    }

    // Overload operator[] to access blocks by name
    Block& operator[](const std::string& name) {
        return block_map.get_block(name);
    }

    const Block& operator[](const std::string& name) const {
        return block_map.get_block(name);
    }
};

} // namespace molcpp

#endif // MOLCPP_FRAME_HPP
