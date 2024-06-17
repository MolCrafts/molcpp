#include "molcore/space.hpp"

#include "xtensor-blas/xlinalg.hpp"
#include <xtensor/xmath.hpp>

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
    return xt::allclose(xt::tril(matrix, -1), 0);
}

namespace molcore
{

Box::Box() : _matrix{xt::eye<double>(3)}, _style{Style::INFINITE}
{
}

Box::Box(const xt::xarray<double> &matrix)
{
    if (matrix.shape()[0] != 3 || matrix.shape()[1] != 3)
    {
        throw std::runtime_error("Matrix must be 3x3");
    }

    if (xt::isclose(xt::linalg::det(matrix), 0))
    {
        throw std::runtime_error("Matrix is singular");
    }
    _matrix = matrix;
    if (is_diagonal(_matrix))
        _style = Style::ORTHORHOMBIC;
    else if (is_upper_triangular(_matrix))
        _style = Style::TRICLINIC;
    else if (xt::allclose(matrix, 0))
        _style = Style::INFINITE;
}

Box::Box(const std::initializer_list<std::initializer_list<double>> &matrix) : Box(xt::xtensor<double, 2>(matrix))
{
}

Box Box::set_lengths_angles(const xt::xarray<double> &lengths, const xt::xarray<double> &angles)
{
    return Box(calc_cell_matrix_from_lengths_angles(lengths, angles));
}

// Box Box::lengths_tilts(const xt::xarray<double> &lengths, const xt::xarray<double> &tilts)
// {
// }

xt::xarray<double> Box::calc_cell_matrix_from_lengths_angles(const xt::xarray<double> &lengths,
                                                             const xt::xarray<double> &angles)
{
    if (lengths.size() != 3 || angles.size() != 3)
    {
        throw std::runtime_error("Lengths and angles must have size 3");
    }
    if (angles[0] <= 0 || angles[1] <= 0 || angles[2] <= 0)
    {
        throw std::runtime_error("Angles must be positive");
    }
    if (lengths[0] <= 0 || lengths[1] <= 0 || lengths[2] <= 0)
    {
        throw std::runtime_error("Lengths must be positive");
    }
    if (angles[0] >= 180.0 || angles[1] >= 180.0 || angles[2] >= 180.0)
    {
        throw std::runtime_error("Angles must be less than 180");
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

xt::xarray<double> Box::get_matrix() const
{
    return _matrix;
}

auto Box::get_style() const -> Style
{
    return _style;
}

bool Box::isin(const xt::xarray<double> &xyz) const
{
    return true;
}
} // namespace molcore
