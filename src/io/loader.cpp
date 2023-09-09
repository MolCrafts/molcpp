#include "loader.h"
#include "trajectory.h"
#include "vec3.h"
#include <chemfiles/UnitCell.hpp>

namespace molcpp
{

Vec3<double> from_chemfiles(const chemfiles::Vector3D &chflVector)
{
    return Vec3<double>(chflVector[0], chflVector[1], chflVector[2]);
}

chemfiles::Vector3D to_chemfiles(const Vec3<double> &vector)
{
    return chemfiles::Vector3D(vector[0], vector[1], vector[2]);
}

DataReader::DataReader(const std::string &path, const std::string &format)
    : _path{path}, _format{format}, _chflTraj(path, 'r', format)
{
}

DataReader::~DataReader()
{
    if (is_open())
    {
        close();
    }
}

void DataReader::open(const std::string &path, const std::string &format)
{

    if (is_open())
    {
        close();
    }

    _path = path;
    _format = format;

    _chflTraj = chemfiles::Trajectory(path, 'w', format);
}

void DataReader::close()
{
    _chflTraj.close();
}

bool DataReader::is_open() const
{
    return false;
}

Frame DataReader::load_frame(size_t step)
{
    chemfiles::Frame chflFrame = _chflTraj.read_step(step);
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

Trajectory DataReader::load_traj(size_t start, size_t stop, size_t step)
{
    std::vector<size_t> steps((stop - start + step - 1) / step); // 创建结果向量
    size_t value = start;
    for (size_t i = 0; i < steps.size(); i++) {
        steps[i] = value;
        value += step;
    }

    Trajectory traj;
    for (size_t step : steps)
    {
        traj.add_frame(load_frame(step));
    }
    return traj;
}

DataWriter::DataWriter(const std::string &path, const std::string &format)
    : _path{path}, _format{format}, _chflTraj(path, 'w', format)
{
}

DataWriter::~DataWriter()
{
    if (is_open())
    {
        close();
    }
}

void DataWriter::open(const std::string &path, const std::string &format)
{
    if (is_open())
    {
        close();
    }

    _path = path;
    _format = format;

    _chflTraj = chemfiles::Trajectory(path, 'w', format);
}

void DataWriter::close()
{
    _chflTraj.close();
}

bool DataWriter::is_open() const
{
    return false;
}

void DataWriter::write_frame(Frame &frame)
{

    const auto lengths = frame.get_box().get_lengths();
    const auto angles = frame.get_box().get_angles();

    chemfiles::UnitCell chflCell({lengths[0], lengths[1], lengths[2]}, {angles[0], angles[1], angles[2]});

    chemfiles::Frame chflFrame(chflCell);
    size_t natoms = frame.get_natoms();
    
    chflFrame.set_step(frame.get_timestep());
    chflFrame.resize(natoms);
    std::vector<Atom> atoms = frame.get_atoms();
    for (size_t i = 0; i < natoms; i++)
    {
        chemfiles::Atom chflAtom(atoms[i].get_name());
        chflFrame.add_atom(chflAtom, to_chemfiles(atoms[i].get<Vec3<double>>(_mp_position)));
    }

    size_t nbonds = frame.get_nbonds();
    auto bonds = frame.get_bonds();
    for (size_t b = 0; b < nbonds; b++)
    {
        chflFrame.add_bond(bonds[b][0], bonds[b][1]);
    }

    _chflTraj.write(chflFrame);
}

void DataWriter::write_traj(Trajectory &traj)
{
    for (auto frame : traj.get_frames())
    {
        write_frame(frame);
    }

}

} // namespace molcpp