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

#ifdef BOND_POT
    REGISTER_POT(harmonic, BondHarmonic);
#endif
}
