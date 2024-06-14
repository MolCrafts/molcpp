#include "molcore/space.hpp"

namespace molcore
{

Box::Box() {}

bool Box::isin(const double x, const double y, const double z) const
{
  return true;
}
}  // namespace molcore
