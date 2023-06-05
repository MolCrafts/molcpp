#pragma once

#include "base.h"

namespace molcpp
{
    class BondHarmonic : public BondPotential
    {
        public:
            BondHarmonic();

            void settings(double, double);

            double energy(double r);

            double force(double r);

        private:
            double _K, _r0;
    };

    PotentialMap::registry_bond_potential("harmonic", []()->BondPotential*{return new BondHarmonic();});
}