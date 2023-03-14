#include "atom.h"

namespace MolCpp
{

    Atom::Atom(const chemfiles::Atom &chflAtom) : Node{},
                                                  _element(Element::get_element(chflAtom.atomic_number().value_or(0))),
                                                  _name(chflAtom.name()),
                                                  _type(chflAtom.type()),
                                                  _mass(chflAtom.mass()),
                                                  _charge(chflAtom.charge()),
                                                  _implicit_hcount(0)
    {
    }

    Atom::Atom(const Element &element) : Node{},
                                         _element{element}, 
                                         _name{element.get_name()}, 
                                         _type{element.get_symbol()}, 
                                         _mass{element.get_mass()}, 
                                         _charge{0.0}, 
                                         _implicit_hcount{0}
    {
        
    }

}