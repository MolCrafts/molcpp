#pragma once

#include "forcefield.h"
#include "trajectory.h"

namespace molcpp
{

    class System
    {
        public:
        System();

        // void select_frame(size_t);



        private:
            ForceField _ff;
            Trajectory _traj;
            Updater _updater;
            Frame* _current_frame;
    };

}