#include <string>

#include <catch2/catch_test_macros.hpp>

#include "molcore/molcore.hpp"

TEST_CASE("Exported Class", "[exported]")
{
  auto const exported = exported_class {};

  CHECK(std::string("molcore") == exported.name());
}
