#pragma once
#include <filesystem>

namespace fs = std::filesystem;
const fs::path TEST_DATA_DIR = fs::path(__FILE__).parent_path() / "tests-data";
 