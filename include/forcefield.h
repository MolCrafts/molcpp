# pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "mplog.h"
namespace MolCpp
{

    class AtomType
    {
        public:
            AtomType(const std::string&);
            std::string get_name() const { return _name; };
            bool operator== (const AtomType&) const;
            bool operator!= (const AtomType&) const;
            
        private:
            std::string _name;
    };

    using AtomTypePtr = std::shared_ptr<AtomType>;

    class AtomTypeManager
    {

        public:
            AtomTypeManager();
            /// @brief define a atomtype by its name
            /// @param  const std::string&
            /// @return true if success else false
            AtomTypePtr def(const std::string&);
            /// @brief get a atomtype by its name
            /// @param  const std::string&
            /// @return AtomType
            std::optional<AtomTypePtr> get(std::string);
            size_t get_ntypes() const { return _atom_types.size(); }


        private:
            std::vector<AtomTypePtr> _atom_types;

    };

    // class BondType
    // {
    //     public:
    //         BondType(const std::string& name, const AtomType& _itype, const AtomType& _jtype) : _name{name}, _itomtype{_itype}, _jtomtype{_jtype} {};

    //         AtomType get_itype() const { return _itomtype; }
    //         AtomType get_jtype() const { return _jtomtype; }
    //         std::string get_name() const { return _name; }

    //         bool operator== (const BondType&) const;

    //     private:
    //         std::string _name;
    //         AtomType _itomtype, _jtomtype;

    // };

    // class BondTypeManager
    // {
    //     public:
    //         BondTypeManager();
    //         std::optional<BondType> get(const std::string& tname);
    //         std::optional<BondType> get(const AtomType& itype, const AtomType& jtype);
    //         BondType def(const std::string&, const AtomType&, const AtomType&);
    //         size_t get_ntypes() const { return _bond_types.size(); }

    //     private:
    //         std::vector<BondType> _bond_types;
    // };

    class ForceField
    {

        public:
            ForceField();
            AtomTypePtr def_atomtype(std::string name);
            size_t get_natomtypes() const { return _atom_type_manager.get_ntypes(); }
            // bool def_bondtype(std::string name, AtomType itype, AtomType jtype);

        private:
            AtomTypeManager _atom_type_manager;
            // BondTypeManager _bond_type_manager;

    };

}