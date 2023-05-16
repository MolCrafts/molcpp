#pragma once

#include <chemfiles.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include "mplog.h"
#include "mperror.h"

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
            Cell(Vector3D lengths, Vector3D angles = {90, 90, 90});
            void set_boundary(PBC, PBC, PBC);
            void set_lengths_and_angles(Vector3D lengths, Vector3D angles);
            const Matrix3D get_matrix() const;
            const Matrix3D get_inverse() const;
            const Vector3D get_lengths() const;
            const Vector3D get_angles() const;
            const Vector3D get_tilts() const;
            const double get_volume() const;
            Matrix3D wrap(Matrix3D);

        private:

            Matrix3D _matrix;
            std::array<PBC, 3> _pbc;

    };

    using CellPtr = std::shared_ptr<Cell>;

    CellPtr new_cell(Vector3D lengths = {0, 0, 0}, Vector3D tilts = {0, 0, 0});
    CellPtr new_cell(chemfiles::UnitCell cell);
    chemfiles::UnitCell to_chemfiles(const CellPtr &cell);

}