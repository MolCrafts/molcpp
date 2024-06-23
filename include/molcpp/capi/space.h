#pragma once

#include "molcpp/export.hpp"
#include "molcpp/capi/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Available box shapes
typedef enum {  // NOLINT: this is both a C and C++ file
    /// The three angles are 90°
    MOL_BOX_ORTHORHOMBIC = 0,
    /// The three angles may not be 90°
    MOL_BOX_TRICLINIC = 1,
    /// Cell shape when there is no periodic boundary conditions
    MOL_BOX_INFINITE = 2,
} mol_box_style;

MOLCPP_EXPORT MOL_BOX* mol_box_free();

// MOLCPP_EXPORT MOL_BOX* mol_box(const mol_vec3 matrix[3]);

// MOLCPP_EXPORT MOL_BOX* mol_box_from_lengths_angles(const mol_vec3 lengths, const mol_vec3 angles);

#ifdef __cplusplus
}
#endif