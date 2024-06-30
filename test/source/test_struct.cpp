#include "doctest/doctest.h"
#include "molcpp/struct.hpp"
#include "molcpp/types.hpp"

#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xrandom.hpp>

using namespace molcpp;

TEST_CASE("TestCreateStruct") {

    SUBCASE("test_empty_struct") {
        Struct s;
        // CHECK(s.get_n_atoms() == 0);
        // CHECK(s.get_n_bonds() == 0);
        // CHECK(s.get_n_angles() == 0);
        // CHECK(s.get_n_dihedrals() == 0);
        // CHECK(s.get_n_impropers() == 0);
    }

}

TEST_CASE("TestAddProps") {

    Struct s;

    SUBCASE("test_add_atoms") {
        xt::xarray<int> random_int = xt::random::randint<int>({10}, 0, 10);
        s.add_atom_prop("int", random_int);
    }

}