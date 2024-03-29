#include "utils.h"
#include "algo.h"

TEST(TestAlgo, test_combination_number)
{
    EXPECT_EQ(molcpp::combination_number(5, 2), 10);
    EXPECT_EQ(molcpp::combination_number(5, 3), 10);
    EXPECT_EQ(molcpp::combination_number(5, 4), 5);
    EXPECT_EQ(molcpp::combination_number(5, 5), 1);
    EXPECT_EQ(molcpp::combination_number(5, 6), 0);
}

TEST(TestAlgo, test_permutation_number)
{
    EXPECT_EQ(molcpp::permutation_number(5, 2), 20);
    EXPECT_EQ(molcpp::permutation_number(5, 3), 60);
    EXPECT_EQ(molcpp::permutation_number(5, 4), 120);
    EXPECT_EQ(molcpp::permutation_number(5, 5), 120);
    EXPECT_EQ(molcpp::permutation_number(5, 6), 0);
}

