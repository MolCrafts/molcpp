#include "cell.h"

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

    Cell::Cell()
    {
        _matrix = xt::eye<double>({3, 3});
        set_boundary(PBC::P, PBC::P, PBC::P);
    }

    Cell::Cell(Vector3D lengths, Vector3D angles) : Cell()
    {
        set_lengths_and_angles(lengths, angles);
    }

    void Cell::set_lengths_and_angles(Vector3D lengths, Vector3D angles)
    {
        auto a = lengths(0);
        auto b = lengths(1);
        auto c = lengths(2);

        auto alpha = angles(0);
        auto beta = angles(1);
        auto gamma = angles(2);

        auto lx = a;
        auto xy = b * cosd(gamma);
        auto xz = c * cosd(beta);
        auto ly = sqrt(b * b - xy * xy);
        auto yz = (b * c * cosd(alpha) - xy * xz) / ly;
        auto lz = sqrt(c * c - xz * xz - yz * yz);

        _matrix(0, 0) = lx;
        _matrix(0, 1) = xy;
        _matrix(0, 2) = xz;
        _matrix(1, 0) = 0;
        _matrix(1, 1) = ly;
        _matrix(1, 2) = yz;
        _matrix(2, 0) = 0;
        _matrix(2, 1) = 0;
        _matrix(2, 2) = lz;

    }

    const Matrix3D Cell::get_matrix() const
    {
        return _matrix;
    }

    const Matrix3D Cell::get_inverse() const
    {
        return xt::linalg::inv(_matrix);
    }

    const Vector3D Cell::get_angles() const
    {
        auto tilts = get_tilts();
        double xy = tilts(0);
        double xz = tilts(1);
        double yz = tilts(2);

        auto lengths = get_lengths();
        auto b = lengths(1);
        auto c = lengths(2);

        double ly = _matrix(1, 1);

        auto cos_alpha = (xy * xz + ly * yz) / (b * c);
        auto cos_beta = xz / c;
        auto cos_gamma = xy / b;

        return {dacos(cos_alpha), dacos(cos_beta), dacos(cos_gamma)};    
    }

    void Cell::set_boundary(PBC x, PBC y, PBC z)
    {
        _pbc = {x, y, z};
    }

    const Vector3D Cell::get_lengths() const
    {
        auto tilts = get_tilts();
        double xy = tilts(0);
        double xz = tilts(1);
        double yz = tilts(2);
        double ly = _matrix(1, 1);
        double lz = _matrix(2, 2);

        auto a = _matrix(0, 0);
        auto b = sqrt(ly * ly + xy * xy);
        auto c = sqrt(lz*lz + xz*xz + yz*yz);
        return {a, b, c};
    }

    const Vector3D Cell::get_tilts() const
    {
        double xy = _matrix(0, 1);
        double xz = _matrix(0, 2);
        double yz = _matrix(1, 2);
        return {xy, xz, yz};
    }

    const double Cell::get_volume() const
    {
        return xt::linalg::det(_matrix);
    }

    Matrix3D Cell::wrap(Matrix3D positions)
    {
        // PBC are all P
        if (_pbc[0] == P && _pbc[1] == P && _pbc[2] == P)
        {
            auto _inv_mat = get_inverse();
            auto reciprocal_vecs = xt::linalg::dot(_inv_mat, xt::transpose(positions));
            auto wrapped_reci_vecs = reciprocal_vecs - xt::floor(reciprocal_vecs);
            auto real_r = xt::linalg::dot(_matrix, wrapped_reci_vecs);
            return xt::transpose(real_r);
        }
        else
            throw NotImplementedError("Only PBC = P is implemented");
    }

    chemfiles::UnitCell to_chemfiles(const CellPtr &cell)
    {
        auto lengths = cell->get_lengths();
        auto angles = cell->get_angles();

        chemfiles::UnitCell chemfiles_cell(
            {lengths[0], lengths[1], lengths[2]},
            {angles[0], angles[1], angles[2]});
        return chemfiles_cell;
    }

    CellPtr new_cell(Vector3D lengths, Vector3D angles)
    {
        return std::make_shared<Cell>(lengths, angles);
    }

    CellPtr new_cell(chemfiles::UnitCell cell)
    {
        Vector3D lengths {cell.lengths()[0], cell.lengths()[1], cell.lengths()[2]};
        Vector3D angles {cell.angles()[0], cell.angles()[1], cell.angles()[2]};
        return std::make_shared<Cell>(lengths, angles);
    }
}