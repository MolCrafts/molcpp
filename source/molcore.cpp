#include <string>

#include "molcpp/molcpp.hpp"

exported_class::exported_class()
    : m_name {"molcpp"}
{
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}
