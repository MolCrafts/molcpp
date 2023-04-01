#pragma once
#include <vector>
#include <memory>

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
            // operator==
            bool operator==(const Bond &other) const;

        private:
            std::weak_ptr<Atom> _itom;
            std::weak_ptr<Atom> _jtom;

    };

    // factory function
    BondPtr create_bond(AtomPtr, AtomPtr);

}
