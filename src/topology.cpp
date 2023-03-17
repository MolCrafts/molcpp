#include "topology.h"

namespace MolCpp
{

    Topology::Topology(const chemfiles::Topology& chflTopology) : Graph {}
    {
        // copy atoms
        for (size_t i = 0; i < chflTopology.size(); i++)
        {
            this->new_atom(chflTopology[i]);
        }

        // copy bonds
        for (size_t i = 0; i < chflTopology.bonds().size(); i++)
        {

            auto _chflBond = chflTopology.bonds()[i];
            this->new_bond(_chflBond[0], _chflBond[1]);
        }

        // register subgraph


    }

    bool Topology::add_atom(AtomPtr atom)
    {
        atom->set_local_idx(_atoms.size());
        _atoms.push_back(atom);
        add_node(atom);
        return true;
    }

    AtomPtr Topology::new_atom()
    {
        AtomPtr atom = std::make_shared<Atom>();
        this->add_atom(atom);
        return atom;
    }

    AtomPtr Topology::new_atom(const chemfiles::Atom &chflAtom)
    {
        AtomPtr atom = std::make_shared<Atom>(chflAtom);
        _atoms.push_back(atom);
        add_node(atom);
        return atom;
    }

    bool Topology::add_bond(BondPtr bond)
    {
        // bond->set_local_idx(_bonds.size());
        _bonds.push_back(bond);
        add_edge(bond);
        return true;
    }

    BondPtr Topology::new_bond(AtomPtr bgn, AtomPtr end)
    {
        BondPtr bond = std::make_shared<Bond>(bgn, end);
        this->add_bond(bond);
        return bond;
    }

    BondPtr Topology::new_bond(size_t bgn_idx, size_t end_idx)
    {
        auto bgn = _atoms.at(bgn_idx);
        auto end = _atoms.at(end_idx);
        return this->new_bond(bgn, end);
    }

}