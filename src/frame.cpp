#include "frame.h"

namespace molcpp
{
    Frame::Frame() : _timestep(0), _cell(new_cell()) , _topology(new_topology())
    {

    }

    size_t Frame::get_natoms() const
    {
        return _topology->get_natoms();
    }

    size_t Frame::get_nbonds() const
    {
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

    const TopologyPtr& Frame::get_topology() const
    {
        return _topology;
    }

    void Frame::set_topology(const TopologyPtr& topology)
    {
        _topology = topology;
    }

    void Frame::set(const std::string& key, const xt::xarray<AtomProperty> &value)
    {
        _topology->set(key, value);
    }

    void Frame::set_positions(const xt::xarray<double>& positions)
    {
        _topology->set_positions(positions);
    }

    const xt::xarray<double> Frame::get_positions() const
    {
        xt::xarray<double> tmp = _topology->get_positions();
        return tmp;
    }

    void Frame::set_cell(CellPtr cell)
    {
        _cell = cell;
    }

    void Frame::set_cell(Vector3D lengths, Vector3D angles)
    {
        _cell = new_cell(lengths, angles);
    }

    CellPtr Frame::get_cell() const
    {
        return _cell;
    }

    FramePtr new_frame()
    {
        return std::make_shared<Frame>();
    }

    FramePtr new_frame(const chemfiles::Frame& chflFrame)
    {
        auto _frame = new_frame();
        _frame->set_timestep(chflFrame.step());
        _frame->set_cell(new_cell(chflFrame.cell()));
        _frame->set_topology(new_topology(chflFrame.topology()));
        int natoms = chflFrame.size();
        auto positions = xt::adapt((double*)chflFrame.positions().data(), {natoms, 3});
        _frame->set_positions(positions);
        return _frame;
    }

    chemfiles::Frame to_chemfiles(const FramePtr& frame)
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