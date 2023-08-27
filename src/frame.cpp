#include "frame.h"
#include "connectivity.h"
#include "vec3.h"

namespace molcpp
{
Frame::Frame(size_t timestep) : _timestep(timestep), _box(new Box()), _connectivity()
{
}

size_t Frame::get_natoms() const
{
    if (_atom_properties.has(_mp_position))
        return 0;
    return _atom_properties.get<std::vector<Vec3<double>>>(_mp_position).size();
}

size_t Frame::get_nbonds() const
{
    return _connectivity.get_nbonds();
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

// void Frame::add_angle(size_t i, size_t j, size_t k)
// {
//     _connectivity.add_angle(i, j, k);
// }

// void Frame::add_dihedral(size_t i, size_t j, size_t k, size_t m)
// {
//     _connectivity.add_dihedral(i, j, k, m);
// }

// void Frame::add_improper(size_t i, size_t j, size_t k, size_t m)
// {
//     _connectivity.add_improper(i, j, k, m);
// }

// Topology *Frame::get_topology() const
// {
//     return _topology;
// }

// void Frame::set_topology(Topology *topology)
// {
//     _topology = topology;
// }

// void Frame::set_cell(Cell *cell)
// {
//     _cell = cell;
// }

// void Frame::set_cell(Vector3D lengths, Vector3D angles)
// {
//     _cell = new Cell(lengths, angles);
// }

// Cell *Frame::get_cell() const
// {
//     return _cell;
// }

// std::unique_ptr<Frame> create_frame()
// {
//     return std::make_unique<Frame>();
// }

Frame from_chemfiles(const chemfiles::Frame &chflFrame)
{
    size_t timestep = chflFrame.step();
    Frame _frame(timestep);
    // _frame.set_cell(from_chemfiles(chflFrame.cell()));
    _frame.set(_mp_position, std::vector<Vec3<double>>(chflFrame.positions().begin(), chflFrame.positions().end()));
    if (chflFrame.velocities())
    {
        _frame.set(_mp_velocity,
                   std::vector<Vec3<double>>(chflFrame.velocities()->begin(), chflFrame.velocities()->end()));
    }

    // get atom properties from topology
    size_t natoms = chflFrame.size();
    const chemfiles::Atom an_atom = chflFrame.topology()[0];
    for (auto props : an_atom.properties())
    {
        std::string key = props.first;
        chemfiles::Property::Kind kind = props.second.kind();
        switch (kind)
        {
        case chemfiles::Property::BOOL:
            _frame.set(key, std::vector<std::optional<bool>>(natoms));
            for (size_t i = 0; i < natoms; i++)
            {
                _frame.get<std::vector<std::optional<bool>>>(key)[i] = chflFrame.topology()[i].get(key)->as_bool();
            }
            break;
        case chemfiles::Property::DOUBLE:
            _frame.set(key, std::vector<std::optional<double>>(natoms));
            for (size_t i = 0; i < natoms; i++)
            {
                _frame.get<std::vector<std::optional<double>>>(key)[i] = chflFrame.topology()[i].get(key)->as_double();
            }
            break;
        case chemfiles::Property::STRING:
            _frame.set(key, std::vector<std::optional<std::string>>(natoms));
            for (size_t i = 0; i < natoms; i++)
            {
                _frame.get<std::vector<std::optional<std::string>>>(key)[i] =
                    chflFrame.topology()[i].get(key)->as_string();
            }
            break;
        case chemfiles::Property::VECTOR3D:
            _frame.set(key, std::vector<std::optional<Vec3<double>>>(natoms));
            for (size_t i = 0; i < natoms; i++)
            {
                auto chflVector = chflFrame.topology()[i].get(key)->as_vector3d();
                _frame.get<std::vector<std::optional<Vec3<double>>>>(key)[i] =
                    Vec3<double>(chflVector[0], chflVector[1], chflVector[2]);
            }
            break;
        }
    }

    auto nbonds = chflFrame.topology().bonds().size();
    for (size_t b = 0; b < nbonds; b++)
    {
        auto bond = chflFrame.topology().bonds()[b];
        size_t i = bond[0], j = bond[1];
        _frame.add_bond(i, j, BondOrder(chflFrame.topology().bond_order(i, j)));
    }

    // auto nangles = chflFrame.topology().angles().size();
    // for (size_t a = 0; a < nangles; a++)
    // {
    //     auto angle = chflFrame.topology().angles()[a];
    //     size_t i = angle[0], j = angle[1], k = angle[2];
    //     _frame.add_angle(i, j, k);
    // }

    return _frame;
}
} // namespace molcpp