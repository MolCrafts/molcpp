#include <map>
#include <variant>

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
    T &get()
    {
        return std::get<T>(value_);
    }

    template <typename T>
    const T &get() const
    {
        return std::get<T>(value_);
    }

    template <typename Visitor>
    decltype(auto) visit(Visitor &&visitor) const
    {
        return std::visit(std::forward<Visitor>(visitor), value_);
    }

    template <typename Visitor>
    decltype(auto) visit(Visitor &&visitor)
    {
        return std::visit(std::forward<Visitor>(visitor), value_);
    }

private:
    variant_type value_;
};

template <typename... Ts>
class Property_map : public std::map<std::string, Property<Ts...>>
{
public:
    using base_type = std::map<std::string, Property<Ts...>>;

    using typename base_type::key_type;
    using typename base_type::mapped_type;
    using typename base_type::value_type;

    using base_type::base_type;

    template <typename T>
    void set(const key_type &key, const T &value)
    {
        auto it = this->find(key);
        if (it == this->end())
        {
            this->emplace(key, value);
        }
        else
        {
            it->second = value;
        }
    }

    template <typename T>
    T &get(const key_type &key)
    {
        auto it = this->find(key);
        if (it == this->end())
        {
            throw std::out_of_range("Key not found");
        }
        return it->second.template get<T>();
    }

    template <typename T>
    const T &get(const key_type &key) const
    {
        auto it = this->find(key);
        if (it == this->end())
        {
            throw std::out_of_range("Key not found");
        }
        return it->second.template get<T>();
    }
};