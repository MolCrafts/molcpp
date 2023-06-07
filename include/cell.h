#pragma once

#include <chemfiles.hpp>
#include "mplog.h"
#include "mperror.h"
#include "linalg.hpp"

namespace molcpp
{


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
            std::vector<Vector3D> wrap(std::vector<Vector3D>&);

        private:

            Matrix3D _matrix;
            std::array<PBC, 3> _pbc;

    };

    std::unique_ptr<Cell> create_cell(Vector3D lengths = {0, 0, 0}, Vector3D angles = {90, 90, 90});
    std::unique_ptr<Cell> from_chemfiles(chemfiles::UnitCell cell);
    chemfiles::UnitCell to_chemfiles(Cell* cell);

}