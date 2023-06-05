#pragma once

#include "base.h"

namespace molcpp
{
    class BondHarmonic : public BondPotential
    {
        public:
            BondHarmonic();

            void settings(double, double);

            double energy(double r) override;

            double force(double r) override;

        private:
            double _K, _r0;
    };

    BondPotential* create_bond_harmonic()
    {
        LOG_DEBUG("Creating bond harmonic potential");
        return new BondHarmonic();
    }

    PotentialMap::RegisterPotential register_potential("harmonic", create_bond_harmonic);

    // TODO: is any possible to convert create_bond_harmonic to a lambda function?
    // bool PotentialMap::register_bond_potential = PotentialMap::register_bond_potential("harmonic", [](){ return new BondHarmonic();});

    // and finally:
    // #define REGISTER_POT(T, U) bool is_registered_##T = \
    PotentialMap::register_bond_potential(#T, [](){ return new U();})

    // REGISTER_POT(harmonic, BondHarmonic);

}