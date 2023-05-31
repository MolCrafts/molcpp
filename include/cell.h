#pragma once

#include <chemfiles.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include "mplog.h"
#include "mperror.h"

namespace molcpp
{

    using Vector = xt::xarray<double>;
    using Matrix = xt::xarray<double>;

    class Cell
    {

        public:

            enum PBC {
                P = 0,
                F = 1,
                S = 2,
            };

            Cell();
            Cell(Vector lengths, Vector angles = {90, 90, 90});
            void set_boundary(PBC, PBC, PBC);
            void set_lengths_and_angles(Vector lengths, Vector angles);
            const Matrix get_matrix() const;
            const Matrix get_inverse() const;
            const Vector get_lengths() const;
            const Vector get_angles() const;
            const Vector get_tilts() const;
            const double get_volume() const;
            Matrix wrap(Matrix);

        private:

            Matrix _matrix;
            std::array<PBC, 3> _pbc;

    };

    using CellPtr = std::shared_ptr<Cell>;

    CellPtr new_cell(Vector lengths = {0, 0, 0}, Vector angles = {90, 90, 90});
    CellPtr new_cell(chemfiles::UnitCell cell);
    chemfiles::UnitCell to_chemfiles(const CellPtr &cell);

}