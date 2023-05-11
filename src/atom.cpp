#include "atom.h"
#include "bond.h"

namespace molcpp
{
    Atom::Atom() : _type{nullptr}, _properties{}, _bonds{}
    {
        _id = reinterpret_cast<size_t>(this);
    }

    Atom::Atom(const AtomTypePtr &type) : _type{type}, _properties{}, _bonds{}
    {
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
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b)
                                    { return *b == *bond; });
        return results == _bonds.end() ? false : true;
    }

    bool Atom::del_bond(BondPtr bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b)
                                    { return *b == *bond; });
        if (results == _bonds.end())
        {
            return false;
        }
        else
        {
            _bonds.erase(results);
            return true;
        }
    }

    bool Atom::is_nbr(AtomPtr atom)
    {
        auto nbrs = this->get_nbrs();
        auto results = std::find_if(nbrs.begin(), nbrs.end(), [atom](AtomPtr a)
                                    { return *a == *atom; });
        return results == nbrs.end() ? false : true;
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

    const std::string &Atom::get_typename()
    {
        if (_type != nullptr)
        {
            return _type->get_name();
        }

        else
            throw KeyError("Atom has no type");
    }

    void Atom::set_type(const AtomTypePtr &type)
    {
        _type = type;
    }

    const AtomTypePtr &Atom::get_type()
    {
        return _type;
    }

    void Atom::set(const std::string &key, const AtomProperty &value)
    {
        _properties.set(key, value);
    }

    bool Atom::equal_to(const Atom &other) const
    {
        return get_id() == other.get_id();
    }

    bool Atom::equal_to(const AtomPtr &other) const
    {
        return get_id() == other->get_id();
    }

    bool Atom::operator==(const Atom &other) const
    {
        return equal_to(other);
    }

    const size_t Atom::get_id() const
    {
        return _id;
    }

    AtomPtr new_atom()
    {
        return std::make_shared<Atom>();
    }

    AtomPtr new_atom(const AtomTypePtr &type)
    {
        return std::make_shared<Atom>(type);
    }

}