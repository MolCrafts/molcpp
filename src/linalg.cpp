#include "linalg.hpp"

namespace molcpp
{
bool allclose(const Vector3D& a, const Vector3D& b, double rtol, double atol)
 {
    for (size_t i = 0; i < 3; ++i) {
        if (std::abs(a[i] - b[i]) > (atol + rtol * std::abs(b[i]))) {
            return false;
        }
    }
    return true;
}
    
}