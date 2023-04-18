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
            Bond(AtomPtr, AtomPtr);
            AtomPtr get_itom() const;
            AtomPtr get_jtom() const;
            BondTypePtr get_bondtype() const;
            void set_type(const BondTypePtr&);
            void set_type(const std::string&);
            bool operator==(const Bond &other) const;

            BondProperty& operator[](const std::string &key);
            void set(const std::string &key, const BondProperty &value);
            template<typename T>
            T get(const std::string &key) const
            {
                if (_properties.has(key)) return _properties.get<T>(key);
                else return _type->get<T>(key);
            }

        private:
            std::weak_ptr<Atom> _itom;
            std::weak_ptr<Atom> _jtom;
            BondTypePtr _type;
            BondPropertyDict _properties;
    };

    // factory function
    BondPtr create_bond(AtomPtr, AtomPtr);

}
