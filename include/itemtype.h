#pragma once
#include "dict.h"
#include "log.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace molcpp
{
class AtomType
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

    /**
     * @brief Set the Atom Property
     *
     * @param key
     * @param value
     */
    void set(const std::string &key, const AtomProperty &value);

    /**
     * @brief Get the Atom Property
     *
     * @tparam T
     * @param key
     * @return T
     */
    template <typename T> T get(const std::string &key)
    {
        if (_properties.has(key))
            return _properties.get<T>(key);
        else
            throw std::runtime_error("AtomType::get: key not found");
    };

    template <typename T> const T get(const std::string &key) const
    {
        if (_properties.has(key))
            return _properties.get<T>(key);
        else
            throw std::runtime_error("AtomType::get: key not found");
    };

    /**
     * @brief Check if has
     *
     */
    bool has(const std::string &key) const;

    /**
     * @brief Get a value raw value for a key
     *
     * @param key
     * @return value_type&
     */
    AtomPropertyDict::value_type &operator[](const AtomPropertyDict::key_type &key);
    /**
     * @brief Get a value raw value for a key
     *
     * @param key
     * @return const value_type&
     */
    const AtomPropertyDict::value_type &operator[](const AtomPropertyDict::key_type &key) const;

  private:
    AtomPropertyDict _properties;
};

std::unique_ptr<AtomType> create_atomtype(const std::string &);

class AtomTypeManager
{

  public:
    /**
     * @brief Construct a new Atom Type Manager object
     *
     */
    AtomTypeManager();

    /**
     * @brief Define a new AtomType
     *
     * @return AtomType
     */
    AtomType *def(const std::string &);

    /**
     * @brief Get the AtomType by name
     *
     * @return std::optional<AtomType>
     */
    std::optional<AtomType *> get(const std::string &);

    /**
     * @brief Get the number of defined atomtypes
     *
     * @return size_t
     */
    size_t get_ntypes() const;

  private:
    std::vector<AtomType *> _atom_types;
};

class BondType
{
  public:
    /**
     * @brief Construct a new Bond Type object
     *
     * @param name
     * @param _itype
     * @param _jtype
     */
    BondType(const std::string &name, AtomType *_itype, AtomType *_jtype);

    bool has(const std::string &key) const;

    /**
     * @brief Get the itype object
     *
     * @return AtomType
     */
    AtomType *get_itype() const;

    /**
     * @brief Get the jtype object
     *
     * @return AtomType
     */
    AtomType *get_jtype() const;

    /**
     * @brief Get the name object
     *
     * @return std::string
     */
    std::string get_name() const;

    /**
     * @brief Compare two BondType
     *
     * @param other
     * @return true
     * @return false
     */
    bool equal_to(BondType &other);
    bool equal_to(BondType *other);

    /**
     * @brief Compare two BondType
     *
     * @return true
     * @return false
     */
    bool operator==(BondType &);

    /**
     * @brief Compare two BondType
     *
     * @return true
     * @return false
     */

    bool operator!=(BondType *);

    /**
     * @brief Get a value raw value for a key
     *
     * @param key
     * @return value_type&
     */
    BondPropertyDict::value_type &operator[](const BondPropertyDict::key_type &key);

    /**
     * @brief Get a value raw value for a key
     *
     * @param key
     * @return const value_type&
     */
    const BondPropertyDict::value_type &operator[](const BondPropertyDict::key_type &key) const;

    /**
     * @brief
     *
     * @param key
     * @param value
     */
    void set(const std::string &key, const BondProperty &value);

    /**
     * @brief
     *
     * @tparam T
     * @param key
     * @return T
     */
    template <typename T> T get(const std::string &key)
    {
        if (_properties.has(key))
            return _properties.get<T>(key);
        else
            throw std::runtime_error("BondType::get: key not found");
    };

  private:
    std::string _name; // name of the bondtype
    AtomType *_itomtype;
    AtomType *_jtomtype;          // weak pointer to atomtype in both ends
    BondPropertyDict _properties; // properties of the bondtype
};

std::unique_ptr<BondType> create_bondtype(const std::string &, AtomType *, AtomType *);

class BondTypeManager
{
  public:
    /**
     * @brief Construct a new Bond Type Manager object
     *
     */
    BondTypeManager();

    /**
     * @brief Define a new BondType
     *
     * @return BondType
     */
    BondType *def(const std::string &, AtomType *, AtomType *);

    /**
     * @brief Get the BondType by name
     *
     * @param tname
     * @return std::optional<BondType>
     */
    std::optional<BondType *> get(const std::string &tname);

    /**
     * @brief Get the BondType by AtomTypes
     *
     * @param itype
     * @param jtype
     * @return std::optional<BondType>
     */
    std::optional<BondType *> get(AtomType *itype, AtomType *jtype);

    /**
     * @brief Get the ntypes object
     *
     * @return size_t
     */
    size_t get_ntypes() const;

  private:
    std::vector<BondType *> _bond_types;
};

} // namespace molcpp