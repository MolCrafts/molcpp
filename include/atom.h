#pragma once
#include "algo.h"
#include "dict.h"
#include "itemtype.h"
#include <vector>
#include <memory>

namespace molcpp
{

    class Atom;
    using AtomPtr = std::shared_ptr<Atom>;
    class Bond;
    using BondPtr = std::shared_ptr<Bond>;

    using AtomVec = std::vector<AtomPtr>;
    using BondVec = std::vector<BondPtr>;

    class Atom
    {

    public:
        Atom();
        bool add_bond(BondPtr);
        bool del_bond(BondPtr);
        bool has_bond(BondPtr);
        bool is_nbr(AtomPtr);
        std::vector<AtomPtr> get_nbrs();
        AtomProperty& operator[](const std::string &key);
        AtomProperty& get(const std::string &key);
        AtomProperty& set(const std::string &key, const AtomProperty &value);
        const std::string& get_type();
        void set_type(const std::string&);
        void set_atomtype(const AtomTypePtr&);
        const AtomTypePtr& get_atomtype();

    private:
        AtomTypePtr _type;
        AtomPropertyDict _properties;
        std::vector<BondPtr> _bonds;
    };

    // factory function
    AtomPtr create_atom();

}
