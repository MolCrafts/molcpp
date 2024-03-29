#pragma once

#include "algo.h"
#include "atom.h"
#include "bond.h"
#include "mplog.h"
#include "graph.h"
#include <chemfiles.hpp>
#include <vector>

namespace molcpp
{
    using AtomVec = std::vector<Atom *>;
    using BondVec = std::vector<Bond *>;
    class Topology; // forward declearation
    using TopoVec = std::vector<Topology *>;
    
    class Topology
    {

    public:
        /**
         * @brief Construct a new Topology object
         *
         */
        Topology();

        ~Topology();

        /**
         * @brief Add a pointer of exsit atom to this topology
         *
         * @return true
         * @return false
         */
        void add_atom(Atom *);

        /**
         * @brief check if the topology has an atom
         *
         * @return true
         * @return false
         */
        bool has_atom(Atom *);

        /**
         * @brief
         *
         */
        void del_atom(Atom *);

        /**
         * @brief Create an atom in this topology
         *
         * @return AtomPtr
         */
        Atom *create_atom(const std::string &name = "", Vector3D pos = {0, 0, 0});
        // AtomPtr new_atom(const chemfiles::Atom &);

        /**
         * @brief Get the atoms from this topology and its sub-topologies
         *
         * @return AtomVec
         */
        AtomVec get_atoms();

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        void add_bond(Bond *);

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool has_bond(Bond *);

        bool has_bond(Atom *, Atom *);

        /**
         * @brief Create a bond object
         *
         * @return BondPtr
         */
        Bond *create_bond(Atom *, Atom *);

        /**
         * @brief Create a bond object
         *
         * @return BondPtr
         */
        Bond *create_bond(size_t, size_t);

        /**
         * @brief
         *
         */
        void connect(size_t, size_t);
        void check_connect(size_t, size_t);
        // TODO: connect(size_t, size_t, size_t) etc.

        /**
         * @brief Get the bond object
         *
         * @return const BondPtr
         */
        Bond *get_bond(Atom *, Atom *);
        Bond *get_bond(size_t, size_t);

        /**
         * @brief Get the bonds object
         *
         * @return BondVec
         */
        BondVec get_bonds() const;

        /**
         * @brief Get the natoms object
         *
         * @return size_t
         */
        size_t get_natoms() const;

        /**
         * @brief Get the nbonds object
         *
         * @return size_t
         */
        size_t get_nbonds() const;

        /**
         * @brief
         *
         */
        void del_bond(Bond *);

        /**
         * @brief
         *
         */
        void del_bond(Atom *, Atom *);

        Topology *create_topology();

        void add_topology(Topology *);

        template <typename T>
        std::vector<T> get(const std::string &name) const
        {
            std::vector<T> arr(get_natoms());
            for (size_t i = 0; i < get_natoms(); ++i)
            {
                arr[i] = _atoms[i]->get<T>(name);
            }
            return arr;
        }

        void set(const std::string &, const std::vector<AtomProperty> &);

        BondConnect get_bond_connect();

        AngleConnect get_angle_connect();

        DihedralConnect get_dihedral_connect();

    private:
        AtomVec _atoms;
        BondVec _bonds;
        TopoVec _topos;

        Graph _graph;
    };

    // factory function
    std::unique_ptr<Topology> from_chemfiles(const chemfiles::Topology &chflTopology);
    chemfiles::Topology to_chemfiles(Topology*);

    std::unique_ptr<Topology> create_topology();
}