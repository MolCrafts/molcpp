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
            Cell(Vector3D lengths);
            Cell(Vector3D lengths, Vector3D tilts);
            Matrix3D get_matrix();
            Matrix3D get_inverse();
            void set_boundary(PBC, PBC, PBC);
            Vector3D get_lengths();
            Vector3D get_tilts();
            void set_lengths(Vector3D lengths);
            void set_tilts(Vector3D titls);
            double get_volume();
            Matrix3D wrap(Matrix3D);

        private:

            Matrix3D _matrix;
            std::array<PBC, 3> _pbc;

    };

}