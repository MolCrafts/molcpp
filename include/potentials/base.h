#pragma once

#include "../mperror.h"
#include <map>
#include <functional>

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

        double energy(double);
        double force(double);

    private:
    };

    class BondType;

    class PotentialMap
    {

    public:
        using BondCreator = std::function<BondPotential *()>;
        using BondPotRegistry = std::map<std::string, BondCreator>;
        static void registry_bond_potential(const std::string &pot_name, BondCreator creator)
        {
            _registered_bond_potentials[pot_name] = creator;
        }

        static BondPotential *create_bond_potential(const std::string &pot_name)
        {
            return _registered_bond_potentials[pot_name]();
        };

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

    private:
        static BondPotRegistry _registered_bond_potentials;
        std::map<BondType*, BondPotential*> _bond_potential_map;
    };

    PotentialMap::BondPotRegistry PotentialMap::_registered_bond_potentials = {};

}