#include "topology.h"

namespace MolCpp
{

    Topology::Topology(const chemfiles::Topology& chflTopology) : Graph {}
    {
        // copy atoms
        for (size_t i = 0; i < chflTopology.size(); i++)
        {
            this.new_atom(chflTopology[i]);
        }

        // copy bonds
        for (size_t i = 0; i < chflTopology.bonds().size(); i++)
        {

            auto _chflBond = chflTopology.bonds()[i];
            this->new_bond(_chflBond[0], _chflBond[1]);
        }

        // register subgraph


    }

    AtomPtr Topology::new_atom()
    {
        AtomPtr atom = std::make_shared<Atom>();
        _atoms.push_back(atom);
        add_node(atom);
        return atom;
    }

    AtomPtr Topology::new_atom(const chemfiles::Atom &chflAtom)
    {
        AtomPtr atom = std::make_shared<Atom>(chflAtom);
        _atoms.push_back(atom);
        add_node(atom);
        return atom;
    }

}