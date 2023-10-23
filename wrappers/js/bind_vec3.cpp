#include <emscripten/bind.h>

using namespace emscripten;

#include "vec3.h"
#include "mat3.h"

namespace molcpp{
    EMSCRIPTEN_BINDINGS(linalg) {
    class_<Vec3<double>>("Vec3")
    .constructor<double, double, double>()
    .function("getX", &Vec3<double>::getX)
    .function("getY", &Vec3<double>::getY)
    .function("getZ", &Vec3<double>::getZ)
    .function("setX", &Vec3<double>::setX)
    .function("setY", &Vec3<double>::setY)
    .function("setZ", &Vec3<double>::setZ)
    .function("add",  optional_override([](Vec3<double> &self, Vec3<double> &other) { return self + other; }));

    class_<Mat3<double>>("Mat3")
    .constructor<double, double, double, double, double, double, double, double, double>();
}
}