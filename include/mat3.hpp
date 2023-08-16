#ifndef MOLPACK_Mat_H_
#define MOLPACK_Mat_H_
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

#include "vec3.hpp"
namespace molpack {

template <typename T>
class Mat3;

template <typename T>
struct is_arithmetic_mat3 : std::false_type {};

template <typename T>
struct is_arithmetic_mat3<Mat3<T>> : std::is_arithmetic<T> {};

template <typename T>
class Mat3 {
private:
  T inner_[9]{};

public:
  Mat3<T>() = default;
  Mat3<T>(const T& m00, const T& m01, const T& m02, const T& m10, const T& m11, const T& m12,
          const T& m20, const T& m21, const T& m22)
      : inner_{m00, m01, m02, m10, m11, m12, m20, m21, m22} {}

  inline static Mat3<T> zero() {
    return Mat3<T>(0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  inline static Mat3<T> unit() {
    return Mat3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
  }

  inline const T& get(int i, int j) {
    return inner_[i * 3 + j];
  }

  inline void set(int i, int j, const T& value) {
    inner_[i * 3 + j] = value;
  }

  inline const T& operator[](std::size_t index) const {
    return inner_[index];
  }
  inline T& operator[](std::size_t index) {
    return inner_[index];
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline friend auto operator+(const Mat3<T>& lhs, const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      return Mat3<decltype(T{} + U{})>(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs,
                                       lhs[4] + rhs, lhs[5] + rhs, lhs[6] + rhs, lhs[7] + rhs,
                                       lhs[8] + rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      return Mat3<decltype(T{} + U{}[0])>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2],
                                          lhs[3] + rhs[3], lhs[4] + rhs[4], lhs[5] + rhs[5],
                                          lhs[6] + rhs[6], lhs[7] + rhs[7], lhs[8] + rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat are allowed");
    }
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
            typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline friend auto operator+(const U& lhs, const Mat3<T>& rhs) {
    return rhs + lhs;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline friend auto operator-(const Mat3<T>& lhs, const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      return Mat3<decltype(T{} - U{})>(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs,
                                       lhs[4] - rhs, lhs[5] - rhs, lhs[6] - rhs, lhs[7] - rhs,
                                       lhs[8] - rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      return Mat3<decltype(T{} - U{}[0])>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2],
                                          lhs[3] - rhs[3], lhs[4] - rhs[4], lhs[5] - rhs[5],
                                          lhs[6] - rhs[6], lhs[7] - rhs[7], lhs[8] - rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
  }

  template <typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline Mat3<T> operator-() const {
    return {-inner_[0], -inner_[1], -inner_[2], -inner_[3], -inner_[4],
            -inner_[5], -inner_[6], -inner_[7], -inner_[8]};
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
            typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline friend auto operator-(const U& lhs, const Mat3<T>& rhs) {
    return Mat3<decltype(U{} - T{})>{lhs - rhs[0], lhs - rhs[1], lhs - rhs[2],
                                     lhs - rhs[3], lhs - rhs[4], lhs - rhs[5],
                                     lhs - rhs[6], lhs - rhs[7], lhs - rhs[8]};
  }

  template <typename U>
  inline friend auto operator*(const Mat3<T>& lhs, const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      return Mat3<decltype(T{} * U{})>(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs,
                                       lhs[4] * rhs, lhs[5] * rhs, lhs[6] * rhs, lhs[7] * rhs,
                                       lhs[8] * rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      return Mat3<decltype(T{} * U{}[0])>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2],
                                          lhs[3] * rhs[3], lhs[4] * rhs[4], lhs[5] * rhs[5],
                                          lhs[6] * rhs[6], lhs[7] * rhs[7], lhs[8] * rhs[8]);
    } else if constexpr (is_arithmetic_vec3<U>::value) {
      return Vec3<decltype(T{} * U{}[0])>(lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2],
                                          lhs[3] * rhs[0] + lhs[4] * rhs[1] + lhs[5] * rhs[2],
                                          lhs[6] * rhs[0] + lhs[7] * rhs[1] + lhs[8] * rhs[2]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
            typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline friend auto operator*(const U& lhs, const Mat3<T>& rhs) {
    return rhs * lhs;
  }

  template <typename U>
  inline friend auto operator/(const Mat3<T>& lhs, const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      return Mat3<decltype(T{} / U{})>(
          lhs.inner_[0] / rhs, lhs.inner_[1] / rhs, lhs.inner_[2] / rhs, lhs.inner_[3] / rhs,
          lhs.inner_[4] / rhs, lhs.inner_[5] / rhs, lhs.inner_[6] / rhs, lhs.inner_[7] / rhs,
          lhs.inner_[8] / rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      return Mat3<decltype(T{} / U{}[0])>(
          lhs.inner_[0] / rhs[0], lhs.inner_[1] / rhs[1], lhs.inner_[2] / rhs[2],
          lhs.inner_[3] / rhs[3], lhs.inner_[4] / rhs[4], lhs.inner_[5] / rhs[5],
          lhs.inner_[6] / rhs[6], lhs.inner_[7] / rhs[7], lhs.inner_[8] / rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
            typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline friend auto operator/(const U& lhs, const Mat3<T>& rhs) {
    return Mat3<decltype(U{} / T{})>{lhs / rhs[0], lhs / rhs[1], lhs / rhs[2],
                                     lhs / rhs[3], lhs / rhs[4], lhs / rhs[5],
                                     lhs / rhs[6], lhs / rhs[7], lhs / rhs[8]};
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline Mat3<T>& operator+=(const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      inner_[0] = static_cast<T>(inner_[0] + rhs);
      inner_[1] = static_cast<T>(inner_[1] + rhs);
      inner_[2] = static_cast<T>(inner_[2] + rhs);
      inner_[3] = static_cast<T>(inner_[3] + rhs);
      inner_[4] = static_cast<T>(inner_[4] + rhs);
      inner_[5] = static_cast<T>(inner_[5] + rhs);
      inner_[6] = static_cast<T>(inner_[6] + rhs);
      inner_[7] = static_cast<T>(inner_[7] + rhs);
      inner_[8] = static_cast<T>(inner_[8] + rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      inner_[0] = static_cast<T>(inner_[0] + rhs[0]);
      inner_[1] = static_cast<T>(inner_[1] + rhs[1]);
      inner_[2] = static_cast<T>(inner_[2] + rhs[2]);
      inner_[3] = static_cast<T>(inner_[3] + rhs[3]);
      inner_[4] = static_cast<T>(inner_[4] + rhs[4]);
      inner_[5] = static_cast<T>(inner_[5] + rhs[5]);
      inner_[6] = static_cast<T>(inner_[6] + rhs[6]);
      inner_[7] = static_cast<T>(inner_[7] + rhs[7]);
      inner_[8] = static_cast<T>(inner_[8] + rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline Mat3<T>& operator-=(const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      inner_[0] = static_cast<T>(inner_[0] - rhs);
      inner_[1] = static_cast<T>(inner_[1] - rhs);
      inner_[2] = static_cast<T>(inner_[2] - rhs);
      inner_[3] = static_cast<T>(inner_[3] - rhs);
      inner_[4] = static_cast<T>(inner_[4] - rhs);
      inner_[5] = static_cast<T>(inner_[5] - rhs);
      inner_[6] = static_cast<T>(inner_[6] - rhs);
      inner_[7] = static_cast<T>(inner_[7] - rhs);
      inner_[8] = static_cast<T>(inner_[8] - rhs);

    } else if constexpr (is_arithmetic_mat3<U>::value) {
      inner_[0] = static_cast<T>(inner_[0] - rhs[0]);
      inner_[1] = static_cast<T>(inner_[1] - rhs[1]);
      inner_[2] = static_cast<T>(inner_[2] - rhs[2]);
      inner_[3] = static_cast<T>(inner_[3] - rhs[3]);
      inner_[4] = static_cast<T>(inner_[4] - rhs[4]);
      inner_[5] = static_cast<T>(inner_[5] - rhs[5]);
      inner_[6] = static_cast<T>(inner_[6] - rhs[6]);
      inner_[7] = static_cast<T>(inner_[7] - rhs[7]);
      inner_[8] = static_cast<T>(inner_[8] - rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline Mat3<T>& operator*=(const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      inner_[0] = static_cast<T>(inner_[0] * rhs);
      inner_[1] = static_cast<T>(inner_[1] * rhs);
      inner_[2] = static_cast<T>(inner_[2] * rhs);
      inner_[3] = static_cast<T>(inner_[3] * rhs);
      inner_[4] = static_cast<T>(inner_[4] * rhs);
      inner_[5] = static_cast<T>(inner_[5] * rhs);
      inner_[6] = static_cast<T>(inner_[6] * rhs);
      inner_[7] = static_cast<T>(inner_[7] * rhs);
      inner_[8] = static_cast<T>(inner_[8] * rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      inner_[0] = static_cast<T>(inner_[0] * rhs[0]);
      inner_[1] = static_cast<T>(inner_[1] * rhs[1]);
      inner_[2] = static_cast<T>(inner_[2] * rhs[2]);
      inner_[3] = static_cast<T>(inner_[3] * rhs[3]);
      inner_[4] = static_cast<T>(inner_[4] * rhs[4]);
      inner_[5] = static_cast<T>(inner_[5] * rhs[5]);
      inner_[6] = static_cast<T>(inner_[6] * rhs[6]);
      inner_[7] = static_cast<T>(inner_[7] * rhs[7]);
      inner_[8] = static_cast<T>(inner_[8] * rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline Mat3<T>& operator/=(const U& rhs) {
    if constexpr (std::is_arithmetic_v<U>) {
      inner_[0] = static_cast<T>(inner_[0] / rhs);
      inner_[1] = static_cast<T>(inner_[1] / rhs);
      inner_[2] = static_cast<T>(inner_[2] / rhs);
      inner_[3] = static_cast<T>(inner_[3] / rhs);
      inner_[4] = static_cast<T>(inner_[4] / rhs);
      inner_[5] = static_cast<T>(inner_[5] / rhs);
      inner_[6] = static_cast<T>(inner_[6] / rhs);
      inner_[7] = static_cast<T>(inner_[7] / rhs);
      inner_[8] = static_cast<T>(inner_[8] / rhs);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      inner_[0] = static_cast<T>(inner_[0] / rhs[0]);
      inner_[1] = static_cast<T>(inner_[1] / rhs[1]);
      inner_[2] = static_cast<T>(inner_[2] / rhs[2]);
      inner_[3] = static_cast<T>(inner_[3] / rhs[3]);
      inner_[4] = static_cast<T>(inner_[4] / rhs[4]);
      inner_[5] = static_cast<T>(inner_[5] / rhs[5]);
      inner_[6] = static_cast<T>(inner_[6] / rhs[6]);
      inner_[7] = static_cast<T>(inner_[7] / rhs[7]);
      inner_[8] = static_cast<T>(inner_[8] / rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline bool operator==(const U& rhs) const {
    if constexpr (is_arithmetic_mat3<U>::value)
      return inner_[0] == rhs[0] && inner_[1] == rhs[1] && inner_[2] == rhs[2] &&
             inner_[3] == rhs[3] && inner_[4] == rhs[4] && inner_[5] == rhs[5] &&
             inner_[6] == rhs[6] && inner_[7] == rhs[7] && inner_[8] == rhs[8];
  }

  template <typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline T determinant() const {
    double determinant = 0.0;
    determinant += inner_[0] * (inner_[4] * inner_[8] - inner_[7] * inner_[5]);
    determinant -= inner_[1] * (inner_[3] * inner_[8] - inner_[5] * inner_[6]);
    determinant += inner_[2] * (inner_[3] * inner_[7] - inner_[4] * inner_[6]);
    return determinant;
  }

  template <typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline auto invert() const {
    auto determinant = this->determinant();

    if (determinant < std::numeric_limits<double>::epsilon())
      throw std::runtime_error("this matrix is not invertible");

    auto invdet = 1.0 / determinant;
    double xx = (inner_[4] * inner_[8] - inner_[7] * inner_[5]) * invdet;
    double xy = (inner_[2] * inner_[7] - inner_[1] * inner_[8]) * invdet;
    double xz = (inner_[1] * inner_[5] - inner_[2] * inner_[4]) * invdet;

    double yx = (inner_[5] * inner_[6] - inner_[3] * inner_[8]) * invdet;
    double yy = (inner_[0] * inner_[8] - inner_[2] * inner_[6]) * invdet;
    double yz = (inner_[3] * inner_[2] - inner_[0] * inner_[5]) * invdet;

    double zx = (inner_[3] * inner_[7] - inner_[6] * inner_[4]) * invdet;
    double zy = (inner_[6] * inner_[1] - inner_[0] * inner_[7]) * invdet;
    double zz = (inner_[0] * inner_[4] - inner_[3] * inner_[1]) * invdet;

    return Mat3(xx, xy, xz, yx, yy, yz, zx, zy, zz);
  }

  template <typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  inline auto transpose() {
    return Mat3(inner_[0], inner_[3], inner_[6], inner_[1], inner_[4], inner_[7], inner_[2],
                inner_[5], inner_[8]);
  }

  template <typename U, typename = std::enable_if<std::is_arithmetic_v<T>>>
  inline auto dot(const U& rhs) const {
    if constexpr (is_arithmetic_vec3<U>::value) {
      return Vec3<T>(inner_[0] * rhs[0] + inner_[1] * rhs[1] + inner_[2] * rhs[2],
                     inner_[3] * rhs[0] + inner_[4] * rhs[1] + inner_[5] * rhs[2],
                     inner_[6] * rhs[0] + inner_[7] * rhs[1] + inner_[8] * rhs[2]);
    } else if constexpr (is_arithmetic_mat3<U>::value) {
      return Mat3<T>(inner_[0] * rhs[0] + inner_[1] * rhs[3] + inner_[2] * rhs[6], inner_[0] * rhs[1] + inner_[1] * rhs[4] + inner_[2] * rhs[7], inner_[0] * rhs[2] + inner_[1] * rhs[5] + inner_[2] * rhs[8],
                     inner_[3] * rhs[0] + inner_[4] * rhs[3] + inner_[5] * rhs[6], inner_[3] * rhs[1] + inner_[4] * rhs[4] + inner_[5] * rhs[7], inner_[3] * rhs[2] + inner_[4] * rhs[5] + inner_[5] * rhs[8],
                     inner_[6] * rhs[0] + inner_[7] * rhs[3] + inner_[8] * rhs[6], inner_[6] * rhs[1] + inner_[7] * rhs[4] + inner_[8] * rhs[7], inner_[6] * rhs[2] + inner_[7] * rhs[5] + inner_[8] * rhs[8]);
    } else {
      // std::is_arithmetic_v<U> always false, use this to avoid clangd error
      static_assert(std::is_arithmetic_v<U>,
                    "Invalid type: only arithmetic type or Mat3 are allowed");
    }
  }

  inline friend std::ostream& operator<<(std::ostream& os, const Mat3<double>& mat) {
    os << std::endl;
    os << mat[0] << " " << mat[1] << " " << mat[2] << std::endl;
    os << mat[3] << " " << mat[4] << " " << mat[5] << std::endl;
    os << mat[6] << " " << mat[7] << " " << mat[8] << std::endl;
    return os;
  }
};

}  // namespace molpack
#endif