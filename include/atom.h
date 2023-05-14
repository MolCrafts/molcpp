#pragma once
#include "algo.h"
#include "dict.h"
#include "itemtype.h"
#include "xtensor/xarray.hpp"
#include <vector>
#include <memory>
#include <chemfiles.hpp>

namespace molcpp
{

    class Atom;
    using AtomPtr = std::shared_ptr<Atom>;
    class Bond;
    using BondPtr = std::shared_ptr<Bond>;

    using AtomVec = std::vector<AtomPtr>;
    using BondVec = std::vector<BondPtr>;

    class Atom
    {

    public:
        /**
         * @brief Construct a new Atom object
         * 
         */
        Atom();

        /**
         * @brief add a connected bond 
         * 
         * @return true 
         * @return false 
         * @note if the bond is already connected, return false
         */
        bool add_bond(BondPtr);

        /**
         * @brief delete a connected bond 
         * 
         * @return true 
         * @return false 
         */
        bool del_bond(BondPtr);

        /**
         * @brief check if the atom has a connected bond 
         * 
         * @return true 
         * @return false 
         */
        bool has_bond(BondPtr);

        /**
         * @brief check if the atom is a neighbor of the given atom 
         * 
         * @return true 
         * @return false 
         */
        bool is_nbr(AtomPtr);
        
        /**
         * @brief Get a list of connected atoms 
         * 
         * @return std::vector<AtomPtr> 
         */
        std::vector<AtomPtr> get_nbrs();

        /**
         * @brief Get a property by key 
         * 
         * @tparam T 
         * @param key 
         * @return T 
         */
        template<typename T>
        T get(const std::string& key, T _default = T())
        {
            if (_properties.has(key)) return _properties.get<T>(key);
            else if(_type->has(key)) return _type->get<T>(key);
            else return _default;
        };

        /**
         * @brief 
         * 
         * @param key 
         * @param value 
         */
        void set(const std::string& key, const AtomProperty& value);

        /**
         * @brief Set the atomtype
         * 
         */
        void set_type(const AtomTypePtr&);
        
        /**
         * @brief Get the atomtype
         * 
         * @return const AtomTypePtr& 
         */
        const AtomTypePtr& get_type();

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool equal_to(const Atom&) const;

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool equal_to(const AtomPtr&) const;

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool operator==(const Atom&) const;

        /**
         * @brief Get id of this atom
         * 
         */
        const size_t get_id() const;

        void set_position(const xt::xarray<double>& pos);

        const xt::xarray<double>& get_position() const;

    private:
        AtomTypePtr _type;
        AtomPropertyDict _properties;
        std::vector<BondPtr> _bonds;
        size_t _id;
        xt::xarray<double> _pos; 
    };

    // factory function
    AtomPtr new_atom();
    AtomPtr new_atom(const AtomTypePtr& type);
    AtomPtr new_atom(const chemfiles::Atom& chflAtom);

    chemfiles::Atom to_chemfiles(const AtomPtr& atom);

}
