#pragma once
#include <vector>
#include <memory>
#include "dict.h"
#include "itemtype.h"

namespace molcpp
{

    class Atom;
    using AtomPtr = std::shared_ptr<Atom>;
    class Bond;
    using BondPtr = std::shared_ptr<Bond>;

    class Bond
    {

    public:
        /**
         * @brief Construct a new Bond object
         *
         */
        Bond(AtomPtr, AtomPtr);

        /**
         * @brief Get the itom
         *
         * @return AtomPtr
         */
        AtomPtr get_itom() const;

        /**
         * @brief Get the jtom
         *
         * @return AtomPtr
         */
        AtomPtr get_jtom() const;

        /**
         * @brief Get the bondtype
         *
         * @return BondTypePtr
         */
        BondTypePtr get_bondtype() const;

        /**
         * @brief Set the type
         *
         */
        void set_type(const BondTypePtr &);

        /**
         * @brief
         *
         */
        bool equal_to(const Bond &) const;

        /**
         * @brief Compare two BondPtr
         *
         * @return true
         * @return false
         */
        bool equal_to(const BondPtr &) const;

        /**
         * @brief Compare two BondPtr
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator==(const Bond &) const;

        /**
         * @brief get BondProperty
         *
         * @param key
         * @return BondProperty&
         */
        BondProperty &operator[](const std::string &key);

        /**
         * @brief Set property
         *
         * @param key
         * @param value
         */
        void set(const std::string &key, const BondProperty &value);

        /**
         * @brief Get property with key
         *
         * @tparam T
         * @param key
         * @return T
         */
        template <typename T>
        T get(const std::string &key) const
        {
            if (_properties.has(key))
                return _properties.get<T>(key);
            else
                return _type->get<T>(key);
        }

    private:
        std::weak_ptr<Atom> _itom;
        std::weak_ptr<Atom> _jtom;
        BondTypePtr _type;
        BondPropertyDict _properties;
    };

    // factory function
    BondPtr new_bond(AtomPtr, AtomPtr);

}
