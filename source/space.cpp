#include "molcpp/space.hpp"
#include "xtensor-blas/xlinalg.hpp"
#include <xtensor/xarray.hpp>
#include <xtensor/xmath.hpp>


namespace molcpp
{

Box::Box() : _matrix{xt::zeros<double>({3, 3})}
{
}

Box::Box(const Mat3 &matrix)
{
    if (matrix.shape()[0] != 3 || matrix.shape()[1] != 3)
    {
        throw std::runtime_error("Matrix must be 3x3");
    }
    set_matrix(matrix);
}

Box::Box(const std::initializer_list<std::initializer_list<double>> &matrix)
{
    set_matrix(Mat3(matrix));
}

Box::Box(const std::initializer_list<double> &lengths): _matrix{xt::zeros<double>({3, 3})}
{
    Vec3 _lengths = Vec3(lengths);
    set_lengths(_lengths);
}

Box Box::from_lengths_angles(const Vec3 &lengths, const Vec3 &angles)
{
    return Box(calc_matrix_from_lengths_angles(lengths, angles));
}

// Box Box::from_lengths_tilts(const Vec3 &lengths, const Vec3 &tilts)
// {
// }

Mat3 Box::calc_matrix_from_lengths_angles(const Vec3 &lengths, const Vec3 &angles)
{
    if (xt::any(lengths < 0))
    {
        throw std::runtime_error("Lengths must >= 0");
    }
    else if (xt::any(angles <= 0))
    {
        throw std::runtime_error("Angles can not <= 0°");
    }
    else if (xt::any(angles >= 180))
    {
        throw std::runtime_error("Angles can not >= 180°");
    }
    Mat3 matrix;
    matrix.fill(0.0);

    matrix(0, 0) = lengths(0);
    matrix(1, 0) = 0.0;
    matrix(2, 0) = 0.0;

    matrix(0, 1) = lengths(1) * cosd(angles(2));
    matrix(1, 1) = lengths(1) * sind(angles(2));
    matrix(2, 1) = 0.0;

    matrix(0, 2) = cosd(angles(1));
    matrix(1, 2) = (cosd(angles(0)) - cosd(angles(1)) * cosd(angles(2))) / sind(angles(2));
    matrix(2, 2) = sqrt(1 - matrix(0, 2) * matrix(0, 2) - matrix(1, 2) * matrix(1, 2));
    matrix(0, 2) *= lengths(2);
    matrix(1, 2) *= lengths(2);
    matrix(2, 2) *= lengths(2);

    if (!is_upper_triangular(matrix))
    {
        throw std::runtime_error("Matrix is not upper triangular");
    }

    return matrix;
}

Mat3 Box::calc_matrix_from_size_tilts(const Vec3 &sizes, const Vec3 &tilts)
{
    double xz = tilts(1);
    double yz = tilts(2);
    double xy = tilts(0);
    double a = sizes(0);
    double b = sqrt(sizes(1) * sizes(1) + xy * xy);
    double c = sqrt(sizes(2)*sizes(2) + xz*xz + yz*yz);

    double alpha = acos(xy*xz + sizes(1) * yz) / (b * c);
    double beta = acos(xz / c);
    double gamma = acos(xy / b);

    return calc_matrix_from_lengths_angles({a, b, c}, {alpha, beta, gamma});
}

Vec3 Box::calc_lengths_from_matrix(const Mat3 &matrix)
{
    Vec3 result;
    result(0) = xt::linalg::norm(xt::view(matrix, xt::all(), 0));
    result(1) = xt::linalg::norm(xt::view(matrix, xt::all(), 1));
    result(2) = xt::linalg::norm(xt::view(matrix, xt::all(), 2));
    return result;
}

Vec3 Box::calc_angles_from_matrix(const Mat3 &matrix)
{
    auto v1 = xt::view(matrix, xt::all(), 0);
    auto v2 = xt::view(matrix, xt::all(), 1);
    auto v3 = xt::view(matrix, xt::all(), 2);

    auto norm_v1 = xt::linalg::norm(v1);
    auto norm_v2 = xt::linalg::norm(v2);
    auto norm_v3 = xt::linalg::norm(v3);
    return xt::concatenate(xt::xtuple(xt::rad2deg(xt::acos(xt::linalg::dot(v2, v3) / (norm_v2 * norm_v3))),
                                      xt::rad2deg(xt::acos(xt::linalg::dot(v1, v3) / (norm_v1 * norm_v3))),
                                      xt::rad2deg(xt::acos(xt::linalg::dot(v1, v2) / (norm_v1 * norm_v2)))));
}

auto Box::calc_style_from_matrix(const Mat3 &matrix) -> Box::Style
{
    if (xt::allclose(matrix, 0))
        return Box::Style::FREE;
    else if (is_diagonal(matrix))
        return Box::Style::ORTHOGONAL;
    else if (is_upper_triangular(matrix))
        return Box::Style::TRICLINIC;
    else
        throw std::runtime_error("Matrix is valid");
}

auto Box::check_matrix(const Mat3 &matrix) -> Mat3
{
    if (matrix.shape()[0] != 3 || matrix.shape()[1] != 3)
    {
        throw std::runtime_error("Matrix must be 3x3");
    }
    if (xt::linalg::det(matrix) <= 0)
    {
        throw std::runtime_error("Matrix must be invertible");
    }
    return matrix;
}

void Box::set_lengths(const Vec3 &lengths)
{
    if (lengths.size() != 3)
    {
        throw std::runtime_error("Lengths must have size 3");
    }
    auto angles = get_angles();
    _matrix = calc_matrix_from_lengths_angles(lengths, angles);
}

void Box::set_angles(const Vec3 &angles)
{
    auto lengths = get_lengths();
    _matrix = calc_matrix_from_lengths_angles(lengths, angles);
}

void Box::set_matrix(const Mat3 &matrix)
{
    _matrix = check_matrix(matrix);
}

void Box::set_lengths_angles(const Vec3 &lengths, const Vec3 &angles)
{
    if (lengths.size() != 3 || angles.size() != 3)
    {
        throw std::runtime_error("Lengths and angles must have size 3");
    }
    _matrix = calc_matrix_from_lengths_angles(lengths, angles);
}

void Box::set_lengths_tilts(const Vec3 &lengths, const Vec3 &tilts)
{
    _matrix = calc_matrix_from_size_tilts(lengths, tilts);
}

auto Box::get_lengths() const -> Vec3
{
    switch (calc_style_from_matrix(_matrix))
    {
    case FREE:
        return {0, 0, 0};
    case ORTHOGONAL:
        return {_matrix(0, 0), _matrix(1, 1), _matrix(2, 2)};
    case TRICLINIC:
        return Box::calc_lengths_from_matrix(_matrix);
    default:
        throw std::runtime_error("Invalid Style");
    }
}

auto Box::get_angles() const -> Vec3
{
    switch (calc_style_from_matrix(_matrix))
    {
    case FREE:
    case ORTHOGONAL:
        return {90, 90, 90};
    case TRICLINIC:
        return Box::calc_angles_from_matrix(_matrix);
    default:
        throw std::runtime_error("Invalid Style");
    }
}

auto Box::get_volume() const -> double
{
    switch (calc_style_from_matrix(_matrix))
    {
    case FREE:
        return 0;
    case ORTHOGONAL:
    case TRICLINIC:
        return xt::linalg::det(_matrix);
    default:
        throw std::runtime_error("Invalid Style");
    }
}

auto Box::get_distance_between_faces() const -> Vec3
{
    switch (calc_style_from_matrix(_matrix))
    {
    case FREE:
        return {0, 0, 0};
    case ORTHOGONAL:
        return {xt::linalg::norm(xt::view(_matrix, xt::all(), 0)),
                xt::linalg::norm(xt::view(_matrix, xt::all(), 1)),
                xt::linalg::norm(xt::view(_matrix, xt::all(), 2))};
    case TRICLINIC:{
        auto a = xt::view(_matrix, xt::all(), 0);
        auto b = xt::view(_matrix, xt::all(), 1);
        auto c = xt::view(_matrix, xt::all(), 2);

        auto na = xt::linalg::cross(b, c);
        auto nb = xt::linalg::cross(c, a);
        auto nc = xt::linalg::cross(a, b);

        na /= xt::linalg::norm(na);
        nb /= xt::linalg::norm(nb);
        nc /= xt::linalg::norm(nc);

        return xt::concatenate(xt::xtuple(xt::linalg::dot(na, a),
                                          xt::linalg::dot(nb, b),
                                          xt::linalg::dot(nc, c)));}
    default:
        throw std::runtime_error("Invalid Style");
    }

}

auto Box::isin(const xt::xarray<double> &xyz) const -> xt::xarray<bool>
{
    return true;
}

auto Box::wrap(const xt::xarray<double> &xyz) const -> xt::xarray<double>
{
    switch (calc_style_from_matrix(_matrix))
    {
    case FREE:
        return wrap_free(xyz);
    case ORTHOGONAL:
        return wrap_orth(xyz);
    case TRICLINIC:
        return wrap_tric(xyz);
    default:
        throw std::runtime_error("Invalid Style");
    }
}

auto Box::wrap_free(const xt::xarray<double> &xyz) const -> xt::xarray<double>
{
    return xt::xarray<double>(xyz);
}

auto Box::wrap_orth(const xt::xarray<double> &xyz) const -> xt::xarray<double>
{
    auto lengths = this->get_lengths();
    return xyz - xt::round(xyz / lengths) * lengths;
}

auto Box::wrap_tric(const xt::xarray<double> &xyz) const -> xt::xarray<double>
{
    auto fractional = xt::linalg::dot(this->get_inv(), xt::transpose(xyz));
    return xt::transpose(xt::linalg::dot(get_matrix(), fractional - xt::round(fractional)));
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