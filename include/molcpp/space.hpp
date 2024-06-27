#pragma once

#include "molcpp/export.hpp"
#include "molcpp/types.hpp"

#include <initializer_list>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xfixed.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xtensor.hpp>
#include "xtensor-blas/xlinalg.hpp"

namespace molcpp
{

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

    Box(const std::initializer_list<double> &lengths);
    Box(const std::initializer_list<std::initializer_list<double>> &matrix);

    ~Box() override = default;
    Box(const Box &other) = default;
    Box &operator=(const Box &other) = default;
    Box(Box &other) noexcept = default;
    Box &operator=(Box &&other) noexcept = default;

    static Box from_lengths_angles(const Vec3 &lengths, const Vec3 &angles);

    // static Box set_lengths_tilts(const Vec3 &lengths, const Vec3 &tilts);

    static Mat3 calc_matrix_from_lengths_angles(const Vec3 &lengths, const Vec3 &angles);

    static Vec3 calc_lengths_from_matrix(const Mat3 &matrix);

    static Vec3 calc_angles_from_matrix(const Mat3 &matrix);

    static auto calc_style_from_matrix(const Mat3 &matrix) -> Style;

    static auto check_matrix(const Mat3 &matrix) -> Mat3;

    void set_lengths(const Vec3 &lengths);

    void set_angles(const Vec3 &angles);

    void set_matrix(const Mat3 &matrix);

    void set_lengths_angles(const Vec3 &lengths, const Vec3 &angles);

    auto isin(const xt::xarray<double> &xyz) const -> xt::xarray<bool> override;

    auto wrap(const xt::xarray<double> &xyz) const -> xt::xarray<double> override;

    auto wrap_orth(const xt::xarray<double> &xyz) const -> xt::xarray<double>;

    auto wrap_tric(const xt::xarray<double> &xyz) const -> xt::xarray<double>;

    auto wrap_free(const xt::xarray<double> &xyz) const -> xt::xarray<double>;

    auto get_style() const -> Style;

    auto get_matrix() const -> Mat3;

    auto get_inv() const -> Mat3 {
        return xt::linalg::inv(_matrix);
    }

    auto get_lengths() const -> Vec3;

    auto get_angles() const -> Vec3;

    auto get_volume() const -> double;

  private:
    Mat3 _matrix;
};

bool MOLCPP_EXPORT operator==(const Box &rhs, const Box &lhs);
bool MOLCPP_EXPORT operator!=(const Box &rhs, const Box &lhs);

} // namespace molcpp