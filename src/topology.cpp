#include "topology.h"
#include <cstddef>

namespace molcpp
{

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::istringstream stream(input);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

Atom &Topology::new_atom(std::string name)
{
    auto [iterator, result] = _atoms.insert({name, Atom(name)});
    return iterator->second;
}

void Topology::del_atom(std::string name)
{
    _atoms.erase(name);
}

void Topology::add_atom(Atom &atom)
{
    _atoms.insert({atom.get_name(), atom});
}

Atom &Topology::get_atom(std::string name)
{
    auto paths = split(name, '/');
    auto subtopo = *this;
    for (size_t depth = 0; depth < paths.size() - 1; depth++)
    {
        subtopo = subtopo._topos.at(paths[depth]);
    }
    return subtopo._atoms.at(paths.back());
}

size_t Topology::get_natoms() const
{
    return _atoms.size();
}

Bond &Topology::new_bond(Atom &a1, Atom &a2)
{
    _bonds.push_back(Bond(&a1, &a2));
    return _bonds.back();
}

void Topology::del_bond(Bond &bond)
{
    _bonds.erase(std::remove(_bonds.begin(), _bonds.end(), bond), _bonds.end());
}

void Topology::add_bond(Bond &bond)
{
    _bonds.push_back(bond);
}

Bond &Topology::get_bond(Atom &a1, Atom &a2)
{
    Bond _rhs = Bond(&a1, &a2);
    for (auto &_lhs : _bonds)
        if (_lhs == _rhs)
            return _lhs;
    throw KeyError("Bond not found");
}

void Topology::del_bond(Atom &a1, Atom &a2)
{
    auto bond = get_bond(a1, a2);
    del_bond(bond);
}

size_t Topology::get_nbonds() const
{
    return _bonds.size();
}

Topology &Topology::new_topo(std::string name)
{
    auto [iterator, result] = _topos.insert({name, Topology(name)});
    return iterator->second;
}

void Topology::del_topo(std::string name)
{
    _topos.erase(name);
}

Topology &Topology::add_topo(Topology &topo)
{
    auto [iterator, result] = _topos.insert({topo.get_name(), topo});
    return iterator->second;
}

Topology &Topology::get_topo(std::string name)
{
    auto paths = split(name, '/');
    auto subtopo = *this;
    for (size_t depth = 0; depth < paths.size() - 1; depth++)
    {
        subtopo = subtopo._topos.at(paths[depth]);
    }
    return subtopo._topos.at(paths.back());
}

std::string Topology::get_name() const
{
    return _name;
}


} // namespace molcpp