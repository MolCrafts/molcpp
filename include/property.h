#include <map>
#include <variant>

namespace molcpp
{

    template <typename... Ts>
    class Property
    {
    public:
        using variant_type = std::variant<Ts...>;

        Property() : value_(variant_type{}) {}

        template <typename T>
        Property(const T &value) : value_(value) {}

        template <typename T>
        Property<Ts...> &operator=(const T &value)
        {

            value_ = value;
            return *this;
        }

        template <typename T>
        bool operator==(const T &value) const
        {
            // return std::visit([&](auto &&arg) { return arg == value; }, value_);
            return value_ == value;
        }

        template <typename... Us>
        bool operator==(const Property<Us...>& other) const
        {
            return value_ == other.value_;
        }

        template <typename T>
        T &get()
        {
            return std::get<T>(value_);
        }

        template <typename T>
        const T &get() const
        {
            return std::get<T>(value_);
        }

        template <typename T>
        bool is() const
        {
            return std::holds_alternative<T>(value_);
        }

    private:
        variant_type value_;
    };

    template <typename... Ts>
    class Property_map
    {
    public:
        using key_type = std::string;
        using value_type = Property<Ts...>;
        using container_type = std::map<key_type, value_type>;

    private:
        container_type m_map;

    public:
        template <typename T>
        void set(const key_type &key, const T &value)
        {
            auto it = m_map.find(key);
            if (it == m_map.end())
            {
                m_map.emplace(key, value);
            }
            else
            {
                it->second = value;
            }
        }

        template <typename T>
        T &get(const key_type &key)
        {
            auto it = m_map.find(key);
            if (it == m_map.end())
            {
                throw std::out_of_range("Key not found");
            }
            return it->second.template get<T>();
        }

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

    };
}