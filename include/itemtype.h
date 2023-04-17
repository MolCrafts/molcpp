#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "mplog.h"
#include "dict.h"

namespace molcpp
{

    class AtomType
    {
        public:
            AtomType(const std::string&);
            const std::string& get_name() const;
            bool operator== (const AtomType&) const;
            bool operator!= (const AtomType&) const;
            AtomProperty& operator[](const std::string &key);
            
        private:
            AtomPropertyDict _properties;
    };

    using AtomTypePtr = std::shared_ptr<AtomType>;

    AtomTypePtr create_atomtype(const std::string&);

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
            std::optional<AtomTypePtr> get(const std::string&);
            size_t get_ntypes() const { return _atom_types.size(); }


        private:
            std::vector<AtomTypePtr> _atom_types;

    };

    class BondType
    {
        public:
            BondType(const std::string& name, const AtomTypePtr& _itype, const AtomTypePtr& _jtype) : _name{name}, _itomtype{_itype}, _jtomtype{_jtype} {};

            AtomTypePtr get_itype() const { return _itomtype.lock(); }
            AtomTypePtr get_jtype() const { return _jtomtype.lock(); }
            std::string get_name() const { return _name; }

            bool operator== (const BondType&) const;
            BondProperty& operator[](const std::string &key);

        private:
            std::string _name;
            std::weak_ptr<AtomType> _itomtype, _jtomtype;
            BondPropertyDict _properties;

    };

    using BondTypePtr = std::shared_ptr<BondType>;

    BondTypePtr create_bondtype(const std::string&, const AtomTypePtr&, const AtomTypePtr&);

    class BondTypeManager
    {
        public:
            BondTypeManager();
            std::optional<BondTypePtr> get(const std::string& tname);
            std::optional<BondTypePtr> get(const AtomTypePtr& itype, const AtomTypePtr& jtype);
            BondTypePtr def(const std::string&, const AtomTypePtr&, const AtomTypePtr&);
            size_t get_ntypes() const { return _bond_types.size(); }

        private:
            std::vector<BondTypePtr> _bond_types;
    };

}