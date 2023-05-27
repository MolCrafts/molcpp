#pragma once
#include "algo.h"
#include "dict.h"
#include "itemtype.h"
#include "types.hpp"
#include <vector>
#include <memory>
#include <chemfiles.hpp>

namespace molcpp
{

    class Atom
    {

    public:
        /**
         * @brief Construct a new Atom object
         *
         */
        Atom(const std::string& name = "", Vector3D pos = {0, 0, 0});

        // copy constructor
        Atom(const Atom&);

        // move constructor
        Atom(Atom&&) noexcept;

        Atom& operator=(const Atom &);
        Atom& operator=(Atom &&) noexcept;

        /**
         * @brief Get a property by key
         *
         * @tparam T
         * @param key
         * @return T
         */
        template<typename T>
        T get(const std::string& key, T _default = T()) const
        {
            if (_properties.has(key)) return _properties.get<T>(key);
            else if(_type->has(key)) return _type->get<T>(key);
            else return _default;
        };

        /**
         * @brief
         *
         * @param key
         * @param value
         */
        void set(const std::string& key, const AtomProperty& value);

        bool has(const std::string& key);

        /**
         * @brief Set the atomtype
         *
         */
        void set_type(const AtomTypePtr&);

        /**
         * @brief Get the atomtype
         *
         * @return const AtomTypePtr&
         */
        const AtomTypePtr& get_type();

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool equal_to(const Atom&) const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool operator==(const Atom&) const;

        /**
         * @brief Get id of this atom
         *
         */
        const size_t get_id() const;

        void set_position(const Vector3D& pos);

        const Vector3D& get_position() const;

        AtomProperty &operator[](const std::string& key)
        {
            return _properties[key];
        }

        const AtomProperty &operator[](const std::string& key) const
        {
            return _properties[key];
        }

    private:
        AtomTypePtr _type;
        AtomPropertyDict _properties;
        size_t _id;
        Vector3D _pos;
    };

    // factory function
    Atom from_chemfiles(const chemfiles::Atom& chflAtom);
    chemfiles::Atom to_chemfiles(const Atom& atom);

}
