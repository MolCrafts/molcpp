#include <pybind11/pybind11.h>
#define FORCE_IMPORT_ARRAY
#include "xtensor-python/pyarray.hpp"

namespace py = pybind11;

PYBIND11_MODULE(molcpp, m) {

    xt::import_numpy();

    m.doc() = "molcpp python bindings";
    py::class_<Box>(m, "Box")
        .def(py::init<>())
        .def_static("from_lengths_angles", &Box::from_lengths_angles)
        .def("wrap", &Box::wrap)
        .def("get_style", &Box::get_style)
        .def("get_matrix", &Box::get_matrix)
        .def("get_inv", &Box::get_inv)
        .def("get_lengths", &Box::get_lengths)
        .def("get_angles", &Box::get_angles)
        .def("get_volume", &Box::get_volume)

}