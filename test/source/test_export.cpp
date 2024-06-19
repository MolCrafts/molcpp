#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include "molcore/molcore.hpp"

TEST_CASE("Test Exported Class")
{
  auto const exported = exported_class {};

  CHECK(std::string("molcore") == exported.name());
}
