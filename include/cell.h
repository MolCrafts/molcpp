#pragma once

#include <chemfiles.hpp>
#include "mplog.h"
#include "mperror.h"
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>

namespace molcpp
{

    using Vector3D = xt::xarray<double>;
    using Matrix3D = xt::xarray<double>;

    class Cell
    {

        public:

            enum PBC {
                P = 0,
                F = 1,
                S = 2,
            };

            Cell();
            Cell(Vector3D lengths, Vector3D tilts = {0, 0, 0});
            const Matrix3D get_matrix() const;
            const Matrix3D get_inverse() const;
            void set_boundary(PBC, PBC, PBC);
            const Vector3D get_lengths() const;
            const Vector3D get_tilts() const;
            void set_lengths(Vector3D lengths);
            void set_tilts(Vector3D titls);
            const double get_volume() const;
            Matrix3D wrap(Matrix3D);

        private:

            Matrix3D _matrix;
            std::array<PBC, 3> _pbc;

    };

    chemfiles::UnitCell to_chemfiles(const Cell &cell);

}