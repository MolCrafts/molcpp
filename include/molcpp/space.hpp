#pragma once

#include <initializer_list>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xfixed.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xtensor.hpp>

namespace molcpp
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
        INFINITE,
        ORTHOGONAL,
        TRICLINIC
    };

    /// Construct an `INFINITY` box, with all lengths set to 0
    Box();

    explicit Box(const xt::xarray<double> &matrix);

    Box(const std::initializer_list<std::initializer_list<double>> &matrix);

    ~Box() override = default;
    Box(const Box& other) = default;
    Box& operator=(const Box& other) = default;
    Box(Box& other) noexcept = default;
    Box& operator=(Box&& other) noexcept = default;

    static Box set_lengths_angles(const xt::xarray<double> &lengths, const xt::xarray<double> &angles);

    // static Box set_lengths_tilts(const xt::xarray<double> &lengths, const xt::xarray<double> &tilts);

    static xt::xarray<double> calc_matrix_from_lengths_angles(const xt::xarray<double> &lengths,
                                                              const xt::xarray<double> &angles);

    static xt::xtensor_fixed<double, xt::xshape<3>> calc_lengths_from_matrix(const xt::xtensor_fixed<double, xt::xshape<3, 3>> &matrix);

    static xt::xtensor_fixed<double, xt::xshape<3>> calc_angles_from_matrix(const xt::xtensor_fixed<double, xt::xshape<3, 3>> &matrix);

    auto isin(const xt::xarray<double> &xyz) const -> bool override;

    // box style getter
    auto get_style() const -> Style;

    auto get_matrix() const -> xt::xtensor_fixed<double, xt::xshape<3, 3>>;

    auto get_lengths() const -> xt::xtensor_fixed<double, xt::xshape<3>>;

    auto get_angles() const -> xt::xtensor_fixed<double, xt::xshape<3>>;

    auto get_volume() const -> double;

  private:
    xt::xtensor_fixed<double, xt::xshape<3, 3>> _matrix;
    Style _style;
};

bool operator==(const Box& rhs, const Box& lhs);
bool operator!=(const Box& rhs, const Box& lhs);

} // namespace molcpp