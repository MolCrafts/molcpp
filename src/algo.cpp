#include "algo.h"

namespace molcpp
{

    size_t C(int n, int k)
    {
        size_t result = 1;
        for (int i = 1; i <= k; ++i)
        {
            result *= (n - i + 1);
            result /= i;
        }
        return result;
    }

    size_t P(int n, int k)
    {
        size_t result = 1;
        for (int i = 1; i <= k; ++i)
        {
            result *= (n - i + 1);
        }
        return result;
    }

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