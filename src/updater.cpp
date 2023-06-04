#include "updater.h"

namespace molcpp
{

    Updater::Updater(System* system, Minimizer* minimizer)
    {
        _current_system = system;
        _minimizer = minimizer;
    }

    Updater::~Updater()
    {
        delete _current_system;
        delete _minimizer;
    }

    Frame* update(Frame* frame)
    {

        nblist = frame->update_nblist();
        bonds = frame->get_topology()->get_bonds();

        EnergyAndForce pairef = _current_system->get_forcefield()->compute_pair(nblist);
        EnergyAndForce bondef = _current_system->get_forcefield()->compute_bond(frame->get_topology()->get_bonds());
        // get positions of atoms
        std::vector<:Vector3D> positions = frame->get_positions();
        std::vector<:Vector3D> forces(atoms.size());
        for (size_t i = 0; i < atoms.size(); i++)
        {
            forces[i] = pairef.forces[i] + bondef.forces[i];
        }
        double etol = 1e-5;

        _minimizer->minimize(positions, forces);
    }

}