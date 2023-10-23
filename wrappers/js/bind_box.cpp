#include <emscripten/bind.h>
#include <vector>

using namespace emscripten;

#include "box.h"



namespace molcpp{

    std::vector<double> flatten(Mat3<double> mat) {
        std::vector<double> result;
        for (int i = 0; i < 3; i++) {
            result.push_back(mat[i][0]);
            result.push_back(mat[i][1]);
            result.push_back(mat[i][2]);
        }
        return result;
    }

    EMSCRIPTEN_BINDINGS(box) {
    class_<Box>("Box")
    .constructor<>()
    .function("set_lengths_and_angles", &Box::set_lengths_and_angles)
    .property("matrix", &Box::get_matrix);

}
}