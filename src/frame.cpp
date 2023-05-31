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

    void Frame::set(const std::string& key, const xt::xarray<AtomProperty> &value)
    {
        if (_topology == nullptr)
            throw std::runtime_error("Topology is not set");
        _topology->set(key, value);
    }

    void Frame::set_positions(const xt::xarray<double>& positions)
    {
        if (_topology == nullptr)
            throw std::runtime_error("Topology is not set");
        _topology->set_positions(positions);
    }

    const xt::xarray<double> Frame::get_positions() const
    {
        xt::xarray<double> tmp = _topology->get_positions();
        return tmp;
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
        int natoms = chflFrame.size();
        auto positions = xt::adapt((double*)chflFrame.positions().data(), {natoms, 3});
        // _frame->set_positions(positions);
        return _frame;
    }

    chemfiles::Frame to_chemfiles(Frame* frame)
    {
        chemfiles::Frame chflFrame;
        auto chflTopo = to_chemfiles(frame->get_topology());
        chflFrame.set_step(frame->get_timestep());
        chflFrame.set_cell(to_chemfiles(frame->get_cell()));
        for (size_t i = 0; i < chflTopo.size(); i++)
        {   
            auto chflAtom = chflTopo[i];
            xt::xarray<double> xyz = frame->get_positions()(i);
            chflFrame.add_atom(chflAtom, {xyz[0], xyz[1], xyz[2]});
        }
        chflFrame.set_topology(chflTopo);
        return chflFrame;
    }
}