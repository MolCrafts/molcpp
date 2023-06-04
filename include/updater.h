#pragma once

#include "minimizer/min.h"
#include "system.h"
#include "atom.h"
#include "neighborList.h"

namespace molcpp
{
    class Updater
    {
        public:
            Updater(System*, Minimizer*);
            ~Updater();

            Frame* update(Frame*);

        private:
            System* _current_system;
            Minimizer* _minimizer;

    };
}