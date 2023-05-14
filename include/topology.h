#pragma once

#include <chemfiles.hpp>
#include "atom.h"
#include "bond.h"
#include "algo.h"
#include "mplog.h"
#include <xtensor/xarray.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xview.hpp>

namespace molcpp
{

    class Topology;
    using TopoVec = std::vector<Topology>;
    using BondConnect = std::vector<std::vector<size_t>>;

    class Topology
    {

        public:

            /**
             * @brief Construct a new Topology object
             * 
             */
            Topology();
            
            /**
             * @brief Construct a new Topology from Chemfiles' Topology
             * 
             * @param natoms 
             * @param nbonds 
             */
            // Topology(const chemfiles::Topology& chflTopology);
            
            /**
             * @brief Add an exsit atom to the topology
             * 
             * @return true 
             * @return false 
             */
            bool add_atom(AtomPtr);
            
            /**
             * @brief check if the topology has an atom
             * 
             * @return true 
             * @return false 
             */
            bool has_atom(AtomPtr);

            /**
             * @brief 
             * 
             */
            bool del_atom(AtomPtr);
            
            /**
             * @brief Create a 
             * 
             * @return AtomPtr 
             */
            AtomPtr new_atom();
            // AtomPtr new_atom(const chemfiles::Atom &);
            
            /**
             * @brief Get the atoms object
             * 
             * @return AtomVec 
             */
            AtomVec get_atoms() const { return _atoms; }
            
            /**
             * @brief 
             * 
             * @return true 
             * @return false 
             */
            bool add_bond(BondPtr);
            
            /**
             * @brief 
             * 
             * @return true 
             * @return false 
             */
            bool has_bond(BondPtr);
            
            /**
             * @brief Create a bond object
             * 
             * @return BondPtr 
             */
            BondPtr new_bond(AtomPtr, AtomPtr);
            
            /**
             * @brief Create a bond object
             * 
             * @return BondPtr 
             */
            BondPtr new_bond(size_t, size_t);

            /**
             * @brief 
             * 
             */
            void connect(size_t, size_t);

            

            // TODO: connect(size_t, size_t, size_t) etc.

            /**
             * @brief Get the bond object
             * 
             * @return const BondPtr 
             */
            const BondPtr get_bond(const AtomPtr&, const AtomPtr&) const;

            /**
             * @brief Get the bonds object
             * 
             * @return BondVec 
             */
            BondVec get_bonds() const { return _bonds; }

            /**
             * @brief Get the natoms object
             * 
             * @return size_t 
             */
            size_t get_natoms() const { return _atoms.size(); }

            /**
             * @brief Get the nbonds object
             * 
             * @return size_t 
             */
            size_t get_nbonds() const { return _bonds.size(); }

            /**
             * @brief 
             * 
             */
            bool del_bond(BondPtr);

            /**
             * @brief 
             * 
             */
            bool del_bond(const AtomPtr&, const AtomPtr& );

            template<typename T>
            xt::xarray<T> get(const std::string& name) const
            {
                xt::xarray<T> arr = xt::empty<T>({get_natoms()});
                for (size_t i = 0; i < get_natoms(); ++i)
                {
                    arr[i] = _atoms[i]->get<T>(name);
                }
                return arr;
            }

            void set(const std::string&, const xt::xarray<AtomProperty>&);

            void set_positions(const xt::xarray<double>&);

            const xt::xarray<double> get_positions() const;

        private:

            AtomVec _atoms;
            BondVec _bonds;
            TopoVec _topos;

            BondConnect _bondConnect;

    };

    using TopologyPtr = std::shared_ptr<Topology>;

    // factory function
    TopologyPtr new_topology();
    TopologyPtr new_topology(const chemfiles::Topology& chflTopology);

    chemfiles::Topology save_topology(const TopologyPtr &);
}