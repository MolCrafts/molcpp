#include "cell.h"

namespace molcpp
{

    Cell::Cell() : _matrix(xt::zeros<double>({3, 3})), _pbc({P, P, P})
    {
    }

    Cell::Cell(Vector3D lengths) : _matrix(xt::zeros<double>({3, 3})), _pbc({P, P, P})
    {
        set_lengths(lengths);
    }

    Cell::Cell(Vector3D lengths, Vector3D tilts) : _matrix(xt::zeros<double>({3, 3})), _pbc({P, P, P})
    {
        set_lengths(lengths);
        set_tilts(tilts);
    }

    Matrix3D Cell::get_matrix()
    {
        return _matrix;
    }

    Matrix3D Cell::get_inverse()
    {
        return xt::linalg::inv(_matrix);
    }

    void Cell::set_boundary(PBC x, PBC y, PBC z)
    {
        _pbc = {x, y, z};
    }

    Vector3D Cell::get_lengths()
    {
        return Vector3D({_matrix(0, 0), _matrix(1, 1), _matrix(2, 2)});
    }

    Vector3D Cell::get_tilts()
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

    double Cell::get_volume()
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
        else throw NotImplementedError("Only PBC = P is implemented");
    }

}