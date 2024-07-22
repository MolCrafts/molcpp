#include "doctest/doctest.h"

#include "molcpp/types.hpp"

#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>

using namespace molcpp;

TEST_CASE("TestProperties") {

    SUBCASE("test_init") {
            
        Property<int, double, std::string> prop;
        prop.set<int>("int", 42);
        prop.set<double>("double", 42.0);
        prop.set<std::string>("string", "42");
        CHECK(prop.get<int>("int") == 42);
        CHECK(prop.get<double>("double") == 42.0);
        CHECK(prop.get<std::string>("string") == "42");
    }

}
