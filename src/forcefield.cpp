#include "forcefield.h"

namespace MolCpp
{

    // definition of AtomType


    // end of definition of AtomType

    // definition of AtomTypeManager

    AtomTypeManager::AtomTypeManager() : _atom_types{}
    {
    }

    bool def(std::string name)
    {
        AtomType atype;
        atype._name = name;
        _atom_types.push_back(atype);
        return true;
    }

    AtomType AtomTypeManager::get(std::string tname)
    {
        for (const auto atype : _atom_types)
        {
            if (atype._name == tname)
            {
                return atype;
            }
        }
        else
            LOG_ERROR("Atom type {} not found.", tname);
    }

    // end of definition of AtomTypeManager

    // definition of BondType

    // end of definition of BondType

    // definition of BondTypeManager

    BondTypeManager::BondTypeManager() : _bond_types{}
    {
    }

    bool def_bodtype(std::string name, AtomType itype, AtomType jtype)
    {
        BondType btype(name, itype, jtype);
        _bond_types.push_back(btype);
        return true;
    }

    BondType BondTypeManager::get(std::string tname)
    {
        for (const auto btype : _bond_types)
        {
            if (btype._name == tname)
            {
                return btype;
            }
        }
        else
            LOG_ERROR("Bond type {} not found.", tname);
    }

    BondType BondTypeManager::get(const AtomType& itype, const AtomType& jtype)
    {
        for (const auto btype : _bond_types)
        {
            if (btype._itomtype == itype && btype._jtomtype == jtype)
            {
                return btype;
            }
        }
        else
            LOG_ERROR("Bond type {}-{} not found.", itype._name, jtype._name);
    }

    // end of definition of BondTypeManager

    // def of ForceField

    ForceField::ForceField() : _atom_type_manager{}, _bond_type_manager{}
    {
    }

    bool ForceField::def_atomtype(std::string name)
    {
        return _atom_type_manager.def(name);
    }

    bool ForceField::def_bondtype(std::string name, AtomType itype, AtomType jtype)
    {
        return _bond_type_manager.def_bondtype(name, itype, jtype);
    }

}