#include "molcpp/space.hpp"
#include "xtensor-blas/xlinalg.hpp"
#include <xtensor/xarray.hpp>
#include <xtensor/xmath.hpp>

namespace molcpp
{

constexpr double pi = 3.141592653589793238463;

static double deg2rad(double x)
{
    return x * pi / 180.0;
}

// static double rad2deg(double x)
// {
//     return x * 180.0 / pi;
// }

static double cosd(double theta)
{
    return cos(deg2rad(theta));
}

static double sind(double theta)
{
    return sin(deg2rad(theta));
}

// static bool is_roughly_zero(double value)
// {
//     // We think that 0.00001 is close enough to 0
//     return fabs(value) < 1e-5;
// }

// static bool is_roughly_90(double value)
// {
//     // We think that 89.999° is close enough to 90°
//     return fabs(value - 90.0) < 1e-3;
// }

static bool is_diagonal(const xt::xarray<double> &matrix)
{

    return xt::allclose(xt::triu(matrix, 1), 0) && xt::allclose(tril(matrix, -1), 0);
}

static bool is_upper_triangular(const xt::xarray<double> &matrix)
{
    bool is_diag = is_diagonal(matrix);
    bool is_upper_zero =
        !xt::allclose(matrix(0, 1), 0) || !xt::allclose(matrix(0, 2), 0) || !xt::allclose(matrix(1, 2), 0);
    return is_diag && is_upper_zero;
}

Box::Box() : _matrix{xt::zeros<double>({3, 3})}, _style{Style::INFINITE}
{
}

Box::Box(const xt::xarray<double> &matrix)
{
    if (matrix.shape()[0] != 3 || matrix.shape()[1] != 3)
    {
        throw std::runtime_error("Matrix must be 3x3");
    }
    _matrix = matrix;
    if (xt::allclose(matrix, 0))
        _style = Style::INFINITE;
    else if (is_upper_triangular(_matrix))
        _style = Style::TRICLINIC;
    else if (is_diagonal(_matrix))
        _style = Style::ORTHOGONAL;
}

Box::Box(const std::initializer_list<std::initializer_list<double>> &matrix) : Box(xt::xtensor<double, 2>(matrix))
{
}

Box Box::set_lengths_angles(const xt::xarray<double> &lengths, const xt::xarray<double> &angles)
{
    return Box(calc_matrix_from_lengths_angles(lengths, angles));
}

// Box Box::lengths_tilts(const xt::xarray<double> &lengths, const xt::xarray<double> &tilts)
// {
// }

xt::xarray<double> Box::calc_matrix_from_lengths_angles(const xt::xarray<double> &lengths,
                                                        const xt::xarray<double> &angles)
{
    if (lengths.size() != 3 || angles.size() != 3)
    {
        throw std::runtime_error("Lengths and angles must have size 3");
    }
    auto matrix = xt::xtensor_fixed<double, xt::xshape<3, 3>>::from_shape({3, 3});

    matrix(0, 0) = lengths[0];
    matrix(1, 0) = 0.0;
    matrix(2, 0) = 0.0;

    matrix(0, 1) = lengths[1] * cosd(angles[2]);
    matrix(1, 1) = lengths[1] * sind(angles[2]);
    matrix(2, 1) = 0.0;

    matrix(0, 2) = cosd(angles[1]);
    matrix(1, 2) = (cosd(angles[0]) - cosd(angles[1]) * cosd(angles[2])) / sind(angles[2]);
    matrix(2, 2) = sqrt(1 - matrix(0, 2) * matrix(0, 2) - matrix(1, 2) * matrix(1, 2));
    matrix(0, 2) *= lengths[2];
    matrix(1, 2) *= lengths[2];
    matrix(2, 2) *= lengths[2];

    if (!is_upper_triangular(matrix))
    {
        throw std::runtime_error("Matrix is not upper triangular");
    }

    return matrix;
}

xt::xtensor_fixed<double, xt::xshape<3>> Box::calc_lengths_from_matrix(
    const xt::xtensor_fixed<double, xt::xshape<3, 3>> &matrix)
{
    xt::xtensor_fixed<double, xt::xshape<3>> result;
    result(0) = xt::linalg::norm(xt::view(matrix, xt::all(), 0));
    result(1) = xt::linalg::norm(xt::view(matrix, xt::all(), 1));
    result(2) = xt::linalg::norm(xt::view(matrix, xt::all(), 2));
    return result;
}

xt::xtensor_fixed<double, xt::xshape<3>> Box::calc_angles_from_matrix(
    const xt::xtensor_fixed<double, xt::xshape<3, 3>> &matrix)
{

    auto v1 = xt::view(matrix, xt::all(), 0);
    auto v2 = xt::view(matrix, xt::all(), 1);
    auto v3 = xt::view(matrix, xt::all(), 2);

    auto norm_v1 = xt::linalg::norm(v1);
    auto norm_v2 = xt::linalg::norm(v2);
    auto norm_v3 = xt::linalg::norm(v3);
    return xt::concatenate(xt::xtuple(xt::rad2deg(xt::acos(xt::linalg::dot(v2, v3) / (norm_v2 * norm_v3))),
                                      xt::rad2deg(xt::acos(xt::linalg::dot(v1, v3) / (norm_v1 * norm_v3))),
                                      xt::rad2deg(xt::acos(xt::linalg::dot(v1, v2) / (norm_v1 * norm_v2)))),
                           1);
}

xt::xtensor_fixed<double, xt::xshape<3, 3>> Box::get_matrix() const
{
    return _matrix;
}

auto Box::get_style() const -> Style
{
    return _style;
}

auto Box::get_lengths() const -> xt::xtensor_fixed<double, xt::xshape<3>>
{
    switch (_style)
    {
    case INFINITE:
        return {0, 0, 0};
    case ORTHOGONAL:
        return {_matrix(0, 0), _matrix(1, 1), _matrix(2, 2)};
    case TRICLINIC:
        return Box::calc_lengths_from_matrix(_matrix);
    }
}

auto Box::get_angles() const -> xt::xtensor_fixed<double, xt::xshape<3>>
{
    switch (_style)
    {
    case INFINITE:
    case ORTHOGONAL:
        return {90, 90, 90};
    case TRICLINIC:
        return Box::calc_angles_from_matrix(_matrix);
    }
}

auto Box::get_volume() const -> double
{
    switch (_style)
    {
    case INFINITE:
        return 0;
    case ORTHOGONAL:
    case TRICLINIC:
        return xt::linalg::det(_matrix);
    }
}

bool Box::isin(const xt::xarray<double> &xyz) const
{
    return true;
}

bool operator==(const Box &rhs, const Box &lhs)
{
    if (lhs.get_style() != rhs.get_style())
    {
        return false;
    }
    return xt::allclose(rhs.get_matrix(), lhs.get_matrix());
}

bool operator!=(const Box &rhs, const Box &lhs)
{
    return !(rhs == lhs);
}
} // namespace molcpp