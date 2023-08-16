#ifndef MOLPACK_APPROX_H
#define MOLPACK_APPROX_H

#include <cmath>
#include <type_traits>

#include "mat3.hpp"
#include "vec3.hpp"

namespace molpack {

template <typename T>
static T abs(T value) {
  if constexpr (std::is_arithmetic_v<T>) {
    return value < 0 ? -value : value;
  } else {
    throw std::runtime_error("abs() is not defined for this type");
  }
}

template <typename T, typename U>
static bool approx_eq(const T& lhs, const U& rhs, double eps = 1e-12) {
  if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
    return abs(lhs - rhs) < eps;
  } else if constexpr (is_arithmetic_vec3<T>::value && is_arithmetic_vec3<U>::value) {
    return abs(lhs[0] - rhs[0]) < eps && abs(lhs[1] - rhs[1]) < eps && abs(lhs[2] - rhs[2]) < eps;
  } else if constexpr (is_arithmetic_mat3<T>::value && is_arithmetic_mat3<U>::value) {
    std::cout << eps << std::endl;
    for (int i = 0; i < 9; ++i) {
      if (abs(lhs[i] - rhs[i]) > eps) {
        std::cout << i << " : " << abs(lhs[i] - rhs[i]) << std::endl;
      }
    }
    return abs(lhs[0] - rhs[0]) < eps && abs(lhs[1] - rhs[1]) < eps && abs(lhs[2] - rhs[2]) < eps &&
           abs(lhs[3] - rhs[3]) < eps && abs(lhs[4] - rhs[4]) < eps && abs(lhs[5] - rhs[5]) < eps &&
           abs(lhs[6] - rhs[6]) < eps && abs(lhs[7] - rhs[7]) < eps && abs(lhs[8] - rhs[8]) < eps;
   } else {
    throw std::runtime_error("approx_eq() is not defined for this type");
   }
}

}  // namespace molpack

#endif  // MOLPACK_APPROX_H