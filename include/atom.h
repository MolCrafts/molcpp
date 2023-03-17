#ifndef ATOM_H
#define ATOM_H

#include <chemfiles.hpp>
#include "graph.h"
// #include "bond.h"
#include "element.h"
#include <string>
#include <optional>

namespace MolCpp
{

    //ATOM Property Macros (flags)
    //! Atom is in a 4-membered ring
    const int RING4_ATOM     = 1<<1;
    //! Atom is in a 3-membered ring
    const int RING3_ATOM     = 1<<2;
    //! Atom is aromatic
    const int AROMATIC_ATOM  = 1<<3;
    //! Atom is in a ring
    const int RING_ATOM      = 1<<4;
    //! Atom is an electron donor
    const int DONOR_ATOM     = 1<<7;
    //! Atom is an electron acceptor
    const int ACCEPTOR_ATOM  = 1<<8;

    class Bond;
    class Atom : public Node
    {
    public:
        Atom(const chemfiles::Atom &);
        Atom(const Element &);
        Atom() = default;

        Element get_element() const { return _element; }

        size_t get_implicit_hcount();
        void set_implicit_hcount(size_t);
        void set_local_idx(size_t idx) { _local_idx = idx; }
        //! \return Is the atom aromatic?
        bool IsAromatic()      const;

    private:
        Element _element;
        std::string _name;
        std::string _type;
        double _mass;
        double _charge;
        size_t _implicit_hcount;
        // std::vector<BondPtr> _bonds;
        size_t _local_idx;

    };

    using AtomPtr = std::shared_ptr<Atom>;
}

#endif // ATOM_H