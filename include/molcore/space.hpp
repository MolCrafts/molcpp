#pragma once

#include <xtensor/xarray.hpp>
#include <xtensor/xfixed.hpp>
#include <xtensor/xtensor.hpp>

namespace molcore
{

class Region
{
  public:
    virtual auto isin(const xt::xarray<double> &xyz) const -> bool = 0;

    virtual ~Region() = default;

  private:
};

class Boundary
{
  public:
    virtual ~Boundary() = default;

  private:
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

    /// Construct an `ORTHORHOMBIC` box with the given box `lengths`
    Box(const xt::xtensor_fixed<double, xt::xshape<3>> &lengths);

    /// Construct a box with the given box `lengths` and `angles`
    ///
    /// If all lengths are set to 0, then the box is `INFINITE`. If at least
    /// one length is not zero and all angles are 90.0, then the box is
    /// `ORTHORHOMBIC`.  Else a `TRICLINIC` box is created.
    // Box(xt::xarray<double> lengths, xt::xarray<double> angles);

    /// Construct a box from matrix.
    ///
    /// If `matrix` contains only zeros, then an infinite box is created. If
    /// only the diagonal of the matrix is non-zero, then the box is
    /// `ORTHORHOMBIC`.  Else a `TRICLINIC` box is created. The matrix entries
    /// should be in Angstroms.
    // Box( matrix);

    auto isin(const xt::xarray<double> &xyz) const -> bool override;

    // box style getter
    auto get_style() const -> Style;

  private:
    xt::xtensor_fixed<double, xt::xshape<3, 3>> _matrix;
    Style _style;
};
} // namespace molcore