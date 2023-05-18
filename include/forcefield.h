#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "mplog.h"
#include "mperror.h"
#include "itemtype.h"

namespace molcpp
{

    class ForceField
    {

    public:
        /**
         * @brief Construct a new Force Field object
         * 
         */
        ForceField();

        /**
         * @brief Define an atom type
         * 
         * @return AtomTypePtr 
         */
        AtomTypePtr def_atomtype(const std::string&);

        /**
         * @brief Get the number of defined atomtypes
         * 
         * @return size_t 
         */
        size_t get_natomtypes();

        /**
         * @brief Get the atomtype object with given name
         * 
         * @return std::optional<AtomTypePtr> 
         */
        std::optional<AtomTypePtr> get_atomtype(const std::string&);

        /**
         * @brief Define a bond type
         * 
         * @return BondTypePtr 
         */
        BondTypePtr def_bondtype(const std::string&, const AtomTypePtr&, const AtomTypePtr&);

        /**
         * @brief Define a bond type
         * 
         * @return BondTypePtr 
         */
        BondTypePtr def_bondtype(const std::string&, const std::string&, const std::string&);

        /**
         * @brief Get the number of defined bondtypes
         * 
         * @return size_t 
         */
        size_t get_nbondtypes();

        /**
         * @brief Get the bondtype object with given name
         * 
         * @return std::optional<BondTypePtr> 
         */
        std::optional<BondTypePtr> get_bondtype(const std::string&);

        /**
         * @brief Get the bondtype object with given atomtypes
         * 
         * @return std::optional<BondTypePtr> 
         */
        std::optional<BondTypePtr> get_bondtype(const AtomTypePtr&, const AtomTypePtr&);

        // bool match_atom(const AtomPtr&);
        // bool match_bond(const BondPtr&);

    private:
        AtomTypeManager _atom_type_manager;
        BondTypeManager _bond_type_manager;
    };

}