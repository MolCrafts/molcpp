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
        Atom(const AtomTypePtr&);
        bool add_bond(BondPtr);
        bool del_bond(BondPtr);
        bool has_bond(BondPtr);
        bool is_nbr(AtomPtr);
        std::vector<AtomPtr> get_nbrs();
        template<typename T>
        T get(const std::string& key)
        {
            if (_properties.has(key)) return _properties.get<T>(key);
            else return _type->get<T>(key);
        };
        void set(const std::string& key, const AtomProperty& value);
        const std::string& get_typename();
        void set_type(const std::string&);
        void set_type(const AtomTypePtr&);
        const AtomTypePtr& get_type();

    private:
        AtomTypePtr _type;
        AtomPropertyDict _properties;
        std::vector<BondPtr> _bonds;
    };

    // factory function
    AtomPtr create_atom();
    AtomPtr create_atom(const AtomTypePtr& type);

}
