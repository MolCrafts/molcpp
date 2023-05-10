#include "frame.h"

namespace molcpp
{
    // xt::xarray<double> copy_to_xarray(const std::vector<chemfiles::Vector3D>& vec, std::vector<size_t> shape)
    // {
        
    //     std::vector<double> temp_arr(shape[0]*shape[1]);
    //     for (size_t i = 0; i < shape[0]; i++)
    //     {
    //         for (size_t j = 0; j < shape[1]; j++)
    //         {
    //             temp_arr[i*shape[1] + j] = vec[i][j];
    //         }
    //     }
    //     return xt::adapt(temp_arr, shape);
    // }

    Frame::Frame() : _current_step(0), _topology(Topology())
    {
    }

    size_t Frame::get_natoms() const
    {
        return _topology.get_natoms();
    }

    size_t Frame::get_nbonds() const
    {
        return _topology.get_nbonds();
    }

    size_t Frame::get_current_step() const
    {
        return _current_step;
    }

    Topology& Frame::get_topology()
    {
        return _topology;
    }

}