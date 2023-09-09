#pragma once
#include <filesystem>
#include <doctest/doctest.h>

namespace fs = std::filesystem;
const fs::path TEST_DATA_DIR = fs::path(__FILE__).parent_path() / "tests-data";
const fs::path TMP_DIR = fs::path(__FILE__).parent_path() / "tmp";