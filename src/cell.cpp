#include "cell.h"

namespace molcpp
{

    // Sinus and Cosine for degree values
    constexpr double pi = 3.141592653589793238463;
    // static double deg2rad(double x)
    // {
    //     return x * pi / 180.0;
    // }

    static double rad2deg(double x)
    {
        return x * 180.0 / pi;
    }

    static double dcos(double alpha)
    {
        return rad2deg(acos(alpha));
    }

    // static double cosd(double theta)
    // {
    //     return cos(deg2rad(theta));
    // }

    // static double sind(double theta)
    // {
    //     return sin(deg2rad(theta));
    // }

    Cell::Cell() : _matrix(xt::zeros<double>({3, 3})), _pbc({P, P, P})
    {
    }

    Cell::Cell(Vector3D lengths, Vector3D tilts) : _matrix(xt::zeros<double>({3, 3})), _pbc({P, P, P})
    {
        set_lengths(lengths);
        set_tilts(tilts);
    }

    const Matrix3D Cell::get_matrix() const
    {
        return _matrix;
    }

    const Matrix3D Cell::get_inverse() const
    {
        return xt::linalg::inv(_matrix);
    }

    void Cell::set_boundary(PBC x, PBC y, PBC z)
    {
        _pbc = {x, y, z};
    }

    const Vector3D Cell::get_lengths() const
    {
        return Vector3D({_matrix(0, 0), _matrix(1, 1), _matrix(2, 2)});
    }

    const Vector3D Cell::get_tilts() const
    {
        return Vector3D({_matrix(0, 1), _matrix(0, 2), _matrix(1, 2)});
    }

    void Cell::set_lengths(Vector3D lengths)
    {
        _matrix(0, 0) = lengths(0);
        _matrix(1, 1) = lengths(1);
        _matrix(2, 2) = lengths(2);
    }

    void Cell::set_tilts(Vector3D tilts)
    {
        _matrix(0, 1) = tilts(0);
        _matrix(0, 2) = tilts(1);
        _matrix(1, 2) = tilts(2);
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

    chemfiles::UnitCell to_chemfiles(const Cell &cell)
    {
        auto lengths = cell.get_lengths();
        auto tilts = cell.get_tilts();

        chemfiles::UnitCell chemfiles_cell(
            {lengths[0], lengths[1], lengths[2]},
            {dcos(tilts(0) / lengths(1)),
             dcos(tilts(1) / lengths(2)),
             dcos(tilts(2) / lengths(0))});
        return chemfiles_cell;
    }
}