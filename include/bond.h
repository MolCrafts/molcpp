#pragma once
#include <vector>
#include <memory>
#include "dict.h"

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
            bool operator==(const Bond &other) const;

            BondProperty& operator[](const std::string &key);

        private:
            std::weak_ptr<Atom> _itom;
            std::weak_ptr<Atom> _jtom;

            BondPropertyDict _properties;
    };

    // factory function
    BondPtr create_bond(AtomPtr, AtomPtr);

}
