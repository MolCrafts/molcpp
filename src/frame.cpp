#include "frame.h"

namespace molcpp
{
    Frame::Frame() : _timestep(0), _topology(new_topology())
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
        return _topology->get_positions();
    }

    void Frame::set_cell(Cell cell)
    {
        _cell = cell;
    }

    void Frame::set_cell(Vector3D lengths, Vector3D tilts)
    {
        _cell = Cell(lengths, tilts);
    }

    Cell Frame::get_cell() const
    {
        return _cell;
    }

    FramePtr new_frame()
    {
        return std::make_shared<Frame>();
    }

    FramePtr new_frame(const chemfiles::Frame& cfhlFrame)
    {
        auto _frame = new_frame();
        _frame->set_timestep(cfhlFrame.step());
        // _frame->set_cell(new_cell(cfhlFrame.cell());
        _frame->set_topology(new_topology(cfhlFrame.topology()));
        return _frame;
    }

    chemfiles::Frame to_chemfiles(const FramePtr& frame)
    {
        chemfiles::Frame cfhlFrame;
        cfhlFrame.set_step(frame->get_timestep());
        cfhlFrame.set_cell(to_chemfiles(frame->get_cell()));
        cfhlFrame.set_topology(to_chemfiles(frame->get_topology()));
        return cfhlFrame;
    }
}