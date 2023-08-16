#include "utils.h"
#include "algo.h"

TEST("TestAlgo, test_combination_number")
{
    CHECK_EQ(molcpp::combination_number(5, 2), 10);
    CHECK_EQ(molcpp::combination_number(5, 3), 10);
    CHECK_EQ(molcpp::combination_number(5, 4), 5);
    CHECK_EQ(molcpp::combination_number(5, 5), 1);
    CHECK_EQ(molcpp::combination_number(5, 6), 0);
}

TEST("TestAlgo, test_permutation_number")
{
    CHECK_EQ(molcpp::permutation_number(5, 2), 20);
    CHECK_EQ(molcpp::permutation_number(5, 3), 60);
    CHECK_EQ(molcpp::permutation_number(5, 4), 120);
    CHECK_EQ(molcpp::permutation_number(5, 5), 120);
    CHECK_EQ(molcpp::permutation_number(5, 6), 0);
}

