#include "forcefield.h"

namespace molcpp
{

    ForceField::ForceField() : _atom_type_manager{}// , _bond_type_manager{}
    {
    }

    AtomTypePtr ForceField::def_atomtype(const std::string& name)
    {
        return _atom_type_manager.def(name);
    }

    BondTypePtr ForceField::def_bondtype(const std::string& name, const AtomTypePtr& itype, const AtomTypePtr& jtype)
    {
        return _bond_type_manager.def(name, itype, jtype);
    }

    BondTypePtr ForceField::def_bondtype(const std::string& name, const std::string& itype, const std::string& jtype)
    {
        auto it = get_atomtype(itype);
        auto jt = get_atomtype(jtype);
        if (it && jt)
            return _bond_type_manager.def(name, *it, *jt);
        else
        {
            LOG_ERROR("ForceField::def_bondtype: atom type not found");
            throw std::runtime_error("ForceField::def_bondtype: atom type not found");
        }
    }

    std::optional<AtomTypePtr> ForceField::get_atomtype(const std::string& tname)
    {
        return _atom_type_manager.get(tname);
    }

    std::optional<BondTypePtr> ForceField::get_bondtype(const std::string& tname)
    {
        return _bond_type_manager.get(tname);
    }

    std::optional<BondTypePtr> ForceField::get_bondtype(const AtomTypePtr& itype, const AtomTypePtr& jtype)
    {
        return _bond_type_manager.get(itype, jtype);
    }

    size_t ForceField::get_natomtypes()
    {
        return _atom_type_manager.get_ntypes();
    }

    size_t ForceField::get_nbondtypes()
    {
        return _bond_type_manager.get_ntypes();
    }

    bool ForceField::match_atom(const AtomPtr atom)
    {
        auto at = atom->get_type();
        auto atomtype = get_atomtype(at);
        if (atomtype.has_value())
        {
            atom->set_atomtype(atomtype.value());
            return true;
        }
        else
        {
            return false;
        }
    }
}