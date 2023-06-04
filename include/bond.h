#pragma once
#include <vector>
#include <memory>
#include "dict.h"
#include "itemtype.h"
#include "atom.h"

namespace molcpp
{

    using BondVec = std::vector<Bond *>;
    class Bond
    {

    public:
        /**
         * @brief Construct a new Bond object
         *
         */
        Bond(Atom*, Atom*);

        // copy constructor
        Bond(const Bond&);

        // move constructor
        Bond(Bond&&) noexcept;

        ~Bond();

        /**
         * @brief Get the itom
         *
         * @return Atom
         */
        Atom* get_itom();

        /**
         * @brief Get the jtom
         *
         * @return Atom
         */
        Atom* get_jtom();

        /**
         * @brief Get the bondtype
         *
         * @return BondTypePtr
         */
        BondType* get_bondtype() const;

        /**
         * @brief Set the type
         *
         */
        void set_type(BondType*);

        /**
         * @brief
         *
         */
        bool equal_to(Bond*);

        /**
         * @brief Compare two BondPtr
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator==(Bond*);

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
        T get(const std::string &key, T _default = T()) const
        {
            if (_properties.has(key))
                return _properties.get<T>(key);
            else if(_type != nullptr && _type->has(key))
                return _type->get<T>(key);
            else return _default;
        }

        Bond& operator=(Bond &&);

    private:
        Atom* _itom;
        Atom* _jtom;
        BondType* _type;
        BondPropertyDict _properties;
    };

    std::unique_ptr<Bond> create_bond(Atom*, Atom*);

}
