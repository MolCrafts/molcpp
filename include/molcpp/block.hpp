#ifndef MOLCPP_BLOCK_HPP
#define MOLCPP_BLOCK_HPP

#include <xframe/xvariable.hpp>
#include <xtensor/xarray.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace molcpp {

class Block {
private:
    xframe::xvariable<double> data_; // Core data structure
    std::unordered_map<std::string, std::string> attrs_; // Metadata

public:
    // Default constructor
    Block() = default;

    // Static factory method to create a Block from data and coordinates
    static Block from_data(const xt::xarray<double>& data,
                           const std::vector<std::string>& dims,
                           const std::vector<xt::xarray<int>>& coords) {
        if (dims.size() != coords.size()) {
            throw std::invalid_argument("Number of dimensions and coordinates must match.");
        }

        // Create coordinate map
        xframe::coordinate_map<std::string> coord_map;
        for (size_t i = 0; i < dims.size(); ++i) {
            coord_map[dims[i]] = coords[i];
        }

        // Create xvariable
        xframe::xvariable<double> xvar(data, coord_map);

        // Initialize Block
        Block block;
        block.data_ = xvar;
        return block;
    }

    // Access data
    const xt::xarray<double>& data() const {
        return data_.data();
    }

    // Access coordinates
    const xt::xarray<int>& coords(const std::string& dim) const {
        if (!data_.coordinates().contains(dim)) {
            throw std::out_of_range("Dimension " + dim + " does not exist.");
        }
        return data_.coordinates().at(dim);
    }

    // Access metadata
    std::unordered_map<std::string, std::string>& attrs() {
        return attrs_;
    }

    const std::unordered_map<std::string, std::string>& attrs() const {
        return attrs_;
    }

    // Selection by coordinate
    Block sel(const std::unordered_map<std::string, int>& selectors) const {
        auto selected = data_.select(selectors);
        Block result;
        result.data_ = selected;
        return result;
    }

    // Selection by index
    Block isel(const std::unordered_map<std::string, size_t>& indexers) const {
        auto indexed = data_.isel(indexers);
        Block result;
        result.data_ = indexed;
        return result;
    }

    // Arithmetic operations
    Block operator+(const Block& other) const {
        Block result;
        result.data_ = data_ + other.data_;
        return result;
    }

    Block operator-(const Block& other) const {
        Block result;
        result.data_ = data_ - other.data_;
        return result;
    }
};

} // namespace molcpp

#endif // MOLCPP_BLOCK_HPP
