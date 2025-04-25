#ifndef MOLCPP_COMPUTE_HPP
#define MOLCPP_COMPUTE_HPP
#include <vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>

namespace molcpp
{

class Result
{
};

template <typename T> class Result1D : public Result
{
  public:
    Result1D(std::string key = "") : _key(key) {};
    Result1D(std::string key, const xt::xarray<T> &data) : _key(key), _data(data)
    {
    }
    auto get(std::string key) -> xt::xarray<T>
    {
        return _data;
    }

  private:
    std::string _key;
    xt::xarray<T> _data;
};

class Result2D : public Result
{
};

template <typename Derived, typename ResultType> class Compute
{
};

class MSDCompute : public Compute<MSDCompute, Result1D<double>>
{

  public:
    // enum class Style
    enum class MSDStyle
    {
        DIRECT,
        WINDOW
    };
    MSDCompute(MSDStyle style = MSDStyle::DIRECT) : _style(style)
    {
    }

    Result1D<double> compute(const xt::xarray<double> &xyz)
    {
        Result1D<double> result;
        switch (_style)
        {
        case MSDStyle::DIRECT:
            result = direct_msd_compute(xyz);
            break;

        case MSDStyle::WINDOW:
            break;
        default:
            break;
        }
        return result;
    }

    Result1D<double> direct_msd_compute(const xt::xarray<double> &xyz)
    {
        auto xyz0 = xt::view(xyz, 0, xt::all(), xt::all());
        auto diff = xt::pow(xyz, 2) - xt::pow(xyz0, 2);
        Result1D<double> result{"direct_msd", diff};

        return result;
    }

  private:
    MSDStyle _style;
};

} // namespace molcpp
#endif // MOLCPP_COMPUTE_HPP