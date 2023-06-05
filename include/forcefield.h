#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "mplog.h"
#include "mperror.h"
#include "itemtype.h"
#include "bond.h"
#include "potentials/base.h"

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
        BondType* def_bondtype(const std::string&, AtomType*, AtomType*, const std::string& style="");

        /**
         * @brief Define a bond type
         * 
         * @return BondType* 
         */
        BondType* def_bondtype(const std::string&, const std::string&, const std::string&, const std::string& style="");

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

        double compute_bond_energy(Bond*);

        // bool match_atom(const AtomPtr&);
        // bool match_bond(const BondPtr&);

    private:
        AtomTypeManager _atom_type_manager;
        BondTypeManager _bond_type_manager;

        PotentialMap _potential_map;
    };

}