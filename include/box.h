#pragma once

#include <chemfiles.hpp>
#include <vector>
#include "log.h"
#include "error.h"
#include "vec3.hpp"
#include "mat3.hpp"

namespace molcpp
{


    class Box
    {

        public:

            enum PBC {
                F = 0,
                P = 1,
            };

            Box();
            Box(Vec3<double> lengths, Vec3<double> angles = {90, 90, 90});
            void set_periodic(PBC, PBC, PBC);
            const std::array<Box::PBC, 3> get_periodic() const;
            void set_lengths_and_angles(Vec3<double> lengths, Vec3<double> angles);
            const Mat3<double> get_matrix() const;
            const Mat3<double> get_inverse() const;
            const Vec3<double> get_lengths() const;
            const Vec3<double> get_angles() const;
            const Vec3<double> get_tilts() const;
            const double get_volume() const;
            std::vector<Vec3<double>> wrap(std::vector<Vec3<double>>&);
            Vec3<double> wrap(Vec3<double>&);
            double calc_distance(Vec3<double>&, Vec3<double>&);
            Vec3<double> calc_displacement(Vec3<double>&, Vec3<double>&);

        private:

            Mat3<double> _matrix;
            std::array<PBC, 3> _pbc;

    };

    std::unique_ptr<Box> create_box(Vec3<double> lengths = {0, 0, 0}, Vec3<double> angles = {90, 90, 90});
    std::unique_ptr<Box> from_chemfiles(chemfiles::UnitCell Cell);
    chemfiles::UnitCell to_chemfiles(Box* Box);

}