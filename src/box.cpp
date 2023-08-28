#include "box.h"
#include <error.h>

namespace molcpp
{

// Sinus and Cosine for degree values
constexpr double pi = 3.141592653589793238463;
static double deg2rad(double x)
{
    return x * pi / 180.0;
}

static double rad2deg(double x)
{
    return x * 180.0 / pi;
}

static double dacos(double alpha)
{
    return rad2deg(acos(alpha));
}

// static double dasin(double alpha)
// {
//     return rad2deg(asin(alpha));
// }

static double cosd(double theta)
{
    return cos(deg2rad(theta));
}

// static double sind(double theta)
// {
//     return sin(deg2rad(theta));
// }

Box::Box() : _matrix(Mat3<double>::unit())
{
    set_periodic(PBC::P, PBC::P, PBC::P);
}

Box::Box(Vec3<double> lengths, Vec3<double> angles) : Box()
{
    set_lengths_and_angles(lengths, angles);
}

void Box::set_lengths_and_angles(Vec3<double> lengths, Vec3<double> angles)
{
    auto a = lengths[0];
    auto b = lengths[1];
    auto c = lengths[2];

    auto alpha = angles[0];
    auto beta = angles[1];
    auto gamma = angles[2];

    auto lx = a;
    auto xy = b * cosd(gamma);
    auto xz = c * cosd(beta);
    auto ly = sqrt(b * b - xy * xy);
    auto yz = (b * c * cosd(alpha) - xy * xz) / ly;
    auto lz = sqrt(c * c - xz * xz - yz * yz);

    _matrix[0][0] = lx;
    _matrix[0][1] = xy;
    _matrix[0][2] = xz;
    _matrix[1][0] = 0;
    _matrix[1][1] = ly;
    _matrix[1][2] = yz;
    _matrix[2][0] = 0;
    _matrix[2][1] = 0;
    _matrix[2][2] = lz;
}

const Mat3<double> Box::get_matrix() const
{
    return _matrix;
}

const Mat3<double> Box::get_inverse() const
{
    return _matrix.invert();
}

const Vec3<double> Box::get_angles() const
{
    auto tilts = get_tilts();
    double xy = tilts[0];
    double xz = tilts[1];
    double yz = tilts[2];

    auto lengths = get_lengths();
    auto b = lengths[1];
    auto c = lengths[2];

    double ly = _matrix[1][1];

    auto cos_alpha = (xy * xz + ly * yz) / (b * c);
    auto cos_beta = xz / c;
    auto cos_gamma = xy / b;

    return {dacos(cos_alpha), dacos(cos_beta), dacos(cos_gamma)};
}

void Box::set_periodic(PBC x, PBC y, PBC z)
{
    _pbc = {x, y, z};
}

const std::array<Box::PBC, 3> Box::get_periodic() const
{
    return _pbc;
}

const Vec3<double> Box::get_lengths() const
{
    auto tilts = get_tilts();
    double xy = tilts[0];
    double xz = tilts[1];
    double yz = tilts[2];
    double ly = _matrix[1][1];
    double lz = _matrix[2][2];

    auto a = _matrix[0][0];
    auto b = sqrt(ly * ly + xy * xy);
    auto c = sqrt(lz * lz + xz * xz + yz * yz);
    return {a, b, c};
}

const Vec3<double> Box::get_tilts() const
{
    double xy = _matrix[0][1];
    double xz = _matrix[0][2];
    double yz = _matrix[1][2];
    return {xy, xz, yz};
}

double Box::get_volume() const
{
    return _matrix.determinant();
}

std::vector<Vec3<double>> Box::wrap(std::vector<Vec3<double>> &positions)
{
    std::vector<Vec3<double>> wrapped_positions(positions.size());
    for (size_t i = 0; i < positions.size(); i++)
    {
        wrapped_positions[i] = wrap(positions[i]);
    }
    return wrapped_positions;
}

Vec3<double> Box::wrap(Vec3<double> &position)
{
    // PBC are all P
    if (_pbc[0] == P && _pbc[1] == P && _pbc[2] == P)
    {
        auto _inv_mat = get_inverse();
        Vec3<double> reci_vec = _inv_mat * position;
        Vec3<double> wrapped_reci_vec = reci_vec - floor(reci_vec);
        return _matrix * wrapped_reci_vec;
    }
    else
        throw NotImplementedError("Only PBC = P is implemented");
}

double Box::calc_distance(Vec3<double> &r1, Vec3<double> &r2)
{
    auto dr = r1 - r2;
    auto wrapped_dr = wrap(dr);
    return norm(wrapped_dr);
}

Vec3<double> Box::calc_vector(Vec3<double> &r1, Vec3<double> &r2)
{
    auto dr = r1 - r2;
    auto wrapped_dr = wrap(dr);
    return wrapped_dr;
}

} // namespace molcpp