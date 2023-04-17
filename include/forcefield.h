#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "mplog.h"
#include "topology.h"
#include "itemtype.h"

namespace molcpp
{

    class ForceField
    {

    public:
        ForceField();
        AtomTypePtr def_atomtype(const std::string&);
        size_t get_natomtypes();
        std::optional<AtomTypePtr> get_atomtype(const std::string&);
        BondTypePtr def_bondtype(const std::string&, const AtomTypePtr&, const AtomTypePtr&);
        BondTypePtr def_bondtype(const std::string&, const std::string&, const std::string&);
        size_t get_nbondtypes();
        std::optional<BondTypePtr> get_bondtype(const std::string&);
        std::optional<BondTypePtr> get_bondtype(const AtomTypePtr&, const AtomTypePtr&);

        bool match_atom(const AtomPtr);

    private:
        AtomTypeManager _atom_type_manager;
        BondTypeManager _bond_type_manager;
    };

}