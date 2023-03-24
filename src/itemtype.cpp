#include "forcefield.h"

namespace MolCpp
{

    AtomType::AtomType(const std::string &name) : _name{name} {};

    bool AtomType::operator==(const AtomType &other) const
    {
        if (other.get_name() == _name)
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
        if (other._name == _name && other._itomtype == _itomtype && other._jtomtype == _jtomtype)
            return true;
        else
            return false;
    }

    BondTypeManager::BondTypeManager() : _bond_types{}
    {
    }

    BondTypePre BondTypeManager::def(const std::string &name, const AtomType &itype, const AtomType &jtype)
    {
        auto at1 = std::make_shared<BondType>(name);
        _atom_types.push_back(at1);
        return at1;
    }

    std::optional<BondType> BondTypeManager::get(const std::string &tname)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&tname](const BondType &atype)
                               { return atype.get_name() == tname; });

        if (it != _bond_types.end())
            return *it;
        else
        {
            LOG_ERROR("BondType " << tname << " not found.");
            return std::nullopt;
        }
    }

    std::optional<BondType> BondTypeManager::get(const AtomType &itype, const AtomType &jtype)
    {
        auto it = std::find_if(_bond_types.begin(), _bond_types.end(), [&itype, &jtype](const BondType &atype)
                               { return atype.get_itype() == itype && atype.get_jtype() == jtype; });

        if (it != _bond_types.end())
            return *it;
        else
        {
            LOG_ERROR("BondType " << itype.get_name() << "-" << jtype.get_name() << " not found.");
            return std::nullopt;
        }
    }


}