#pragma once
#include <map>
#include <variant>
#include "mperror.h"

namespace molcpp
{
    /**
     * @brief The class template Data represents a type-safe union. An instance of Data at any given time holds a value of one of its alternative types
     * 
     * @tparam Ts 
     */
    template <typename... Ts>
    class Data
    {
    public:
        using variant_type = std::variant<Ts...>;

        /**
         * @brief Construct a new Data object
         * 
         */
        Data() : _value(variant_type{}) {}

        /**
         * @brief Construct a new Data object with value
         * 
         * @tparam T 
         * @param value 
         */
        template <typename T>
        Data(const T &value) : _value(value) {}

        /**
         * @brief Assignment operator
         * 
         * @tparam T 
         * @param V 
         * @return Data<Ts...>& 
         */
        template <typename T>
        Data<Ts...> &operator=(const T &V)
        {

            _value = V;
            return *this;
        }

        /**
         * @brief Equality operator
         * 
         * @tparam Us 
         * @param other 
         * @return true 
         * @return false 
         */
        template <typename... Us>
        bool operator==(const Data<Us...> &other) const
        {
            if (_value.index() != other.get_variant().index())
                return false;
            return _value == other.get_variant();
        }

        /**
         * @brief Get a typed value object
         * 
         * @tparam T 
         * @return const T& 
         */
        template <typename T>
        const T &get() const
        {
            return std::get<T>(_value);
        }

        /**
         * @brief Set any type of value
         * 
         * @param V 
         */
        void set(const variant_type &V)
        {
            _value = V;
        }

        /**
         * @brief Check if the value is of type T
         * 
         * @tparam T 
         * @return true 
         * @return false 
         */
        template <typename T>
        bool is() const
        {
            return std::holds_alternative<T>(_value);
        }

        // variant_type _value;
        /**
         * @brief Returns the zero-based index of the alternative that is currently held by the variant.
         * For Data<int, double>(3.14), the index is 1.
         * @return const auto 
         */
        const size_t index() const
        {
            return _value.index();
        }

        /**
         * @brief Get the variant object
         * Obtain internal std:: variant variables, which can be manipulated but cannot be modified
         * @return variant_type 
         */
        variant_type get_raw() const
        {
            return _value;
        }

        /**
         * @brief For print Data object
         * 
         * @param os 
         * @param d 
         * @return std::ostream& 
         */
        friend std::ostream &operator<<(std::ostream &os, const Data &d)
        {
            switch (d.index())
            {
            case 0:
                os << d.get<int>();
                break;
            case 1:
                os << d.get<std::string>();
                break;
            }
            return os;
        }
    };

    /**
     * @brief The class template Dict represents a map for Data. An instance of Dict at any given time holds a set of string-Data<Ts...> pairs
     * 
     * @tparam Ts 
     */
    template <typename... Ts>
    class Dict
    {
    public:
        using key_type = std::string;
        using value_type = Data<Ts...>;
        using container_type = std::map<key_type, value_type>;

        /**
         * @brief Construct a new Dict object
         * 
         */
        Dict() : m_map(){};

        /**
         * @brief Construct a new Dict object
         * 
         * @param map 
         */
        Dict(const container_type &map) : m_map(map){};

        /**
         * @brief Return the number of elements in the container
         * 
         * @return size_t
         */
        size_t size() const
        {
            return m_map.size();
        }

        /**
         * @brief Set a value for a key
         * 
         * @tparam T 
         * @param key 
         * @param value 
         */
        template <typename T>
        void set(const key_type &key, const T &value)
        {
            m_map.emplace(key, value);
        }

        /**
         * @brief 
         * 
         * @tparam T 
         * @param key 
         * @return const T& 
         */
        template <typename T>
        const T &get(const key_type &key) const
        {
            auto it = m_map.find(key);
            if (it == m_map.end())
            {
                throw std::out_of_range("Key not found");
            }
            return it->second.template get<T>();
        }

        std::vector<key_type> key() const
        {
            std::vector<key_type> keys;
            for (const auto &pair : m_map)
            {
                keys.push_back(pair.first);
            }
            return keys;
        }

        std::vector<value_type> value() const
        {
            std::vector<value_type> values;
            for (const auto &pair : m_map)
            {
                values.push_back(pair.second);
            }
            return values;
        }

        bool has(const key_type &key) const
        {
            return m_map.find(key) != m_map.end();
        }

        value_type &operator[](const key_type &key)
        {
            return m_map[key];
        }

        const value_type &operator[](const key_type &key) const
        {
            return m_map.at(key);
        }

        // iterator and return key-value pair
        auto begin() const
        {
            return m_map.begin();
        }

        auto end() const
        {
            return m_map.end();
        }

        container_type get_map() const
        {
            return m_map;
        }
    
    private:
        container_type m_map;
    };

    // pre-defined dict type
    using AtomPropertyDict = Dict<int, double, std::string>;
    using AtomProperty = AtomPropertyDict::value_type;
    using BondPropertyDict = Dict<int, double, std::string>;
    using BondProperty = BondPropertyDict::value_type;
}