#pragma once
#include <vector>
#include <string>
#include <map>

// #include <chemfiles.hpp>

#include "item.h"
#include "algo.h"
#include "log.h"
#include "graph.h"

namespace molcpp
{
    class Topology
    {
        public:
            
            Atom& create_atom(std::string name);
            Bond& create_bond(Atom& a1, Atom& a2);

        private:
            std::map<std::string, Atom> _atoms;
            std::vector<Bond> _bonds;
            Graph _graph;
    };
}