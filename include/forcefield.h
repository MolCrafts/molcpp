#ifndef FORCEFIELD_H
#define FORCEFIELD_H
#include <string>
#include <vector>
#include <memory>
#include "mplog.h"
namespace MolCpp
{

    class AtomType
    {
        public:
            AtomType(std::string name) : _name{name} {};

        private:
            std::string _name;
    };

    // using AtomTypePtr = std::shared_ptr<AtomType>;

    class AtomTypeManager
    {

        public:
            AtomTypeManager();
            AtomType get_by_type(std::string tname);
            bool def(std::string name);
            size_t get_ntypes() const { return _atom_types.size(); }

            bool operator == (const AtomType& other) const
            {
                if (other._name == _name)
                    return true;
                else
                    return false;
            }

        private:
            std::vector<AtomType> _atom_types;

    };

    class BondType
    {
        public:
            BondType(std::string name, const AtomType& _itype, const AtomType& _jtype) : _name{name}, _itomtype{_itype}, _jtomtype{_jtype} {};

            AtomType get_itype() const { return _itomtype; }
            AtomType get_jtype() const { return _jtomtype; }

            bool opertaor == (const BondType& other) const
            {
                if (other.get_itype() == _itomtype && other.get_jtype() == _jtomtype)
                    return true;
                else if (other.get_itype() == _jtomtype && other.get_jtype() == _itomtype)
                    return true;
                else
                    return false;
            }


        private:
            std::string _name;
            AtomType _itomtype, _jtomtype;

    };

    class BondTypeManager
    {
        public:
            BondTypeManager();
            BondType get(std::string tname);
            BondType get(const AtomType& itype, const AtomType& jtype);
            bool def_bondtype(std::string name, AtomType itype, AtomType jtype);
            size_t get_ntypes() const { return _bond_types.size(); }

        private:
            std::vector<BondType> _bond_types;
    };

    class ForceField
    {

        public:
            ForceField();
            bool def(std::string name);
            bool def_bondtype(std::string name, AtomType itype, AtomType jtype);

        private:
            AtomTypeManager _atom_type_manager;
            BondTypeManager _bond_type_manager;

    };

}

#endif