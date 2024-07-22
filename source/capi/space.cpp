#include "molcpp/capi/space.h"
#include "molcpp/capi/types.h"
#include "molcpp/capi/utils.hpp"
#include "molcpp/space.hpp"
#include "molcpp/types.hpp"
#include <memory>
#include <xtensor/xadapt.hpp>
#include <xtensor/xarray.hpp>

using namespace molcpp;

static_assert(sizeof(mol_box_style) == sizeof(int), "Wrong size for mol_box_style");

extern "C" MOL_BOX *mol_box_free()
{
    return new Box();
}

// extern "C" MOL_BOX *mol_box(const mol_vec3 matrix[3])
// {
//     return new Box(Mat3({
//         {matrix[0][0], matrix[0][1], matrix[0][2]},
//         {matrix[1][0], matrix[1][1], matrix[1][2]},
//         {matrix[2][0], matrix[2][1], matrix[2][2]},
//     }))
// }

extern "C" MOL_BOX *mol_box_from_lengths_angles(const mol_array lengths, const mol_array angles)
{
    return new Box(Box::from_lengths_angles(to_xarray(lengths), to_xarray(angles)));
}

extern "C" mol_array mol_box_wrap(const MOL_BOX* box, const mol_array xyz)
{
    auto wrapped = box->wrap(to_xarray(xyz));
    return to_molarr(wrapped);
}