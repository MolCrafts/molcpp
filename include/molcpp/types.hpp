#pragma once

#include <xtensor/xfixed.hpp>

typedef xt::xtensor_fixed<double, xt::xshape<3>> Vec3;
typedef xt::xtensor_fixed<double, xt::xshape<3, 3>> Mat3;

#include <string>
#include <unordered_map>
#include <variant>
#include <xtensor/xarray.hpp>

namespace molcpp
{
template <typename... Args> class Property
{
  public:
    template <typename T> void set(std::string key, T value)
    {
        _data[key] = value;
    }

    void set(std::string key, std::variant<Args...> value)
    {
        _data[key] = value;
    }

    template <typename T> const T get(std::string key)
    {
        return std::get<T>(_data[key]);
    }

  private:
    std::unordered_map<std::string, std::variant<Args...>> _data;
};

} // namespace molcpp