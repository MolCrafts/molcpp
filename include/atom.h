#ifndef ATOM_H
#define ATOM_H

#include <chemfiles.hpp>
#include "graph.h"
#include "bond.h"
#include "element.h"
#include <string>
#include <optional>

namespace MolCpp
{

    class Atom : public Node
    {
    public:
        Atom(const chemfiles::Atom &);
        Atom(const Element &);
        Atom() = default;

        Element get_element() const { return _element; }

        size_t get_implicit_hcount();
        void set_implicit_hcount();

    private:
        Element _element;
        std::string _name;
        std::string _type;
        double _mass;
        double _charge;
        size_t _implicit_hcount;
    };

    using AtomPtr = std::shared_ptr<Atom>;
}

#endif // ATOM_H