#ifndef MOLPACK_GEOM_H
#define MOLPACK_GEOM_H

#include <type_traits>
#include <vector>

#include "mat3.hpp"
#include "vec3.hpp"

namespace molpack {

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto translate(Vec3<T>& v, Vec3<T>& t) {
  return v + t;
}
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto rotate(Vec3<T>& v, Mat3<T>& rot) {
  return rot * v;
}
/**
 * @brief Rotate a vector around an axis by an angle theta. The rotate matrix is calculated via
 * Rodrigues' rotation formula. Ref: https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
 *
 * @param v
 * @param axis
 * @param theta
 * @return Vec3<T>&
 */
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto rotate(Vec3<T>& v, Vec3<T>& axis, T theta) {

  // convert degree to radian
    theta = theta * M_PI / 180.0;

  auto rot = Mat3<double>::zero();

  // normalize axis
    axis /= axis.norm();

 Mat3<double> K{
     0, -axis[2], axis[1],
     axis[2], 0, -axis[0],
     -axis[1], axis[0], 0};

    rot = Mat3<double>::unit() + sin(theta) * K + (1 - cos(theta)) * K.dot(K);

  return rotate(v, rot);
}
/**
 * @brief Rotate a vector around the x, y, z axis by alpha, beta, gamma respectively. The rotate
 * matrix is calculated via Euler angles. Ref: https://en.wikipedia.org/wiki/Euler_angles
 *
 * @param v
 * @param alpha
 * @param beta
 * @param gamma
 * @return Vec3<T>&
 */
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto rotate(Vec3<T>& v, T alpha, T beta, T gamma) {

// convert degree to radian
    alpha = alpha * M_PI / 180.0;
    beta = beta * M_PI / 180.0;
    gamma = gamma * M_PI / 180.0;

  auto rot = Mat3<double>::zero();

  double ca = cos(alpha);
  double sa = sin(alpha);
  double cb = cos(beta);
  double sb = sin(beta);
  double cg = cos(gamma);
  double sg = sin(gamma);

  rot[0] = ca * cb * cg - sa * sg;
  rot[1] = -ca * cb * sg - sa * cg;
  rot[2] = ca * sb;
  rot[3] = sa * cb * cg + ca * sg;
  rot[4] = -sa * cb * sg + ca * cg;
  rot[5] = sa * sb;
  rot[6] = -sb * cg;
  rot[7] = sb * sg;
  rot[8] = cb;

  return rotate(v, rot);
}
}  // namespace molpack

#endif  // MOLPACK_GEOM_H