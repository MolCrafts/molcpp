#pragma once

#include <gtest/gtest.h>
#include <chemfiles.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "xtensor/xtensor.hpp"
#include <filesystem>

namespace fs = std::filesystem;
const fs::path TEST_DATA_DIR = fs::path(__FILE__).parent_path() / "tests-data";
