#pragma once

#include "atom.h"
#include "bond.h"
#include "algo.h"
#include "mplog.h"
#include "chemfiles.hpp"

namespace molcpp
{

    class Topology;
    using TopoVec = std::vector<Topology>;

    class Topology
    {

        public:
            Topology() = default;
            Topology(size_t natoms, size_t nbonds = 0) : _atoms(natoms), _bonds(nbonds) {};
            Topology(const chemfiles::Topology& chflTopology);
            bool add_atom(AtomPtr);
            bool has_atom(AtomPtr);
            AtomPtr create_atom();
            // AtomPtr create_atom(const chemfiles::Atom &);
            AtomVec get_atoms() const { return _atoms; }
            bool add_bond(BondPtr);
            bool has_bond(BondPtr);
            BondPtr create_bond(AtomPtr, AtomPtr);
            BondPtr create_bond(size_t, size_t);
            BondVec get_bonds() const { return _bonds; }
            size_t get_natoms() const { return _atoms.size(); }
            size_t get_nbonds() const { return _bonds.size(); }

        private:

            AtomVec _atoms;
            BondVec _bonds;
            TopoVec _topos;

    };

    using TopologyPtr = std::shared_ptr<Topology>;

    // factory function
    TopologyPtr create_topology();
    TopologyPtr create_topology(size_t, size_t);

}