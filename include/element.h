#pragma once

#include <any>
#include <initializer_list>
#include <map>
#include <vector>

/**
 * @brief A dictionary class for C++17 that mimics Python's dict behavior.
 * The keys and values can be of any type.
 */
class Dict {
public:
    /**
     * @brief Default constructor
     */
    Dict() = default;

    /**
     * @brief Constructor with an initializer list
     * @param initList The initializer list
     */
    Dict(std::initializer_list<std::pair<std::any, std::any>> initList) {
        for (const auto& pair : initList) {
            data[pair.first] = pair.second;
        }
    }

    /**
     * @brief Get the value associated with the specified key, or a default value.
     * @param key The key to look for
     * @param defaultValue The default value to return if the key is not found
     * @return The value associated with the key or the default value
     */
    std::any get(const std::any& key, const std::any& defaultValue = std::any()) const {
        auto it = data.find(key);
        return it != data.end() ? it->second : defaultValue;
    }

    /**
     * @brief Set the default value for a key if it's not already set.
     * @param key The key to set
     * @param defaultValue The default value to set if the key is not found
     * @return The value associated with the key
     */
    std::any setdefault(const std::any& key, const std::any& defaultValue) {
        auto[it, inserted] = data.try_emplace(key, defaultValue);
        return it->second;
    }

    /**
     * @brief Gets the list of keys in the dictionary.
     * @return A std::vector containing the keys
     */
    std::vector<std::any> keys() const {
        std::vector<std::any> keys;
        for (const auto& pair : data) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    /**
     * @brief Gets the list of values in the dictionary.
     * @return A std::vector containing the values
     */
    std::vector<std::any> values() const {
        std::vector<std::any> values;
        for (const auto& pair : data) {
            values.push_back(pair.second);
        }
        return values;
    }

    /**
     * @brief Update the dictionary with the key-value pairs from another dictionary.
     * @param other The other dictionary
     */
    void update(const Dict& other) {
        for (const auto& pair : other.data) {
            data[pair.first] = pair.second;
        }
    }

    /**
     * @brief Access an element in the dictionary.
     * @param key The key to access
     * @return A reference to the value associated with the key
     */
    std::any& operator[](const std::any& key) {
        return data[key];
    }

    /**
     * @brief Get the number of elements in the dictionary.
     * @return The number of elements
     */
    size_t size() const {
        return data.size();
    }

    /**
     * @brief Check if the dictionary is empty.
     * @return true if the dictionary is empty, false otherwise
     */
    bool empty() const {
        return data.empty();
    }

    /**
     * @brief Clear the contents of the dictionary.
     */
    void clear() {
        data.clear();
    }

private:
    std::map<std::any, std::any> data;
};