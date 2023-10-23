#pragma once
#include <chemfiles.hpp>
#include <cmath>
#include <type_traits>

namespace molcpp
{

template <typename T> class Vec3;

template <typename T> struct is_arithmetic_vec3 : std::false_type
{
};

template <typename T> struct is_arithmetic_vec3<Vec3<T>> : std::is_arithmetic<T>
{
};


template <typename T> class Vec3
{
  private:
    T inner_[3]{};

  public:
    Vec3<T>() = default;
    Vec3<T>(const T &x, const T &y, const T &z) : inner_{x, y, z}
    {
    }
    template <typename U, typename = std::enable_if<std::is_arithmetic_v<U>>>
    Vec3<T>(const Vec3<U> &vec) : inner_{static_cast<T>(vec[0]), static_cast<T>(vec[1]), static_cast<T>(vec[2])}
    {
    }

    Vec3<T>(const chemfiles::Vector3D &vec) : inner_{vec[0], vec[1], vec[2]}
    {
    }

    inline const T &getX() const
    {
        return inner_[0];
    }
    inline const T &getY() const
    {
        return inner_[1];
    }
    inline const T &getZ() const
    {
        return inner_[2];
    }

    inline void setX(T new_val)
    {
        inner_[0] = new_val;
    }
    inline void setY(T new_val)
    {
        inner_[1] = new_val;
    }
    inline void setZ(T new_val)
    {
        inner_[2] = new_val;
    }

    inline const T &operator[](std::size_t index) const
    {
        return inner_[index];
    }
    inline T &operator[](std::size_t index)
    {
        return inner_[index];
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator+(const Vec3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Vec3<decltype(T{} + U{})>(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            return Vec3<decltype(T{} + U{}[0])>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator+(const U &lhs, const Vec3<T> &rhs)
    {
        return rhs + lhs;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator-(const Vec3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Vec3<decltype(T{} - U{})>(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            return Vec3<decltype(T{} - U{}[0])>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
    }

    template <typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Vec3<T> operator-() const
    {
        return {-inner_[0], -inner_[1], -inner_[2]};
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator-(const U &lhs, const Vec3<T> &rhs)
    {
        return Vec3<decltype(U{} - T{})>{lhs - rhs[0], lhs - rhs[1], lhs - rhs[2]};
    }

    template <typename U> inline friend auto operator*(const Vec3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Vec3<decltype(T{} * U{})>(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            return Vec3<decltype(T{} * U{}[0])>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator*(const U &lhs, const Vec3<T> &rhs)
    {
        return rhs * lhs;
    }

    template <typename U> inline friend auto operator/(const Vec3<T> &lhs, const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            return Vec3<decltype(T{} / U{})>(lhs.inner_[0] / rhs, lhs.inner_[1] / rhs, lhs.inner_[2] / rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            return Vec3<decltype(T{} / U{}[0])>(lhs.inner_[0] / rhs[0], lhs.inner_[1] / rhs[1], lhs.inner_[2] / rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>,
              typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline friend auto operator/(const U &lhs, const Vec3<T> &rhs)
    {
        return Vec3<decltype(U{} / T{})>{lhs / rhs[0], lhs / rhs[1], lhs / rhs[2]};
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Vec3<T> &operator+=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0] = static_cast<T>(inner_[0] + rhs);
            inner_[1] = static_cast<T>(inner_[1] + rhs);
            inner_[2] = static_cast<T>(inner_[2] + rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            inner_[0] = static_cast<T>(inner_[0] + rhs[0]);
            inner_[1] = static_cast<T>(inner_[1] + rhs[1]);
            inner_[2] = static_cast<T>(inner_[2] + rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Vec3<T> &operator-=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0] = static_cast<T>(inner_[0] - rhs);
            inner_[1] = static_cast<T>(inner_[1] - rhs);
            inner_[2] = static_cast<T>(inner_[2] - rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            inner_[0] = static_cast<T>(inner_[0] - rhs[0]);
            inner_[1] = static_cast<T>(inner_[1] - rhs[1]);
            inner_[2] = static_cast<T>(inner_[2] - rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Vec3<T> &operator*=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0] = static_cast<T>(inner_[0] * rhs);
            inner_[1] = static_cast<T>(inner_[1] * rhs);
            inner_[2] = static_cast<T>(inner_[2] * rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            inner_[0] = static_cast<T>(inner_[0] * rhs[0]);
            inner_[1] = static_cast<T>(inner_[1] * rhs[1]);
            inner_[2] = static_cast<T>(inner_[2] * rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>> inline Vec3<T> &operator/=(const U &rhs)
    {
        if constexpr (std::is_arithmetic_v<U>)
        {
            inner_[0] = static_cast<T>(inner_[0] / rhs);
            inner_[1] = static_cast<T>(inner_[1] / rhs);
            inner_[2] = static_cast<T>(inner_[2] / rhs);
        }
        else if constexpr (is_arithmetic_vec3<U>::value)
        {
            inner_[0] = static_cast<T>(inner_[0] / rhs[0]);
            inner_[1] = static_cast<T>(inner_[1] / rhs[1]);
            inner_[2] = static_cast<T>(inner_[2] / rhs[2]);
        }
        else
        {
            // std::is_arithmetic_v<U> always false, use this to avoid clangd error
            static_assert(std::is_arithmetic_v<U>, "Invalid type: only arithmetic type or Vec3 are allowed");
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline bool operator==(const U &rhs) const
    {
        if constexpr (is_arithmetic_vec3<U>::value)
            return inner_[0] == rhs[0] && inner_[1] == rhs[1] && inner_[2] == rhs[2];
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline bool operator!=(const U &rhs) const
    {
        if constexpr (is_arithmetic_vec3<U>::value)
            return !((*this) == rhs);
    }
};

template <typename T, typename = std::enable_if_t<is_arithmetic_vec3<T>::value>> inline double norm(const T &vec)
{
    return std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

template <typename T, typename = std::enable_if_t<is_arithmetic_vec3<T>::value>> inline Vec3<double> floor(const T &vec)
{
    return {std::floor(vec[0]), std::floor(vec[1]), std::floor(vec[2])};
}

} // namespace molcpp