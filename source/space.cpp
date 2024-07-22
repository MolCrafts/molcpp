#include "molcpp/space.hpp"
#include <xtensor/xbuilder.hpp>
#include <xtensor/xfixed.hpp>

namespace molcpp
{

Box::Box() : _matrix{xt::eye<double>(3)}, _style{Style::ORTHORHOMBIC} {}

Box::Box(const xt::xtensor_fixed<double, xt::xshape<3>> &lengths): _matrix{xt::diag(lengths)}, _style{Style::ORTHORHOMBIC} {}

auto Box::get_style() const -> Style
{
    return _style;
}

bool Box::isin(const xt::xarray<double> &xyz) const
{
    return true;
}
} // namespace molcpp
