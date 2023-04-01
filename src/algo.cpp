#include "algo.h"

namespace molcpp
{
    // @brief: the number of combinations in a given container
    // @param: v - the container
    // @param: n - the number of elements in each combination
    // @return: combinations in 1D, which shape should be (size/n, n)

    std::vector<size_t> combination(std::vector<size_t> &v, size_t n)
    {
        std::vector<size_t> result;
        std::vector<bool> vbool(v.size());
        std::fill(vbool.end() - n, vbool.end(), true);
        do
        {
            for (size_t i = 0; i < v.size(); ++i)
            {
                if (vbool[i])
                {
                    result.push_back(v[i]);
                }
            }
        } while (std::next_permutation(vbool.begin(), vbool.end()));
        return result;

    }


}