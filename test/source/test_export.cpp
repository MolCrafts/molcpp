#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include "molcpp/molcpp.hpp"

TEST_CASE("Test Exported Class")
{
  auto const exported = exported_class {};

  CHECK(std::string("molcpp") == exported.name());
}
