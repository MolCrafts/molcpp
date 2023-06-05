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
        return new BondHarmonic();
    }

    PotentialMap::RegisterPotential register_potential("harmonic", create_bond_harmonic);

}