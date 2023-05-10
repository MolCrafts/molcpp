#include "itemtype.h"
#include "forcefield.h"

namespace molcpp
{

    AtomType::AtomType(const std::string &name) : _properties{}
    {
        _properties["name"] = name;
    };

    const std::string &AtomType::get_name() const
    {
        return _properties["name"].get<std::string>();
    }

    bool AtomType::equal_to(const AtomType &other) const
    {
        if (other.get_name() == get_name())
            return true;
        else
            return false;
    }

    bool AtomType::equal_to(const AtomTypePtr &other) const
    {
        if (other->get_name() == this->get_name())
            return true;
        else
            return false;
    }

    bool AtomType::operator==(const AtomType &other) const
    {
        return equal_to(other);
    }

    bool AtomType::operator!=(const AtomType &other) const
    {
        return !equal_to(other);
    }

    AtomPropertyDict::value_type &AtomType::operator[](const AtomPropertyDict::key_type &key)
    {
        return _properties[key];
    }

    const AtomPropertyDict::value_type &AtomType::operator[](const AtomPropertyDict::key_type &key) const
    {
        return _properties[key];
    }

    void AtomType::set(const std::string &key, const AtomProperty &value)
    {
        _properties.set(key, value);
    }

    AtomTypePtr new_atomtype(const std::string &name)
    {
        return std::make_shared<AtomType>(name);
    }

    AtomTypeManager::AtomTypeManager() : _atom_types{}
    {
    }

    AtomTypePtr AtomTypeManager::def(const std::string &name)
    {
        auto at1 = std::make_shared<AtomType>(name);
        _atom_types.push_back(at1);
        return at1;
    }

    std::optional<AtomTypePtr> AtomTypeManager::get(const std::string &tname)
    {
        // use std::find to find atomtype
        auto it = std::find_if(_atom_types.begin(), _atom_types.end(), [&tname](const AtomTypePtr &atype)
                               { return atype->get_name() == tname; });

        if (it != _atom_types.end())
            return *it;
        else
        {
            LOG_INFO("AtomType " << tname << " not found.");
            return std::nullopt;
        }
    }

    size_t AtomTypeManager::get_ntypes() const
    {
        return _atom_types.size();
    }

    BondType::BondType(const std::string &name, const AtomTypePtr &_itype, const AtomTypePtr &_jtype) : _name{name}, _itomtype{_itype}, _jtomtype{_jtype} {};

    AtomTypePtr BondType::get_itype() const
    {
        return _itomtype.lock();
    }

    AtomTypePtr BondType::get_jtype() const
    {
        return _jtomtype.lock();
    }

    std::string BondType::get_name() const
    {
        return _name;
    }

    bool BondType::equal_to(const BondType &other) const
    {
        if (other.get_name() == _name)
            return true;
        else
            return false;
    }

    bool BondType::equal_to(const BondTypePtr &other) const
    {
        if (other->get_name() == _name)
            return true;
        else
            return false;
    }

    bool BondType::operator==(const BondType &other) const
    {
        return equal_to(other);
    }

    bool BondType::operator!=(const BondType &other) const
    {
        return !equal_to(other);
    }

    BondPropertyDict::value_type &BondType::operator[](const BondPropertyDict::key_type &key)
    {
        return _properties[key];
    }

    const BondPropertyDict::value_type &BondType::operator[](const BondPropertyDict::key_type &key) const
    {
        return _properties[key];
    }

    void BondType::set(const std::string &key, const BondProperty &value)
    {
        _properties.set(key, value);
    }

    BondTypePtr new_bondtype(const std::string &name, const AtomTypePtr &itype, const AtomTypePtr &jtype)
    {
        return std::make_shared<BondType>(name, itype, jtype);
    }

    BondTypeManager::BondTypeManager() : _bond_types{}
    {
    }

    BondTypePtr BondTypeManager::def(const std::string &name, const AtomTypePtr &itype, const AtomTypePtr &jtype)
    {
        auto bondtype = this->get(name);
        if (bondtype.has_value())
        {
            throw KeyError("BondType " + name + " already exists.");
        }
        else
        {
            auto bt = new_bondtype(name, itype, jtype);
            _bond_types.push_back(bt);
            return bt;
        }
    }

    std::optional<BondTypePtr> BondTypeManager::get(const std::string &tname)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&tname](const BondTypePtr &btype)
                               { return btype->get_name() == tname; });

        if (it != _bond_types.end())
            return *it;
        else
        {
            LOG_INFO("BondType " << tname << " not found.");
            return std::nullopt;
        }
    }

    std::optional<BondTypePtr> BondTypeManager::get(const AtomTypePtr &itype, const AtomTypePtr &jtype)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&itype, &jtype](const BondTypePtr &btype)
                               { return ((btype->get_itype() == itype && btype->get_jtype() == jtype) || (btype->get_itype() == jtype && btype->get_jtype() == itype)); });

        if (it != _bond_types.end())
            return *it;
        else
        {
            LOG_INFO("BondType " << itype->get_name() << "-" << jtype->get_name() << " not found.");
            return std::nullopt;
        }
    }

    size_t BondTypeManager::get_ntypes() const
    {
        return _bond_types.size();
    }

}