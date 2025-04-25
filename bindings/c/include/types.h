#pragma once

#include "molcpp/export.hpp"
#include <stddef.h>

#if defined(__cplusplus)
namespace molcpp {
    class Region;
    class Boundary;
    class Box;
}

typedef molcpp::Region MOL_REGION;
typedef molcpp::Boundary MOL_BOUNDARY;
typedef molcpp::Box MOL_BOX;

#else

typedef struct MOL_REGION MOL_REGION;
typedef struct MOL_BOUNDARY MOL_BOUNDARY;
typedef struct MOL_BOX MOL_BOX;

#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {  // NOLINT: this is both a C and C++ file
    /// Status code for successful operations.
    MOL_SUCCESS = 0,
    /// Status code for error concerning memory: out of memory, wrong size for
    /// pre-allocated buffers, *etc.*
    MOL_MEMORY_ERROR = 1,
    /// Status code for error concerning files: the file do not exist, the user
    /// does not have rights to open it, *etc.*
    MOL_FILE_ERROR = 2,
    /// Status code for error in file formating, i.e. for invalid files.
    MOL_FORMAT_ERROR = 3,
    /// Status code for invalid selection strings.
    MOL_SELECTION_ERROR = 4,
    /* error code 5 used to be MOL_CONFIGURATION_ERROR */
    /// Status code for out of bounds errors.
    MOL_OUT_OF_BOUNDS = 6,
    /// Status code for errors related to properties.
    MOL_PROPERTY_ERROR = 7,
    /// Status code for any other error from Chemfiles.
    MOL_GENERIC_ERROR = 254,
    /// Status code for error in the C++ standard library.
    MOL_CXX_ERROR = 255,
} mol_status;

typedef double mol_vec3[3];

const size_t MAX_DIMS = 5;

typedef struct {
    float *data;
    size_t size;
    size_t ndims;
    size_t shape[MAX_DIMS];
} mol_array;

#ifdef __cplusplus
}
#endif