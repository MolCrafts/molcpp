#include "topology.h"

namespace molcpp
{
Atom &Topology::new_atom(std::string name)
{
    auto [iterator, result] = _atoms.insert({name, Atom(name)});
    return iterator->second;
}

void Topology::del_atom(std::string name)
{
    _atoms.erase(name);
}

Atom &Topology::add_atom(Atom &atom)
{
    auto [iterator, result] = _atoms.insert({atom.get_name(), atom});
    return iterator->second;
}

Atom &Topology::get_atom(std::string name)
{
    return _atoms.at(name);
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

Bond &Topology::add_bond(Bond &bond)
{
    _bonds.push_back(bond);
    return _bonds.back();
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
    return _topos.at(name);
}

std::string Topology::get_name() const
{
    return _name;
}


} // namespace molcpp