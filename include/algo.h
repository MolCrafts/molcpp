#pragma once

#include <vector>
#include <algorithm>
#include <exception>
#include <optional>

namespace molcpp
{
    // C(n, k) = C(n-1, k-1) * n / k
    size_t C(int n, int k);

    // P(n, k) = P(n-1, k-1) * n
    size_t P(int n, int k);

    // @brief: the number of combinations in a given container
    // @param: v - the container
    // @param: n - the number of elements in each combination
    // @return: combinations in 1D, which shape should be (size/n, n)
    std::vector<size_t> combination(std::vector<size_t> &v, size_t n);

}
