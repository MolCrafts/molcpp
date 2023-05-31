#include "forcefield.h"

namespace molcpp
{

    ForceField::ForceField() : _atom_type_manager{}, _bond_type_manager{}
    {
    }

    AtomType* ForceField::def_atomtype(const std::string& name)
    {
        return _atom_type_manager.def(name);
    }

    size_t ForceField::get_natomtypes()
    {
        return _atom_type_manager.get_ntypes();
    }

    std::optional<AtomType*> ForceField::get_atomtype(const std::string& tname)
    {
        return _atom_type_manager.get(tname);
    }

    BondType* ForceField::def_bondtype(const std::string& name, AtomType* itype, AtomType* jtype)
    {
        return _bond_type_manager.def(name, itype, jtype);
    }

    BondType* ForceField::def_bondtype(const std::string& name, const std::string& itypename, const std::string& jtypename)
    {
        auto it = get_atomtype(itypename);
        auto jt = get_atomtype(jtypename);
        if (it && jt)
            return _bond_type_manager.def(name, *it, *jt);
        else
        {
            LOG_ERROR("ForceField::def_bondtype: atom type not found");
            throw std::runtime_error("ForceField::def_bondtype: atom type not found");
        }
    }

    size_t ForceField::get_nbondtypes()
    {
        return _bond_type_manager.get_ntypes();
    }

    std::optional<BondType*> ForceField::get_bondtype(const std::string& tname)
    {
        return _bond_type_manager.get(tname);
    }

    std::optional<BondType*> ForceField::get_bondtype(AtomType* itype, AtomType* jtype)
    {
        return _bond_type_manager.get(itype, jtype);
    }

    // bool ForceField::match_atom(const AtomPtr& atom)
    // {
    //     auto at = atom->get_typename();
    //     auto atomtype = get_atomtype(at);
    //     if (atomtype.has_value())
    //     {
    //         atom->set_type(atomtype.value());
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    // bool ForceField::match_bond(const BondPtr& bond)
    // {
    //     auto it = bond->get_itom()->get_type();
    //     auto jt = bond->get_jtom()->get_type();
    //     auto bondtype = get_bondtype(it, jt);
    //     if (bondtype.has_value())
    //     {
    //         bond->set_type(bondtype.value());
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }
}