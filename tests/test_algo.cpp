#include "utils.h"
#include "algo.h"

TEST(TestAlgo, test_combination)
{
    std::vector<size_t> candidiate = {0, 1};
    auto combinations = molcpp::combination(candidiate, 2);
    EXPECT_EQ(combinations.size()/2, 1);

    candidiate = {0, 1, 2};
    combinations = molcpp::combination(candidiate, 2);
    EXPECT_EQ(combinations.size()/2, 3);
}
