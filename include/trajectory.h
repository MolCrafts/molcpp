#pragma once
#include <optional>
#include <string>
#include <map>
#include <memory>
#include "frame.h"
#include "algo.h"
#include "error.h"

namespace molcpp
{

    class Trajectory
    {

    public:

        Trajectory();

        void add_frame(const Frame& frame);
        std::vector<Frame> get_frames() const;

    private:

        std::map<size_t, Frame> _frames;
        
    };

}