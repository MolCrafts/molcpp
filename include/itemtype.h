#pragma once
#include "dict.h"
#include "log.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace molcpp
{

static size_t gen_id()
{
    return reinterpret_cast<size_t>(new size_t);
}

class ItemType
{

  public:
    ItemType() : _id(gen_id()){};

    ItemType(const ItemType &other) : _id(gen_id()), _props(other._props){};

    ItemType(ItemType &&other) : _id(other._id), _props(std::move(other._props)){};

    size_t get_id() const
    {
        return _id;
    }

    /**
     * @brief Get the clone of the itemType.
     *
     */
    ItemType clone() const
    {
        return ItemType(*this);
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

class AtomType : public ItemType
{
  public:
    /**
     * @brief Construct a new Atom Type object
     *
     */
    AtomType(const std::string &);

    /**
     * @brief Get the name of the AtomType
     *
     * @return const std::string&
     */
    const std::string &get_name() const;

    /**
     * @brief Compare two AtomType
     *
     * @param other
     * @return true
     * @return false
     */
    bool equal_to(AtomType &other);

    /**
     * @brief Compare two AtomType with names
     *
     * @param other
     * @return true
     * @return false
     */
    bool equal_to(AtomType *other);

    /**
     * @brief Compare two AtomType with names
     *
     * @return true
     * @return false
     */
    bool operator==(AtomType &);

    /**
     * @brief Compare two AtomType with names
     *
     * @return true
     * @return false
     */
    bool operator!=(AtomType *);
};

} // namespace molcpp