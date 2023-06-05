#include "potentials/bond_harmonic.h"

namespace molcpp
{
    BondHarmonic::BondHarmonic()
    {
    }

    void BondHarmonic::settings(double K, double r0)
    {
        _K = K;
        _r0 = r0;
    }

    double BondHarmonic::energy(double r)
    {
        return 0.5 * _K * (r - _r0) * (r - _r0);
    }

    double BondHarmonic::force(double r)
    {
        return _K * (r - _r0);
    }
}