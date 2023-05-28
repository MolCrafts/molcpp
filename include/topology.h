#pragma once

#include <chemfiles.hpp>
#include "atom.h"
#include "bond.h"
#include "algo.h"
#include "mplog.h"
#include <xtensor/xarray.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xview.hpp>
#include <xtensor/xadapt.hpp>

namespace molcpp
{
    class Topology;  // forward declearation
    using AtomVec = std::vector<Atom *>;
    using BondVec = std::vector<Bond *>;
    using TopoVec = std::vector<Topology *>;
    using AtomTopoMask = std::vector<size_t>;
    using BondConnect = std::vector<std::vector<size_t>>;
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

        bool has_bond(Atom*, Atom*);

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

        void set(const std::string &, const xt::xarray<AtomProperty> &);

        void set_positions(xt::xarray<double> &);

        xt::xarray<double> get_positions();

        const BondConnect get_bond_connect() const { return _bondConnect; }

    private:

        AtomVec _atoms;
        BondVec _bonds;
        TopoVec _topos;

        BondConnect _bondConnect;
    };

    // factory function
    std::unique_ptr<Topology> from_chemfiles(const chemfiles::Topology &chflTopology);
    chemfiles::Topology to_chemfiles(const Topology &);

    std::unique_ptr<Topology> create_topology();
}