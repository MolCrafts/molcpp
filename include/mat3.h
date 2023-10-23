#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

#include "vec3.h"

namespace molcpp
{

template <typename T> class Mat3;

template <typename T> struct is_arithmetic_mat3 : std::false_type
{
};

template <typename T> struct is_arithmetic_mat3<Mat3<T>> : std::is_arithmetic<T>
{
};

template <typename T> class Mat3
{
  private:
    T inner_[3][3]{};

  public:
    Mat3<T>() = default;
    Mat3<T>(const T &m00, const T &m01, const T &m02, const T &m10, const T &m11, const T &m12, const T &m20,
            const T &m21, const T &m22)
        : inner_{{m00, m01, m02}, {m10, m11, m12}, {m20, m21, m22}}
    {
    }

    inline static Mat3<T> zero()
    {
        return Mat3<T>(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    inline static Mat3<T> unit()
    {
        return Mat3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
    }

    inline const T *operator[](size_t index) const
    {
        return inner_[index];
    }

    inline T *operator[](size_t index)
    {
        return inner_[index];
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator+(const Mat3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Mat3<decltype(T{} + U{})>(lhs[0][0] + rhs, lhs[0][1] + rhs, lhs[0][2] + rhs, lhs[1][0] + rhs,
                                             lhs[1][1] + rhs, lhs[1][2] + rhs, lhs[2][0] + rhs, lhs[2][1] + rhs,
                                             lhs[2][2] + rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            return Mat3<decltype(T{} + U{}[0][0])>(lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1], lhs[0][2] + rhs[0][2],
                                                   lhs[1][0] + rhs[1][0], lhs[1][1] + rhs[1][1], lhs[1][2] + rhs[1][2],
                                                   lhs[2][0] + rhs[2][0], lhs[2][1] + rhs[2][1], lhs[2][2] + rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat are allowed");
        }
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator+(const U &lhs, const Mat3<T> &rhs)
    {
        return rhs + lhs;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator-(const Mat3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Mat3<decltype(T{} - U{})>(lhs[0][0] - rhs, lhs[0][1] - rhs, lhs[0][2] - rhs, lhs[1][0] - rhs,
                                             lhs[1][1] - rhs, lhs[1][2] - rhs, lhs[2][0] - rhs, lhs[2][1] - rhs,
                                             lhs[2][2] - rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            return Mat3<decltype(T{} - U{}[0][0])>(lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1], lhs[0][2] - rhs[0][2],
                                                   lhs[1][0] - rhs[1][0], lhs[1][1] - rhs[1][1], lhs[1][2] - rhs[1][2],
                                                   lhs[2][0] - rhs[2][0], lhs[2][1] - rhs[2][1], lhs[2][2] - rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
    }

    template <typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Mat3<T> operator-() const
    {
        return {-inner_[0][0], -inner_[0][1], -inner_[0][2], -inner_[1][0], -inner_[1][1],
                -inner_[1][2], -inner_[2][0], -inner_[2][1], -inner_[2][2]};
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator-(const U &lhs, const Mat3<T> &rhs)
    {
        return Mat3<decltype(U{} - T{})>{lhs - rhs[0][0], lhs - rhs[0][1], lhs - rhs[0][2],
                                         lhs - rhs[1][0], lhs - rhs[1][1], lhs - rhs[1][2],
                                         lhs - rhs[2][0], lhs - rhs[2][1], lhs - rhs[2][2]};
    }

    template <typename U> inline friend auto operator*(const Mat3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Mat3<decltype(T{} * U{})>(lhs[0][0] * rhs, lhs[0][1] * rhs, lhs[0][2] * rhs, lhs[1][0] * rhs,
                                             lhs[1][1] * rhs, lhs[1][2] * rhs, lhs[2][0] * rhs, lhs[2][1] * rhs,
                                             lhs[2][2] * rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            return Mat3<decltype(T{} * U{}[0])>(lhs[0][0] * rhs[0][0], lhs[0][1] * rhs[0][1], lhs[0][2] * rhs[0][2],
                                                lhs[1][0] * rhs[1][0], lhs[1][1] * rhs[1][1], lhs[1][2] * rhs[1][2],
                                                lhs[2][0] * rhs[2][0], lhs[2][1] * rhs[2][1], lhs[2][2] * rhs[2][2]);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            return Vec3<decltype(T{} * U{}[0])>(lhs[0][0] * rhs[0] + lhs[0][1] * rhs[1] + lhs[0][2] * rhs[2],
                                                lhs[1][0] * rhs[0] + lhs[1][1] * rhs[1] + lhs[1][2] * rhs[2],
                                                lhs[2][0] * rhs[0] + lhs[2][1] * rhs[1] + lhs[2][2] * rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator*(const U &lhs, const Mat3<T> &rhs)
    {
        return rhs * lhs;
    }

    template <typename U> inline friend auto operator/(const Mat3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Mat3<decltype(T{} / U{})>(lhs[0][0] / rhs, lhs[0][1] / rhs, lhs[0][2] / rhs, lhs[1][0] / rhs,
                                             lhs[1][1] / rhs, lhs[1][2] / rhs, lhs[2][0] / rhs, lhs[2][1] / rhs,
                                             lhs[2][2] / rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            return Mat3<decltype(T{} / U{}[0])>(
                lhs.inner_[0][0] / rhs[0][0], lhs.inner_[0][1] / rhs[0][1], lhs.inner_[0][2] / rhs[0][2],
                lhs.inner_[1][0] / rhs[1][0], lhs.inner_[1][1] / rhs[1][1], lhs.inner_[1][2] / rhs[1][2],
                lhs.inner_[2][0] / rhs[2][0], lhs.inner_[2][1] / rhs[2][1], lhs.inner_[2][2] / rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator/(const U &lhs, const Mat3<T> &rhs)
    {
        return Mat3<decltype(U{} / T{})>{lhs / rhs[0][0], lhs / rhs[0][1], lhs / rhs[0][2],
                                         lhs / rhs[1][0], lhs / rhs[1][1], lhs / rhs[1][2],
                                         lhs / rhs[2][0], lhs / rhs[2][1], lhs / rhs[2][2]};
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Mat3<T> &operator+=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] + rhs);
            inner_[0][1] = static_cast<T>(inner_[0][1] + rhs);
            inner_[0][2] = static_cast<T>(inner_[0][2] + rhs);
            inner_[1][0] = static_cast<T>(inner_[1][0] + rhs);
            inner_[1][1] = static_cast<T>(inner_[1][1] + rhs);
            inner_[1][2] = static_cast<T>(inner_[1][2] + rhs);
            inner_[2][0] = static_cast<T>(inner_[2][0] + rhs);
            inner_[2][1] = static_cast<T>(inner_[2][1] + rhs);
            inner_[2][2] = static_cast<T>(inner_[2][2] + rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] + rhs[0][0]);
            inner_[0][1] = static_cast<T>(inner_[0][1] + rhs[0][1]);
            inner_[0][2] = static_cast<T>(inner_[0][2] + rhs[0][2]);
            inner_[1][0] = static_cast<T>(inner_[1][0] + rhs[1][0]);
            inner_[1][1] = static_cast<T>(inner_[1][1] + rhs[1][1]);
            inner_[1][2] = static_cast<T>(inner_[1][2] + rhs[1][2]);
            inner_[2][0] = static_cast<T>(inner_[2][0] + rhs[2][0]);
            inner_[2][1] = static_cast<T>(inner_[2][1] + rhs[2][1]);
            inner_[2][2] = static_cast<T>(inner_[2][2] + rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Mat3<T> &operator-=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] - rhs);
            inner_[0][1] = static_cast<T>(inner_[0][1] - rhs);
            inner_[0][2] = static_cast<T>(inner_[0][2] - rhs);
            inner_[1][0] = static_cast<T>(inner_[1][0] - rhs);
            inner_[1][1] = static_cast<T>(inner_[1][1] - rhs);
            inner_[1][2] = static_cast<T>(inner_[1][2] - rhs);
            inner_[2][0] = static_cast<T>(inner_[2][0] - rhs);
            inner_[2][1] = static_cast<T>(inner_[2][1] - rhs);
            inner_[2][2] = static_cast<T>(inner_[2][2] - rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] - rhs[0][0]);
            inner_[0][1] = static_cast<T>(inner_[0][1] - rhs[0][1]);
            inner_[0][2] = static_cast<T>(inner_[0][2] - rhs[0][2]);
            inner_[1][0] = static_cast<T>(inner_[1][0] - rhs[1][0]);
            inner_[1][1] = static_cast<T>(inner_[1][1] - rhs[1][1]);
            inner_[1][2] = static_cast<T>(inner_[1][2] - rhs[1][2]);
            inner_[2][0] = static_cast<T>(inner_[2][0] - rhs[2][0]);
            inner_[2][1] = static_cast<T>(inner_[2][1] - rhs[2][1]);
            inner_[2][2] = static_cast<T>(inner_[2][2] - rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Mat3<T> &operator*=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] * rhs);
            inner_[0][1] = static_cast<T>(inner_[0][1] * rhs);
            inner_[0][2] = static_cast<T>(inner_[0][2] * rhs);
            inner_[1][0] = static_cast<T>(inner_[1][0] * rhs);
            inner_[1][1] = static_cast<T>(inner_[1][1] * rhs);
            inner_[1][2] = static_cast<T>(inner_[1][2] * rhs);
            inner_[2][0] = static_cast<T>(inner_[2][0] * rhs);
            inner_[2][1] = static_cast<T>(inner_[2][1] * rhs);
            inner_[2][2] = static_cast<T>(inner_[2][2] * rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] * rhs[0][0]);
            inner_[0][1] = static_cast<T>(inner_[0][1] * rhs[0][1]);
            inner_[0][2] = static_cast<T>(inner_[0][2] * rhs[0][2]);
            inner_[1][0] = static_cast<T>(inner_[1][0] * rhs[1][0]);
            inner_[1][1] = static_cast<T>(inner_[1][1] * rhs[1][1]);
            inner_[1][2] = static_cast<T>(inner_[1][2] * rhs[1][2]);
            inner_[2][0] = static_cast<T>(inner_[2][0] * rhs[2][0]);
            inner_[2][1] = static_cast<T>(inner_[2][1] * rhs[2][1]);
            inner_[2][2] = static_cast<T>(inner_[2][2] * rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Mat3<T> &operator/=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] / rhs);
            inner_[0][1] = static_cast<T>(inner_[0][1] / rhs);
            inner_[0][2] = static_cast<T>(inner_[0][2] / rhs);
            inner_[1][0] = static_cast<T>(inner_[1][0] / rhs);
            inner_[1][1] = static_cast<T>(inner_[1][1] / rhs);
            inner_[1][2] = static_cast<T>(inner_[1][2] / rhs);
            inner_[2][0] = static_cast<T>(inner_[2][0] / rhs);
            inner_[2][1] = static_cast<T>(inner_[2][1] / rhs);
            inner_[2][2] = static_cast<T>(inner_[2][2] / rhs);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            inner_[0][0] = static_cast<T>(inner_[0][0] / rhs[0][0]);
            inner_[0][1] = static_cast<T>(inner_[0][1] / rhs[0][1]);
            inner_[0][2] = static_cast<T>(inner_[0][2] / rhs[0][2]);
            inner_[1][0] = static_cast<T>(inner_[1][0] / rhs[1][0]);
            inner_[1][1] = static_cast<T>(inner_[1][1] / rhs[1][1]);
            inner_[1][2] = static_cast<T>(inner_[1][2] / rhs[1][2]);
            inner_[2][0] = static_cast<T>(inner_[2][0] / rhs[2][0]);
            inner_[2][1] = static_cast<T>(inner_[2][1] / rhs[2][1]);
            inner_[2][2] = static_cast<T>(inner_[2][2] / rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline bool operator==(const U &rhs) const
    {
        if constexpr (is_arithmetic_mat3<U>::value)
            return {inner_[0][0] == rhs[0][0] && inner_[0][1] == rhs[0][1] && inner_[0][2] == rhs[0][2] &&
                    inner_[1][0] == rhs[1][0] && inner_[1][1] == rhs[1][1] && inner_[1][2] == rhs[1][2] &&
                    inner_[2][0] == rhs[2][0] && inner_[2][1] == rhs[2][1] && inner_[2][2] == rhs[2][2]};
    }

    template <typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline T determinant() const
    {
        T determinant = 0.0;
        determinant += inner_[0][0] * (inner_[1][1] * inner_[2][2] - inner_[1][2] * inner_[2][1]);
        determinant -= inner_[0][1] * (inner_[1][0] * inner_[2][2] - inner_[1][2] * inner_[2][0]);
        determinant += inner_[0][2] * (inner_[1][0] * inner_[2][1] - inner_[1][1] * inner_[2][0]);
        return determinant;
    }

    template <typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline auto invert() const
    {
        auto determinant = this->determinant();

        if (determinant < std::numeric_limits<double>::epsilon())
            throw std::runtime_error("this matrix is not invertible");

        auto invdet = 1.0 / determinant;
        auto xx = (inner_[1][1] * inner_[2][2] - inner_[1][2] * inner_[2][1]) * invdet;
        auto xy = (inner_[0][2] * inner_[2][1] - inner_[0][1] * inner_[2][2]) * invdet;
        auto xz = (inner_[0][1] * inner_[1][2] - inner_[0][2] * inner_[1][1]) * invdet;

        auto yx = (inner_[1][2] * inner_[2][0] - inner_[1][0] * inner_[2][2]) * invdet;
        auto yy = (inner_[0][0] * inner_[2][2] - inner_[0][2] * inner_[2][0]) * invdet;
        auto yz = (inner_[0][2] * inner_[1][0] - inner_[0][0] * inner_[1][2]) * invdet;

        auto zx = (inner_[1][0] * inner_[2][1] - inner_[1][1] * inner_[2][0]) * invdet;
        auto zy = (inner_[0][1] * inner_[2][0] - inner_[0][0] * inner_[2][1]) * invdet;
        auto zz = (inner_[0][0] * inner_[1][1] - inner_[0][1] * inner_[1][0]) * invdet;

        return Mat3(xx, xy, xz, yx, yy, yz, zx, zy, zz);
    }

    template <typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline auto transpose()
    {
        return Mat3(inner_[0][0], inner_[1][0], inner_[2][0], inner_[0][1], inner_[1][1], inner_[2][1], inner_[0][2],
                    inner_[1][2], inner_[2][2]);
    }

    template <typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline std::array<T, 9> flatten()
    {
        return {inner_[0][0], inner_[0][1], inner_[0][2], inner_[1][0], inner_[1][1], inner_[1][2], inner_[2][0],
                inner_[2][1], inner_[2][2]};
    }

    template <typename U, typename = std::enable_if<std::is_arithmetic_v<T>>> inline auto dot(const U &rhs) const
    {
        if constexpr (is_arithmetic_vec3<U>::value)
        {
            return Vec3<T>(inner_[0][0] * rhs[0] + inner_[0][1] * rhs[1] + inner_[0][2] * rhs[2],
                           inner_[1][0] * rhs[0] + inner_[1][1] * rhs[1] + inner_[1][2] * rhs[2],
                           inner_[2][0] * rhs[0] + inner_[2][1] * rhs[1] + inner_[2][2] * rhs[2]);
        }
        else if constexpr (is_arithmetic_mat3<U>::value)
        {
            return Mat3<T>(inner_[0][0] * rhs[0][0] + inner_[0][1] * rhs[1][0] + inner_[0][2] * rhs[2][0],
                           inner_[0][0] * rhs[0][1] + inner_[0][1] * rhs[1][1] + inner_[0][2] * rhs[2][1],
                           inner_[0][0] * rhs[0][2] + inner_[0][1] * rhs[1][2] + inner_[0][2] * rhs[2][2],
                           inner_[1][0] * rhs[0][0] + inner_[1][1] * rhs[1][0] + inner_[1][2] * rhs[2][0],
                           inner_[1][0] * rhs[0][1] + inner_[1][1] * rhs[1][1] + inner_[1][2] * rhs[2][1],
                           inner_[1][0] * rhs[0][2] + inner_[1][1] * rhs[1][2] + inner_[1][2] * rhs[2][2],
                           inner_[2][0] * rhs[0][0] + inner_[2][1] * rhs[1][0] + inner_[2][2] * rhs[2][0],
                           inner_[2][0] * rhs[0][1] + inner_[2][1] * rhs[1][1] + inner_[2][2] * rhs[2][1],
                           inner_[2][0] * rhs[0][2] + inner_[2][1] * rhs[1][2] + inner_[2][2] * rhs[2][2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Mat3 are allowed");
        }
    }

    inline friend std::ostream &operator<<(std::ostream &os, const Mat3<double> &mat)
    {
        std::cout.precision(15);
        os << std::endl;
        os << mat[0][0] << "\t" << mat[0][1] << "\t" << mat[0][2] << std::endl;
        os << mat[1][0] << "\t" << mat[1][1] << "\t" << mat[1][2] << std::endl;
        os << mat[2][0] << "\t" << mat[2][1] << "\t" << mat[2][2] << std::endl;
        return os;
    }
};

} // namespace molcpp