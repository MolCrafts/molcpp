#pragma once
#include "algo.h"
#include "property.h"
#include <vector>
#include <memory>
#include "chemfiles.hpp"

namespace molcpp
{

    class Atom;
    using AtomPtr = std::shared_ptr<Atom>;
    class Bond;
    using BondPtr = std::shared_ptr<Bond>;

    class Atom
    {

    public:
        Atom() = default;
        bool add_bond(BondPtr);
        bool del_bond(BondPtr);
        bool has_bond(BondPtr);
        bool is_nbr(AtomPtr);
        std::vector<AtomPtr> get_nbrs();

        auto operator[](const std::string &key) const;
        Property_map<int, std::string, double> properties;

    private:
        std::vector<BondPtr> _bonds;
    };

    // factory function
    AtomPtr create_atom();

}
