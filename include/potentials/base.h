#pragma once

#include "../mperror.h"
#include <map>
#include <functional>
#include <type_traits>

namespace molcpp
{
    class Potential
    {
    public:
        Potential() = default;
        ~Potential() = default;

    private:
    };

    class BondPotential : public Potential
    {
    public:
        BondPotential() = default;
        ~BondPotential() = default;

        virtual double energy(double);
        virtual double force(double);

    private:
    };

    class BondType;

    class PotentialMap
    {

    public:
        using BondCreator = BondPotential *(*)();
        using BondPotRegistry = std::map<std::string, BondCreator>;
        static void register_bond_potential(const std::string &pot_name, BondCreator creator)
        {
            _registered_bond_potentials[pot_name] = creator;
        }

        static BondPotential *create_bond_potential(const std::string &pot_name)
        {
            auto it = _registered_bond_potentials.find(pot_name);
            if (it != _registered_bond_potentials.end())
            {
                return it->second();
            }
            else
            {
                throw KeyError("Bond potential not found");
            }
        }

        PotentialMap() = default;
        ~PotentialMap() = default;

        BondPotential *def(BondType *bond_type, const std::string &style)
        {
            auto it = _bond_potential_map.find(bond_type);
            if (it == _bond_potential_map.end())
            {
                auto pot = create_bond_potential(style);
                _bond_potential_map[bond_type] = pot;
                return pot;
            }
            else
            {
                throw KeyError("Bond potential already defined");
            }
        }

        BondPotential *get(BondType *bond_type)
        {
            return _bond_potential_map[bond_type];
        }

        template <typename T>
        class RegisterPotential
        {
        public:
            RegisterPotential(std::string pot_name, T creator)
            {
                if (std::is_same<T, BondCreator>::value)
                    register_bond_potential(pot_name, creator);
                // elif (std::is_same<T, AngleCreator>::value)
                //     register_angle_potential(pot_name, creator);
                // elif (std::is_same<T, DihedralCreator>::value)
                //     register_dihedral_potential(pot_name, creator);
                // elif (std::is_same<T, ImproperCreator>::value)
                //     register_improper_potential(pot_name, creator);
                // elif (std::is_same<T, PairCreator>::value)
                //     register_pair_potential(pot_name, creator);
                else
                    throw TypeError("Invalid potential creator type");
            }
        };

    private:
        static inline BondPotRegistry _registered_bond_potentials = {};
        std::map<BondType *, BondPotential *> _bond_potential_map;
    };

}