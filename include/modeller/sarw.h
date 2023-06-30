#include <cmath>
#include <vector>
#include <array>
#include <random>
#include <string>
#include "mperror.h"
#include "mplog.h"

#define PI 3.14159265
#define MAX_X 300
#define MAX_Y 300
#define MAX_Z 300

namespace molcpp
{
    using coord = std::array<size_t, 3>;
    using state = std::array<size_t, 4>;
    using grid = std::vector<std::vector<std::vector<state>>>;
    class SARW
    {

    public:
        SARW(size_t, size_t, size_t, double);

        void allocate(size_t, size_t, size_t);

        std::vector<coord> single(size_t length);

    private:
        size_t _x, _y, _z;
        grid site;
        grid loc_dens;
        grid snd_dens;
        float _density, _max_density;
        size_t _occupied, _n_sites;
    };
}