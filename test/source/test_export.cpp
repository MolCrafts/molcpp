#include <string>

#include <catch2/catch_test_macros.hpp>

#include "molcpp/molcpp.hpp"

TEST_CASE("Exported Class", "[exported]")
{
  auto const exported = exported_class {};

  CHECK(std::string("molcpp") == exported.name());
}
