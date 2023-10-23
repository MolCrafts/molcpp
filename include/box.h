#pragma once

#include <vector>
#include <array>
#include <cmath>

#include "vec3.h"
#include "mat3.h"
#include "error.h"

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
            const std::array<Vec3<double>, 8> get_vertices() const;
            double get_volume() const;
            std::vector<Vec3<double>> wrap(std::vector<Vec3<double>>& points);
            Vec3<double> wrap(Vec3<double>& point);
            double dist(Vec3<double>& point1, Vec3<double>& point2);
            Vec3<double> diff(Vec3<double>&, Vec3<double>&);

        private:

            Mat3<double> _matrix;
            std::array<PBC, 3> _pbc;

    };

}
