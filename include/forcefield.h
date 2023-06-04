#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "atom.h"
#include "bond.h"
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
         * @return AtomType* 
         */
        AtomType* def_atomtype(const std::string&);

        /**
         * @brief Get the number of defined atomtypes
         * 
         * @return size_t 
         */
        size_t get_natomtypes();

        /**
         * @brief Get the atomtype object with given name
         * 
         * @return std::optional<AtomType*> 
         */
        std::optional<AtomType*> get_atomtype(const std::string&);

        /**
         * @brief Define a bond type
         * 
         * @return BondType* 
         */
        BondType* def_bondtype(const std::string&, AtomType*, AtomType*);

        /**
         * @brief Define a bond type
         * 
         * @return BondType* 
         */
        BondType* def_bondtype(const std::string&, const std::string&, const std::string&);

        /**
         * @brief Get the number of defined bondtypes
         * 
         * @return size_t 
         */
        size_t get_nbondtypes();

        /**
         * @brief Get the bondtype object with given name
         * 
         * @return std::optional<BondType*> 
         */
        std::optional<BondType*> get_bondtype(const std::string&);

        /**
         * @brief Get the bondtype object with given atomtypes
         * 
         * @return std::optional<BondType*> 
         */
        std::optional<BondType*> get_bondtype(AtomType*, AtomType*);

        bool match_atom(Atom*);
        bool match_bond(Bond*);

    private:
        AtomTypeManager _atom_type_manager;
        BondTypeManager _bond_type_manager;
    };

}