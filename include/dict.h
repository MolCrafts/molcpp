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

        // constructr for Data<Vector3D>
        template <typename T>
        Data(const T &V) : _value(V) {}

        /**
         * @brief Construct a new Data object from another Data object
         *
         * @tparam Us
         * @param other
         */
        template <typename... Us>
        Data(const Data<Us...> &other) : _value(other.get_raw()) {}

        /**
         * @brief Construct a new Data object from another Data object
         *
         * @tparam Us
         * @param other
         */
        template <typename... Us>
        Data(Data<Us...> &&other) : _value(std::move(other.get_raw())) {}

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
            if (_value.index() != other.get_raw().index())
                return false;
            return _value == other.get_raw();
        }

        /**
         * @brief Equality operator that compare with a value which type is T in Ts
         * 
         */
        template <typename T>
        bool operator==(const T &V) const
        {
            return get<T>() == V;
        }

        /**
         * @brief Get a typed value object
         *
         * @tparam T
         * @return const T&
         */
        template <typename T>
        inline const T &get() const
        {
            return std::get<T>(_value);
        }

        /**
         * @brief Set any type of value
         *
         * @param V
         */
        inline void set(const variant_type &V)
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
        inline bool is() const
        {
            return std::holds_alternative<T>(_value);
        }

        /**
         * @brief Returns the zero-based index of the alternative that is currently held by the variant.
         * For Data<int, double>(3.14), the index is 1.
         * @return const size_t
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

    private:
        variant_type _value;
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

        // copy constructor
        Dict(const Dict &other) : m_map(other.m_map){};

        // move constructor
        Dict(Dict &&other) : m_map(std::move(other.m_map)){};

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
            m_map[key] = value;
        }

        /**
         * @brief Get a typed value for a key
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
                throw KeyError("KeyError: " + key);
            }
            return it->second.template get<T>();
        }

        /**
         * @brief Return a list of keys
         *
         * @return std::vector<key_type>
         */
        std::vector<key_type> keys() const
        {
            std::vector<key_type> keys;
            for (const auto &pair : m_map)
            {
                keys.push_back(pair.first);
            }
            return keys;
        }

        /**
         * @brief Return a list of values
         *
         * @return std::vector<value_type>
         */
        std::vector<value_type> values() const
        {
            std::vector<value_type> values;
            for (const auto &pair : m_map)
            {
                values.push_back(pair.second);
            }
            return values;
        }

        /**
         * @brief Check if the key exists
         *
         * @param key
         * @return true
         * @return false
         */
        bool has(const key_type &key) const
        {
            return m_map.find(key) != m_map.end();
        }

        /**
         * @brief Get a value raw value for a key
         *
         * @param key
         * @return value_type&
         */
        value_type &operator[](const key_type &key)
        {
            return m_map[key];
        }

        /**
         * @brief Get a value raw value for a key
         *
         * @param key
         * @return const value_type&
         */
        const value_type &operator[](const key_type &key) const
        {
            return m_map.at(key);
        }

        // operator=
        Dict &operator=(const Dict &other)
        {
            m_map = other.m_map;
            return *this;
        }

        Dict& operator=(const Dict&& rhs)
        {
            m_map = std::move(rhs.m_map);
            return *this;
        }

        /**
         * @brief Returns a read/write iterator that points to the first pair in the map
         *
         * @return auto
         */
        auto begin() const
        {
            return m_map.begin();
        }

        /**
         * @brief Returns a read/write iterator that points one past the last pair in the map
         *
         * @return auto
         */
        auto end() const
        {
            return m_map.end();
        }

        /**
         * @brief Get the map object
         *
         * @return container_type
         */
        container_type get_map() const
        {
            return m_map;
        }

    private:
        container_type m_map;
    };

}