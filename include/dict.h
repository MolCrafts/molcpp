#pragma once

#include "error.h"
#include <any>
#include <error.h>
#include <initializer_list>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace molcpp {

/**
 * A dictionary class that mimics Python's dict.
 * The keys are unique strings and the values can be of any type.
 */
class Dict {
private:
  std::unordered_map<std::string, std::any> data;

public:
  Dict() = default;

  Dict(std::initializer_list<std::pair<std::string, std::any>> initList) {
    for (const auto &pair : initList) {
      data[pair.first] = pair.second;
    }
  }

  /**
   * Get the value associated with a key.
   * Throws std::out_of_range if key is not present.
   */
  template <typename T> T get(const std::string &key) {
    auto it = data.find(key);
    if (it == data.end()) {
      throw std::out_of_range("Key '" + key + "' not found");
    }
    // if value's type is char, return as std::string
    if (typeid(T) == typeid(std::string) && it->second.type() == typeid(char)) {
        return std::string(1, std::any_cast<char>(it->second));
    } else if (typeid(T) == it->second.type()) {
      return std::any_cast<T>(it->second);
    } else {
      throw TypeError("Invalid type for key '" + key + "'");
    }
  }

    /**
     * Get the value associated with a key, or a default value.
     */
    template <typename T>
    T get(const std::string &key, const T &default_value) {
      try {
        return get<T>(key);
      } catch (const std::out_of_range &) {
        return default_value;
      } catch (const std::bad_any_cast &) {
        throw TypeError("Invalid type for key '" + key + "'");
      }
    }

    /**
     * Set a default value for a key if it is not already present.
     */
    template <typename T>
    T setdefault(const std::string &key, const T &default_value) {
      try {
        return get<T>(key);
      } catch (const std::out_of_range &) {
        data[key] = default_value;
        return default_value;
      } catch (const std::bad_any_cast &) {
        throw TypeError("Type of default_value not match type of key (type of "
                        "default_value is `" +
                        std::string(typeid(default_value).name()) +
                        "` and key is `" +
                        std::string(data[key].type().name()) + "`)");
      }
    }

    /**
     * Get a vector of all the keys in the dictionary.
     */
    std::vector<std::string> keys() const {
      std::vector<std::string> keys;
      for (const auto &pair : data) {
        keys.push_back(pair.first);
      }
      return keys;
    }

    /**
     * Get a vector of all the values in the dictionary.
     * Note: This method returns a vector of std::any objects.
     * You must cast them to the correct type before use.
     */
    std::vector<std::any> values() const {
      std::vector<std::any> values;
      for (const auto &pair : data) {
        values.push_back(pair.second);
      }
      return values;
    }

    /**
     * Update the dictionary with the contents of another dictionary.
     */
    void update(const Dict &other) {
      for (const auto &pair : other.data) {
        data[pair.first] = pair.second;
      }
    }

    /**
     * Operator overload for accessing dictionary values.
     * Note: This will insert the key into the dictionary if it is not present.
     */
    std::any &operator[](const std::string &key) { return data[key]; }

    /**
     * @brief Get size of dictionary
     * 
     */
    size_t size() const { return data.size(); }

    /**
     * @brief Check if dictionary is empty
     * 
     */
    bool empty() const { return data.empty(); }

    /**
     * @brief Clear dictionary
     * 
     */
    void clear() { data.clear(); }
  };

} // namespace molcpp