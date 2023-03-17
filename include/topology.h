#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "atom.h"
#include "bond.h"

namespace MolCpp
{

    using AtomVec = std::vector<AtomPtr>;
    using BondVec = std::vector<BondPtr>;

    class Topology: public Graph
    {

        public:
            Topology() = default;
            Topology(const chemfiles::Topology& chflTopology);
            bool add_atom(AtomPtr);
            AtomPtr new_atom();
            AtomPtr new_atom(const chemfiles::Atom &);
            AtomVec get_atoms() const { return _atoms; }
            bool add_bond(BondPtr);
            BondPtr new_bond(AtomPtr, AtomPtr);
            BondPtr new_bond(size_t, size_t);
            BondVec get_bonds() const { return _bonds; }
            size_t get_natoms() const { return _atoms.size(); }
            size_t get_nbonds() const { return _bonds.size(); }

        protected:
            
            AtomVec _atoms;
            BondVec _bonds;

    };

}

#endif // TOPOLOGY_H