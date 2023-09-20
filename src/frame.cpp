#include "frame.h"
#include "connectivity.h"
#include "item.h"
#include "vec3.h"
#include <algorithm>
#include <chemfiles/Atom.hpp>

namespace molcpp
{
Frame::Frame(size_t timestep) : _timestep(timestep), _box(Box()), _connectivity()
{
}

size_t Frame::get_natoms() const
{
    if (_atom_properties.has(_mp_position))
        return 0;
    return _atom_properties.get<std::vector<Vec3<double>>>(_mp_position).size();
}

std::vector<Atom> Frame::get_atoms()
{
    std::vector<Atom> atoms;
    atoms.reserve(get_natoms());
    if (_atom_properties.has(_mp_position))
    {
        std::vector<std::string> keys = _atom_properties.keys();
        std::vector<Vec3<double>> positions = _atom_properties.get<std::vector<Vec3<double>>>(_mp_position);
        for (size_t i = 0; i < positions.size(); i++)
        {
            auto atom = Atom(std::string(""));
            for (const auto &key : keys)
            {
                atom.set(key, _atom_properties.get(key, i));
            }
            atoms[i] = atom;
        }
    }
    return atoms;
}

size_t Frame::get_nbonds() const
{
    return _connectivity.get_nbonds();
}

std::vector<BondIdx> Frame::get_bonds()
{
    std::vector<BondIdx> bonds;
    bonds.reserve(get_nbonds());
    std::transform(_connectivity.bonds().begin(), _connectivity.bonds().end(), bonds.begin(),
                   [](auto &bond) { return BondIdx(bond[0], bond[1]); });
    return bonds;
}

size_t Frame::get_timestep() const
{
    return _timestep;
}
 
void Frame::set_timestep(size_t timestep)
{
    _timestep = timestep;
}

void Frame::add_bond(size_t i, size_t j, BondOrder order)
{
    _connectivity.add_bond(i, j, order);
}

Box &Frame::get_box()
{
    return _box;
}

} // namespace molcpp