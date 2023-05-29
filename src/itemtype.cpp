#include "itemtype.h"

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

    bool AtomType::equal_to(AtomType &other)
    {
        if (other.get_name() == get_name())
            return true;
        else
            return false;
    }

    bool AtomType::equal_to(AtomType *other)
    {
        if (other->get_name() == get_name())
            return true;
        else
            return false;
    }

    bool AtomType::operator==(AtomType &other)
    {
        return equal_to(other);
    }

    bool AtomType::operator!=(AtomType *other)
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

    bool AtomType::has(const std::string &key) const
    {
        return _properties.has(key);
    }

    std::unique_ptr<AtomType> create_atomtype(const std::string &name)
    {
        return std::make_unique<AtomType>(name);
    }

    AtomTypeManager::AtomTypeManager() : _atom_types{}
    {
    }

    AtomType *AtomTypeManager::def(const std::string &name)
    {
        _atom_types.emplace_back(new AtomType(name));
        return _atom_types.back();
    }

    std::optional<AtomType *> AtomTypeManager::get(const std::string &tname)
    {
        // use std::find to find atomtype
        auto it = std::find_if(_atom_types.begin(), _atom_types.end(), [&tname](AtomType *atype)
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

    BondType::BondType(const std::string &name, AtomType *_itype, AtomType *_jtype) : _name{name}, _itomtype{_itype}, _jtomtype{_jtype} {};

    bool BondType::has(const std::string &key) const
    {
        return _properties.has(key);
    }

    AtomType *BondType::get_itype() const
    {
        return _itomtype;
    }

    AtomType *BondType::get_jtype() const
    {
        return _jtomtype;
    }

    std::string BondType::get_name() const
    {
        return _name;
    }

    bool BondType::equal_to(BondType &other)
    {
        if (other.get_name() == _name)
            return true;
        else
            return false;
    }

    bool BondType::equal_to(BondType *other)
    {
        if (other->get_name() == _name)
            return true;
        else
            return false;
    }

    bool BondType::operator==(BondType &other)
    {
        return equal_to(other);
    }

    bool BondType::operator!=(BondType *other)
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

    std::unique_ptr<BondType> create_bondtype(const std::string &name, AtomType *itype, AtomType *jtype)
    {
        return std::make_unique<BondType>(name, itype, jtype);
    }

    BondTypeManager::BondTypeManager() : _bond_types{}
    {
    }

    BondType *BondTypeManager::def(const std::string &name, AtomType *itype, AtomType *jtype)
    {
        auto bondtype = this->get(name);
        if (bondtype.has_value())
        {
            throw KeyError("BondType " + name + " already exists.");
        }
        else
        {
            _bond_types.push_back(new BondType(name, itype, jtype));
            return _bond_types.back();
        }
    }

    std::optional<BondType *> BondTypeManager::get(const std::string &tname)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&tname](BondType *btype)
                               { return btype->get_name() == tname; });

        if (it != _bond_types.end())
            return *it;
        else
        {
            LOG_INFO("BondType " << tname << " not found.");
            return std::nullopt;
        }
    }

    std::optional<BondType *> BondTypeManager::get(AtomType *itype, AtomType *jtype)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&itype, &jtype](BondType *btype)
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