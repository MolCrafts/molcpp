#pragma once

#include <cmath>
#include <type_traits>

#include "mat3.h"
#include "vec3.h"

namespace molcpp
{

template <typename T> static T abs(T value)
{
    if constexpr (std::is_arithmetic_v<T>)
    {
        return value < 0 ? -value : value;
    }
    else
    {
        throw std::runtime_error("abs() is not defined for this type");
    }
}

template <typename T, typename U> static bool approx_eq(const T &lhs, const U &rhs, double eps = 1e-12)
{
    if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>)
    {
        return abs(lhs - rhs) < eps;
    }
    else if constexpr (is_arithmetic_vec3<T>::value && is_arithmetic_vec3<U>::value)
    {
        return abs(lhs[0] - rhs[0]) < eps && abs(lhs[1] - rhs[1]) < eps && abs(lhs[2] - rhs[2]) < eps;
    }
    else if constexpr (is_arithmetic_mat3<T>::value && is_arithmetic_mat3<U>::value)
    {
        return abs(lhs[0][0] - rhs[0][0]) < eps && abs(lhs[0][1] - rhs[0][1]) < eps &&
               abs(lhs[0][2] - rhs[0][2]) < eps && abs(lhs[1][0] - rhs[1][0]) < eps &&
               abs(lhs[1][1] - rhs[1][1]) < eps && abs(lhs[1][2] - rhs[1][2]) < eps &&
               abs(lhs[2][0] - rhs[2][0]) < eps && abs(lhs[2][1] - rhs[2][1]) < eps && abs(lhs[2][2] - rhs[2][2]) < eps;
    }
    else
    {
        throw std::runtime_error("approx_eq() is not defined for this type");
    }
}

} // namespace molcpp