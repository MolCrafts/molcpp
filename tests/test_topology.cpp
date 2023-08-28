#include "topology.h"
#include <doctest/doctest.h>

TEST_SUITE("Test Topology")
{

    TEST_CASE("Test create atom")
    {
        molcpp::Topology topology;
        auto &atom1 = topology.create_atom("atom1");
        auto &atom2 = topology.create_atom("atom2");
        CHECK(atom1.get_id() != atom2.get_id());
    }

}