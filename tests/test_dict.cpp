#include <any>
#include <string>
#include <doctest/doctest.h>

#include "dict.h"

using namespace std::literals::string_literals;

namespace molcpp {
TEST_CASE("Dict get") {
  Dict d{{"key1", 42}, {"key2", 3.14}, {"key3", "value"s}};

  CHECK(std::any_cast<int>(d["key1"]) == 42);
  CHECK(d.get<double>("key2") == 3.14);
  CHECK(d.get<std::string>("key3") == "value");
  CHECK(d.get<std::string>("nonexistent_key", "default_value") ==
        "default_value");
}

TEST_CASE("Dict set") {
  Dict d;
  d["key1"] = 42;

  CHECK(d.get<int>("key1") == 42);
}

TEST_CASE("Dict setdefault") {

  Dict d;

  CHECK(d.setdefault("key1", 3.14) == 3.14);
  CHECK(d.setdefault<std::string>("key2", "value") == "value");
}

TEST_CASE("Dict keys and values") {
  Dict d{{"key1", 42}, {"key2", 3.14}, {"key3", "value"}};

  CHECK(d.keys() == std::vector<std::string>{"key1", "key2", "key3"});
  // CHECK(d.values() == std::vector<std::any>{42, 3.14, "value"});
}

TEST_CASE("Dict update") {
  Dict d;
  Dict other{{"key1", 1}, {"key3", "new_value"s}};
  d.update(other);
  CHECK(d.get<int>("key1") == 1);
  CHECK(d.get<std::string>("key3") == "new_value");
}

TEST_CASE("Dict erase") {
  Dict d{{"key1", 42}, {"key2", 3.14}, {"key3", "value"}};
  CHECK(d.size() == 3);
  CHECK(!d.empty());
  d.clear();
  CHECK(d.size() == 0);
  CHECK(d.empty());
}
} // namespace molcpp