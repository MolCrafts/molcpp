#include <string>

#include "molcore/molcore.hpp"

exported_class::exported_class()
    : m_name {"molcore"}
{
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}
