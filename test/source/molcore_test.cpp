#include <string>

#include "molcore/molcore.hpp"

auto main() -> int
{
  auto const exported = exported_class {};

  return std::string("molcore") == exported.name() ? 0 : 1;
}
