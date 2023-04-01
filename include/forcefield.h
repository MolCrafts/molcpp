// # pragma once
// #include <string>
// #include <vector>
// #include <memory>
// #include <optional>
// #include "mplog.h"
// #include "topology.h"
// #include "itemtype.h"

// namespace molcpp
// {

//     class ForceField
//     {

//         public:
//             ForceField();
//             AtomTypePtr def_atomtype(std::string name);
//             size_t get_natomtypes() const { return _atom_type_manager.get_ntypes(); }
//             std::optional<AtomTypePtr> get_atomtype(std::string name);
//             BondTypePtr def_bondtype(std::string name, AtomType itype, AtomType jtype);
//             size_t get_nbondtypes() const { return _bond_type_manager.get_ntypes(); }
//             std::optional<BondType> get_bondtype(std::string name);
//             std::optional<BondType> get_bondtype(AtomType itype, AtomType jtype);

//             bool match_atom(const AtomPtr);

//         private:
//             AtomTypeManager _atom_type_manager;
//             BondTypeManager _bond_type_manager;

//     };

// }