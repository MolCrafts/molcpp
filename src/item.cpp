#include "item.h"
#include <memory>

namespace molcpp {

    Atom::Atom() : Item() {};

    std::unique_ptr<Item> Atom::clone() const {
        return std::make_unique<Atom>(*this);
    }

}