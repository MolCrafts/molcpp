#ifndef ALGO_H
#define ALGO_H

#include <vector>
#include <algorithm>
#include <exception>
#include <optional>

namespace molcpp
{

    // @brief: the number of combinations in a given container
    // @param: v - the container
    // @param: n - the number of elements in each combination
    // @return: the number of combinations
    std::vector<size_t> combination(std::vector<size_t> &, size_t);

    // @brief: find the index of a value in a container
    // @param: container - the container
    // @param: value - the value to be found
    // @return: the index of the value in the container
    template<typename Container, typename T>
    std::optional<size_t> find_in_container(const Container& container, const T& value)
    {
        auto it = std::find(container.begin(), container.end(), value);
        if (it != container.end())
        {
            return std::distance(container.begin(), it);
        }
        else
        {
            return std::nullopt;
        }
    }
}


#endif // ALGO_H