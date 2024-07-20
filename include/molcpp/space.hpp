#pragma once

#include "molcpp/export.hpp"
#include "molcpp/types.hpp"

#include "xtensor-blas/xlinalg.hpp"
#include <initializer_list>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xfixed.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xtensor.hpp>

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

static bool is_close_zero(double value)
{
    // We think that 0.00001 is close enough to 0
    return fabs(value) < 1e-5;
}

// static bool is_roughly_90(double value)
// {
//     // We think that 89.999° is close enough to 90°
//     return fabs(value - 90.0) < 1e-3;
// }

static bool is_upper_triangular(const Mat3 &matrix)
{
    bool is_tril_zero = is_close_zero(matrix(1, 0)) && is_close_zero(matrix(2, 0)) && is_close_zero(matrix(2, 1));
    return is_tril_zero;
}

static bool is_diagonal(const Mat3 &matrix)
{

    bool is_tril_zero = is_upper_triangular(matrix);
    bool is_triu_zero = is_close_zero(matrix(0, 1)) && is_close_zero(matrix(0, 2)) && is_close_zero(matrix(1, 2));
    return is_tril_zero && is_triu_zero;
}

class MOLCPP_EXPORT Region
{
  public:
    /// Default constructor
    Region() = default;

    virtual ~Region() = default;

    /// Declare copy constructor
    Region(const Region &) = default;

    /// Declare copy assignment operator
    auto operator=(const Region &) -> Region & = default;

    /// Declare move constructor
    Region(Region &&) = default;

    /// Declare move assignment operator
    auto operator=(Region &&) -> Region & = default;

    /// Check if points is inside the region
    virtual auto isin(const xt::xarray<double> &xyz) const -> xt::xarray<bool> = 0;

  private:
};

class MOLCPP_EXPORT Boundary
{
  public:
    /// Default constructor
    Boundary() = default;

    virtual ~Boundary() = default;

    /// Declare copy constructor
    Boundary(const Boundary &) = default;

    /// Declare copy assignment operator
    auto operator=(const Boundary &) -> Boundary & = default;

    /// Declare move constructor
    Boundary(Boundary &&) = default;

    /// Declare move assignment operator
    auto operator=(Boundary &&) -> Boundary & = default;

    virtual auto wrap(const xt::xarray<double> &) const -> xt::xarray<double> = 0;
};

class MOLCPP_EXPORT Box : public Region, public Boundary
{
  public:
    enum Style
    {
        FREE,
        ORTHOGONAL,
        TRICLINIC
    };

    /// Construct an `INFINITY` box, with all lengths set to 0
    Box();

    explicit Box(const Mat3 &matrix);

    explicit Box(const std::initializer_list<double> &lengths);
    explicit Box(const std::initializer_list<std::initializer_list<double>> &matrix);

    ~Box() override = default;
    Box(const Box &other) = default;
    Box &operator=(const Box &other) = default;
    Box(Box &other) noexcept = default;
    Box &operator=(Box &&other) noexcept = default;

    static Box from_lengths_angles(const Vec3 &lengths, const Vec3 &angles);

    // static Box from_lengths_tilts(const Vec3 &lengths, const Vec3 &tilts);

    static Mat3 calc_matrix_from_lengths_angles(const Vec3 &lengths, const Vec3 &angles);

    static Mat3 calc_matrix_from_size_tilts(const Vec3 &lengths, const Vec3 &tilts);

    static Vec3 calc_lengths_from_matrix(const Mat3 &matrix);

    static Vec3 calc_angles_from_matrix(const Mat3 &matrix);

    static auto calc_style_from_matrix(const Mat3 &matrix) -> Style;

    static auto check_matrix(const Mat3 &matrix) -> Mat3;

    void set_lengths(const Vec3 &lengths);

    void set_angles(const Vec3 &angles);

    void set_matrix(const Mat3 &matrix);

    void set_lengths_angles(const Vec3 &lengths, const Vec3 &angles);

    void set_lengths_tilts(const Vec3 &lengths, const Vec3 &tilts);

    auto isin(const xt::xarray<double> &xyz) const -> xt::xarray<bool> override;

    auto wrap(const xt::xarray<double> &xyz) const -> xt::xarray<double> override;

    auto wrap_orth(const xt::xarray<double> &xyz) const -> xt::xarray<double>;

    auto wrap_tric(const xt::xarray<double> &xyz) const -> xt::xarray<double>;

    auto wrap_free(const xt::xarray<double> &xyz) const -> xt::xarray<double>;

    auto get_style() const -> Style{
        return calc_style_from_matrix(_matrix);
    }

    auto get_matrix() const -> Mat3
    {
      return _matrix;
    }

    auto get_inv() const -> Mat3
    {
        return xt::linalg::inv(_matrix);
    }

    auto get_lengths() const -> Vec3;

    auto get_angles() const -> Vec3;

    auto get_volume() const -> double;

    auto get_distance_between_faces() const -> Vec3;

  private:
    Mat3 _matrix;
};

bool MOLCPP_EXPORT operator==(const Box &rhs, const Box &lhs);
bool MOLCPP_EXPORT operator!=(const Box &rhs, const Box &lhs);

} // namespace molcpp