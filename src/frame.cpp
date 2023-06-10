#include "frame.h"

namespace molcpp
{
    Frame::Frame() : _timestep(0), _cell(new Cell()) , _topology(new Topology())
    {

    }

    size_t Frame::get_natoms() const
    {
        if (_topology == nullptr)
            return 0;
        return _topology->get_natoms();
    }

    size_t Frame::get_nbonds() const
    {
        if (_topology == nullptr)
            return 0;
        return _topology->get_nbonds();
    }

    size_t Frame::get_timestep() const
    {
        return _timestep;
    }

    void Frame::set_timestep(size_t timestep)
    {
        _timestep = timestep;
    }

    Topology* Frame::get_topology() const
    {
        return _topology;
    }

    void Frame::set_topology(Topology* topology)
    {
        _topology = topology;
    }

    void Frame::set(const std::string& key, const std::vector<AtomProperty> &value)
    {
        if (_topology == nullptr)
            throw std::runtime_error("Topology is not set");
        _topology->set(key, value);
    }

    void Frame::set_cell(Cell* cell)
    {
        _cell = cell;
    }

    void Frame::set_cell(Vector3D lengths, Vector3D angles)
    {
        _cell = new Cell(lengths, angles);
    }

    Cell* Frame::get_cell() const
    {
        return _cell;
    }

    std::unique_ptr<Frame> create_frame()
    {
        return std::make_unique<Frame>();
    }

    std::unique_ptr<Frame> from_chemfiles(const chemfiles::Frame& chflFrame)
    {
        auto _frame = create_frame();
        _frame->set_timestep(chflFrame.step());
        _frame->set_cell(from_chemfiles(chflFrame.cell()).release());
        _frame->set_topology(from_chemfiles(chflFrame.topology()).release());
        std::vector<AtomProperty> positions(chflFrame.size());
        std::transform(
            chflFrame.positions().begin(),
            chflFrame.positions().end(),
            positions.begin(),
            [](const chemfiles::Vector3D& pos) {
                return AtomProperty(Vector3D(pos[0], pos[1], pos[2]));
            }
        );
        // NOTE: molcpp::frame.set will assign property to each
        //       atom, so we should use singular rather than plural
        _frame->set("position", positions);
        return _frame;
    }

    chemfiles::Frame to_chemfiles(Frame* frame)
    {
        chemfiles::Frame chflFrame;
        auto chflTopo = to_chemfiles(frame->get_topology());
        chflFrame.set_step(frame->get_timestep());
        chflFrame.set_cell(to_chemfiles(frame->get_cell()));
        std::vector<Vector3D> xyz = frame->get<Vector3D>("position");
        for (size_t i = 0; i < chflTopo.size(); i++)  // for_each atom
        {   
            auto chflAtom = chflTopo[i];
            chflFrame.add_atom(chflAtom, chemfiles::Vector3D(xyz[i][0], xyz[i][1], xyz[i][2]));
        }
        chflFrame.set_topology(chflTopo);
        return chflFrame;
    }
}