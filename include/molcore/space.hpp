#pragma once

#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xfixed.hpp>
#include <xtensor/xtensor.hpp>
#include <initializer_list>
#include <xtensor/xmath.hpp>

namespace molcore
{

class Region
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
    virtual auto isin(const xt::xarray<double> &xyz) const -> bool = 0;

  private:
};

class Boundary
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
};

class Box : public Region, public Boundary
{
  public:
    enum Style
    {
        ORTHORHOMBIC,
        TRICLINIC,
        INFINITE
    };

    /// Construct an `INFINITY` box, with all lengths set to 0
    Box();

    explicit Box(const xt::xarray<double> &matrix);

    Box(const std::initializer_list<std::initializer_list<double>> &matrix);

    static Box set_lengths_angles(const xt::xarray<double> &lengths, const xt::xarray<double> &angles);

    // static Box set_lengths_tilts(const xt::xarray<double> &lengths, const xt::xarray<double> &tilts);

    static xt::xarray<double> calc_cell_matrix_from_lengths_angles(const xt::xarray<double> &lengths, const xt::xarray<double> &angles);

    // static xt::xarray<double> calc_cell_matrix_from_lengths_tilts(const xt::xarray<double> &lengths, const xt::xarray<double> &tilts);


    auto isin(const xt::xarray<double> &xyz) const -> bool override;

    // box style getter
    auto get_style() const -> Style;

    auto get_matrix() const -> xt::xarray<double>;

  private:
    xt::xtensor_fixed<double, xt::xshape<3, 3>> _matrix;
    Style _style;
};
} // namespace molcore