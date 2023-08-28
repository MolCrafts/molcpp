#include <any>
#include <initializer_list>
#include <memory>

#include "dict.h"

namespace molcpp
{

static size_t gen_id()
{
    return reinterpret_cast<size_t>(new size_t);
}

class Item
{

  public:
    Item() : _id(gen_id()){};

    Item(const Item &other) : _id(gen_id()), _props(other._props){};

    Item(Item &&other) : _id(other._id), _props(std::move(other._props)){};

    size_t get_id() const
    {
        return _id;
    }

    /**
     * @brief Get the clone of the item.
     *
     */
    Item clone() const
    {
        return Item(*this);
    }

    /**
     * @brief Get the value associated with a key.
     *
     * @tparam T
     * @param key
     * @return T
     */
    template <typename T> T get(const std::string &key)
    {
        return _props.get<T>(key);
    }

    /**
     * @brief Get the value associated with a key, or a default value.
     *
     * @tparam T
     * @param key
     * @param default_value
     * @return T
     */
    template <typename T> T get(const std::string &key, const T &default_value)
    {
        return _props.get<T>(key, default_value);
    }

    /**
     * @brief Set the value associated with a key.
     *
     */
    template <typename T> T set(const std::string &key, const T &default_value)
    {
        return _props.setdefault<T>(key, default_value);
    }

  private:
    size_t _id;
    Dict _props;
};

class Atom : public Item
{

  public:
    Atom(const std::string &name) : _name{name} {};

    Atom clone() const
    {
        return Atom(*this);
    }

  private:
    std::string _name;
};

class Bond : public Item
{

  public:
    Bond(Atom *i, Atom *j) : _i{i}, _j{j} {};

    Bond clone() const
    {
        return Bond(*this);
    }

    Atom *get_i() const
    {
        return _i;
    }

    Atom *get_j() const
    {
        return _j;
    }

  private:
    Atom *_i;
    Atom *_j;
};
} // namespace molcpp