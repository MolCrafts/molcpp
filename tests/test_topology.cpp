#include "topology.h"
#include <doctest/doctest.h>

namespace molcpp
{

TEST_SUITE("Test Topology")
{

    // TEST_CASE("Test create atom")
    // {
    //     Topology topology("topo");
    //     auto &atom1 = topology.new_atom("atom1");
    //     auto &atom2 = topology.new_atom("atom2");
    //     CHECK(atom1.get_id() != atom2.get_id());
    // }

    TEST_CASE("test get atom")
    {
        Topology topo1("topo1");
        auto &atom1 = topo1.new_atom("atom1");
        // CHECK(topo1.get_atom("atom1").get_name() == "atom1");

        auto &topo2 = topo1.new_topo("topo2");
        auto &atom2 = topo2.new_atom("atom2");
        CHECK(topo1.get_atom("topo2/atom2").get_name() == "atom2");
    }

    // TEST_CASE("Test create bond")
    // {
    //     Topology topology("topo");
    //     auto &atom1 = topology.new_atom("atom1");
    //     auto &atom2 = topology.new_atom("atom2");
    //     auto &bond = topology.new_bond(atom1, atom2);
    //     CHECK(topology.get_nbonds() == 1);
    // }

    // TEST_CASE("Test create topology")
    // {
    //     Topology topology("topo");
    //     auto &topo1 = topology.new_topo("topo1");
    //     auto &topo2 = topology.new_topo("topo2");
    //     auto &topo3 = topo2.new_topo("topo3");
    //     CHECK(topology.get_topo("topo1").get_name() == "topo1");
    //     CHECK(topology.get_topo("topo2").get_name() == "topo2");
    //     CHECK(topology.get_topo("topo2/topo3").get_name() == "topo3");
    // }
}

} // namespace molcpp