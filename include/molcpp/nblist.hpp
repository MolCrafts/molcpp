#pragma once

#include <xtensor/xarray.hpp>

#include "molcpp/space.hpp"

namespace molcpp
{

    class BaseNeighborList
    {
        public:
            virtual xt::xarray<size_t> build(const xt::xarray<double> &xyz, const Box &box) = 0;
            virtual xt::xarray<size_t> update(const xt::xarray<double> &xyz, const Box &box) = 0;

    };

    class CellList : public BaseNeighborList
    {
        CellList(double cutoff);

        xt::xarray<size_t> build(const xt::xarray<double> &xyz, const Box &box); 

        xt::xarray<size_t> update(const xt::xarray<double> &xyz, const Box &box); 

        private:

    };

}