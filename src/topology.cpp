#include "topology.h"

namespace molcpp
{
    Atom& Topology::create_atom(std::string name)
    {
        auto [iterator, result] = _atoms.insert({name, Atom(name)});
        return iterator->second;
    }
}