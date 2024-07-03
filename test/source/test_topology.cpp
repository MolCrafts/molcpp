#include "doctest/doctest.h"
#include "molcpp/topology.hpp"
#include "molcpp/types.hpp"

using namespace molcpp;

TEST_CASE("TestTopologyInit")
{

    Topology topo;

    CHECK(topo.get_n_bonds() == 0);
    CHECK(topo.get_n_angles() == 0);
}

TEST_CASE("TestTopologyAddDeleteBond")
{
    Topology topo;
    topo.add_bond(0, 1, 0);
    topo.add_bond(0, 2, 1);
    CHECK(topo.get_n_bonds() == 2);
    Topology::Bond bond = topo.get_bonds()[0];
    CHECK(bond.i == 0);
    CHECK(bond.j == 1);
    CHECK(bond.id == 0);
    std::cout << topo.get_n_bonds() << std::endl;
    topo.del_bond(0, 1);
    CHECK(topo.get_n_bonds() == 1);
    topo.del_bond(1);
    CHECK(topo.get_n_bonds() == 0);
}

TEST_CASE("TestTopologyAddDeleteAngle")
{

    Topology topo;

    topo.add_angle(0, 1, 2, 0);
    topo.add_angle(0, 2, 3, 1);
    CHECK(topo.get_n_angles() == 2);
    Topology::Angle angle = topo.get_angles()[0];
    CHECK(angle.i == 0);
    CHECK(angle.j == 1);
    CHECK(angle.k == 2);
    CHECK(angle.id == 0);

    topo.del_angle(0, 1, 2);
    CHECK(topo.get_n_angles() == 1);
    topo.del_angle(1);
    CHECK(topo.get_n_angles() == 0);
}