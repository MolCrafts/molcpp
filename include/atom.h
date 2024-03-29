#pragma once
#include "algo.h"
#include "dict.h"
#include "itemtype.h"
#include "linalg.hpp"
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

        ~Atom();

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
        T get(const std::string& key, T _default = T())
        {
            if (_properties.has(key)) return _properties.get<T>(key);
            else if(_type != nullptr && _type->has(key)) return _type->get<T>(key);
            else return _default;
        };

        template<typename T>
        const T get(const std::string& key, T _default = T()) const
        {
            if (_properties.has(key)) return _properties.get<T>(key);
            else if(_type != nullptr && _type->has(key)) return _type->get<T>(key);
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
        void set_type(AtomType*);

        /**
         * @brief Get the atomtype
         *
         * @return const AtomType*
         */
        AtomType* get_type();

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool equal_to(Atom*);

        bool equal_to(const Atom&);

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool operator==(Atom*);
        bool operator==(const Atom&);

        /**
         * @brief Get id of this atom
         *
         */
        size_t get_id() const;

        AtomProperty &operator[](const std::string& key)
        {
            return _properties[key];
        }

        const AtomProperty &operator[](const std::string& key) const
        {
            return _properties[key];
        }

    private:
        AtomType* _type;
        AtomPropertyDict _properties;
        size_t _id;
    };

    // factory function
    std::unique_ptr<Atom> from_chemfiles(const chemfiles::Atom& chflAtom);
    chemfiles::Atom to_chemfiles(Atom*);
    std::unique_ptr<Atom> create_atom(const std::string& name = "", Vector3D pos = {0, 0, 0});

}
