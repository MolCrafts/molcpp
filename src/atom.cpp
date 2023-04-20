#include "atom.h"
#include "bond.h"

namespace molcpp
{
    Atom::Atom() : _type{nullptr}, _properties{}, _bonds{} {}

    Atom::Atom(const AtomTypePtr& type) : _type{type}, _properties{}, _bonds{} {
        _properties.set("type", type->get_name());
    }

    bool Atom::add_bond(BondPtr bond)
    {
        if (has_bond(bond))
        {
            return false;
        }
        else
        {
            _bonds.push_back(bond);
            return true;
        }
    }

    bool Atom::has_bond(BondPtr bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b) {
            return *b == *bond;
        });
        return results == _bonds.end() ? false : true;
    }

    bool Atom::del_bond(BondPtr bond)
    {
        auto result = find_in_container<std::vector<BondPtr>, BondPtr>(_bonds, bond);
        if (result.has_value())
        {
            _bonds.erase(_bonds.begin() + result.value());
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Atom::is_nbr(AtomPtr atom)
    {
        auto nbrs = this->get_nbrs();
        auto isInNbrs = find_in_container<std::vector<AtomPtr>, AtomPtr>(nbrs, atom).has_value();
        return isInNbrs;
    }

    std::vector<AtomPtr> Atom::get_nbrs()
    {
        std::vector<AtomPtr> nbrs;
        for (auto bond : _bonds)
        {
            auto itom = bond->get_itom();
            auto jtom = bond->get_jtom();
            if (itom.get() == this)
            {
                nbrs.push_back(jtom);
            }
            else
            {
                nbrs.push_back(itom);
            }
        }
        return nbrs;
    }

    const std::string& Atom::get_typename()
    {
        if (_properties.has("type"))
        {
            return _properties.get<std::string>("type");
        }
        else
        {
            return _type->get_name();
        }
    }

    void Atom::set_type(const std::string& type)
    {
        _properties.set("type", type);
    }

    void Atom::set_type(const AtomTypePtr& type)
    {
        _type = type;
    }

    const AtomTypePtr& Atom::get_type()
    {
        return _type;
    }

    AtomProperty& Atom::operator [] (const std::string& key)
    {
        if (_properties.has(key))
        {
            return _properties[key];
        }
        else
        {
            return (*_type)[key];
        }
    }

    void Atom::set(const std::string &key, const AtomProperty &value)
    {
        _properties.set(key, value);
    }

    AtomPtr create_atom()
    {
        return std::make_shared<Atom>();
    }

    AtomPtr create_atom(const AtomTypePtr& type)
    {
        return std::make_shared<Atom>(type);
    }
}