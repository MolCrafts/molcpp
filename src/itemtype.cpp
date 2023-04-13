#include "itemtype.h"
#include "forcefield.h"

namespace molcpp
{

    AtomType::AtomType(const std::string &name) : _properties{}
    {
        _properties["name"] = name;
    };

    const std::string& AtomType::get_name() const
    {
        return _properties["name"].get<std::string>();
    }

    bool AtomType::operator==(const AtomType &other) const
    {
        if (other.get_name() == get_name())
            return true;
        else
            return false;
    }

    bool AtomType::operator!=(const AtomType &other) const
    {
        return !operator==(other);
    }

    AtomTypeManager::AtomTypeManager() : _atom_types{}
    {
    }

    AtomProperty &AtomType::operator[](const std::string &key)
    {
        return _properties[key];
    }

    AtomTypePtr create_atomtype(const std::string &name)
    {
        return std::make_shared<AtomType>(name);
    }

    AtomTypePtr AtomTypeManager::def(const std::string &name)
    {
        auto at1 = std::make_shared<AtomType>(name);
        _atom_types.push_back(at1);
        return at1;
    }

    std::optional<AtomTypePtr> AtomTypeManager::get(std::string tname)
    {
        // use std::find to find atomtype
        auto it = std::find_if(_atom_types.begin(), _atom_types.end(), [&tname](const AtomTypePtr &atype)
                               { return atype->get_name() == tname; });

        if (it != _atom_types.end())
            return *it;
        else
        {
            LOG_ERROR("AtomType " << tname << " not found.");
            return std::nullopt;
        }
    }

    bool BondType::operator==(const BondType &other) const
    {
        if (other.get_name() == _name)
            return true;
        else
            return false;
    }

    BondProperty &BondType::operator[](const std::string &key)
    {
        return _properties[key];
    }

    BondTypeManager::BondTypeManager() : _bond_types{}
    {
    }

    BondTypePtr create_bondtype(const std::string &name, const AtomTypePtr &itype, const AtomTypePtr &jtype)
    {
        return std::make_shared<BondType>(name, itype, jtype);
    }

    BondTypePtr BondTypeManager::def(const std::string &name, const AtomTypePtr &itype, const AtomTypePtr &jtype)
    {
        auto bondtype = this->get(name);
        if (bondtype.has_value())
        {
            LOG_ERROR("BondType " << name << " already exists.");
            throw std::runtime_error("BondType already exists.");
        }
        auto bt = create_bondtype(name, itype, jtype);
        _bond_types.push_back(bt);
        return bt;
    }

    std::optional<BondTypePtr> BondTypeManager::get(const std::string &tname)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&tname](const BondTypePtr &btype)
                               { return btype->get_name() == tname; });

        if (it != _bond_types.end())
            return *it;
        else
        {
            LOG_ERROR("BondType " << tname << " not found.");
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
            LOG_ERROR("BondType " << itype->get_name() << "-" << jtype->get_name() << " not found.");
            return std::nullopt;
        }
    }

}