#include <catch2/catch_test_macros.hpp>

#include "molcore/space.hpp"

namespace molcore
{

TEST_CASE("Test Space", "[Box]")
{
  auto box = Box();
  CHECK(box.isin(1, 2, 3));
}

}  // namespace molcore