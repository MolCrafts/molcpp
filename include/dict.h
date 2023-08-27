#pragma once

#include "error.h"
#include <any>
#include <error.h>
#include <initializer_list>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace molcpp
{

/**
 * A dictionary class that mimics Python's dict.
 * The keys are unique strings and the values can be of any type.
 */
class Dict
{
  private:
    std::map<std::string, std::any> data;

  public:
    Dict() = default;

    Dict(std::initializer_list<std::pair<std::string, std::any>> initList)
    {
        for (const auto &pair : initList)
        {
            data[pair.first] = pair.second;
        }
    }

    /**
     * Get the value associated with a key.
     * Throws std::out_of_range if key is not present.
     */
    template <typename T> T get(const std::string &key)
    {
        return std::any_cast<T>(data.at(key));
    }

    /**
     * Get the value associated with a key, or a default value.
     */
    template <typename T> T get(const std::string &key, const T &default_value)
    {
        auto it = data.find(key);
        if (it == data.end())
            return default_value;
        else
            return std::any_cast<T>(it->second);
    }

    template <typename T> T get(const std::string &key) const
    {
        return std::any_cast<T>(data.at(key));
    }

    bool has(const std::string &key) const
    {
        return data.find(key) != data.end();
    }

    /**
     * Set a default value for a key if it is not already present.
     */
    template <typename T> T setdefault(const std::string &key, const T &default_value)
    {
        auto it = data.find(key);
        if (it == data.end())
        {
            data[key] = default_value;
            return default_value;
        }
        else
        {
            if (it->second.type() != typeid(T))
            {
                throw TypeError("Type mismatch");
            }
            return std::any_cast<T>(it->second);
        }
    }

    /**
     * Get a vector of all the keys in the dictionary.
     */
    std::vector<std::string> keys() const
    {
        std::vector<std::string> keys;
        for (const auto &pair : data)
        {
            keys.push_back(pair.first);
        }
        return keys;
    }

    /**
     * Get a vector of all the values in the dictionary.
     * Note: This method returns a vector of std::any objects.
     * You must cast them to the correct type before use.
     */
    std::vector<std::any> values() const
    {
        std::vector<std::any> values;
        for (const auto &pair : data)
        {
            values.push_back(pair.second);
        }
        return values;
    }

    /**
     * Update the dictionary with the contents of another dictionary.
     */
    void update(const Dict &other)
    {
        for (const auto &pair : other.data)
        {
            data[pair.first] = pair.second;
        }
    }

    /**
     * Operator overload for accessing dictionary values.
     * Note: This will insert the key into the dictionary if it is not present.
     */
    std::any &operator[](const std::string &key)
    {
        return data[key];
    }

    /**
     * @brief Get size of dictionary
     *
     */
    size_t size() const
    {
        return data.size();
    }

    /**
     * @brief Check if dictionary is empty
     *
     */
    bool empty() const
    {
        return data.empty();
    }

    /**
     * @brief Clear dictionary
     *
     */
    void clear()
    {
        data.clear();
    }

    /**
     * @brief Get iterator to beginning of dictionary
     *
     */
    auto begin()
    {
        return data.begin();
    }

    /**
     * @brief Get iterator to end of dictionary
     *
     */
    auto end()
    {
        return data.end();
    }

    /**
     * @brief Get iterator to beginning of dictionary
     *
     */
    auto begin() const
    {
        return data.begin();
    }

    /**
     * @brief Get iterator to end of dictionary
     *
     */
    auto end() const
    {
        return data.end();
    }
};

} // namespace molcpp