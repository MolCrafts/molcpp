#include "topology.h"
#include <doctest/doctest.h>

TEST_SUITE("Test Topology")
{

    TEST_CASE("Test create atom")
    {
        molcpp::Topology topology("topo");
        auto &atom1 = topology.new_atom("atom1");
        auto &atom2 = topology.new_atom("atom2");
        CHECK(atom1.get_id() != atom2.get_id());
    }

    TEST_CASE("Test create bond")
    {
        molcpp::Topology topology("topo");
        auto &atom1 = topology.new_atom("atom1");
        auto &atom2 = topology.new_atom("atom2");
        auto &bond = topology.new_bond(atom1, atom2);
        CHECK(topology.get_nbonds() == 1);
    }

}