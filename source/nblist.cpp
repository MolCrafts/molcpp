#include "molcpp/nblist.hpp"

using namespace molcpp;

CellList::CellList(double cutoff) : _cutoff(cutoff)
{
}

xt::xarray<size_t> CellList::build(const xt::xarray<double> &xyz, const Box &box)
{
    auto lengths = box.get_distance_between_faces();
    auto cell_shape = xt::xarray<size_t>(
        {static_cast<size_t>(std::ceil(lengths[0] / _cutoff)),
         static_cast<size_t>(std::ceil(lengths[1] / _cutoff)),
         static_cast<size_t>(std::ceil(lengths[2] / _cutoff))}
    );

    auto n_cells = cell_shape[0] * cell_shape[1] * cell_shape[2];
}

xt::xarray<size_t> CellList::update(const xt::xarray<double> &xyz, const Box &box)
{
    
}