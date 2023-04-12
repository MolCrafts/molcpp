#include "atom.h"
#include "bond.h"

namespace molcpp
{

    Bond::Bond(AtomPtr itom, AtomPtr jtom) : _itom{itom}, _jtom{jtom} {}

    AtomPtr Bond::get_itom() const
    {
        return _itom.lock();
    }

    AtomPtr Bond::get_jtom() const
    {
        return _jtom.lock();
    }

    bool Bond::operator==(const Bond &other) const
    {
        auto itom = get_itom();
        auto jtom = get_jtom();
        auto other_itom = other.get_itom();
        auto other_jtom = other.get_jtom();
        return (itom == other_itom && jtom == other_jtom) ||
               (itom == other_jtom && jtom == other_itom);

    }

    BondProperty &Bond::operator[](const std::string &key)
    {
        return _properties.has(key) ? _properties[key] : (*_type)[key];
    }

    // factory function
    BondPtr create_bond(AtomPtr itom, AtomPtr jtom)
    {
        return std::make_shared<Bond>(itom, jtom);
    }

}