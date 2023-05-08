#include "atom.h"
#include "bond.h"

namespace molcpp
{

    Bond::Bond(AtomPtr itom, AtomPtr jtom) : _itom{itom}, _jtom{jtom} 
    {

    }

    AtomPtr Bond::get_itom() const
    {
        return _itom.lock();
    }

    AtomPtr Bond::get_jtom() const
    {
        return _jtom.lock();
    }

    BondTypePtr Bond::get_bondtype() const
    {
        return _type;
    }

    void Bond::set_type(const BondTypePtr &type)
    {
        _type = type;
    }

    bool Bond::equal_to(const Bond& other) const
    {
        auto itom = get_itom();
        auto jtom = get_jtom();
        auto other_itom = other.get_itom();
        auto other_jtom = other.get_jtom();
        return (itom == other_itom && jtom == other_jtom) ||
               (itom == other_jtom && jtom == other_itom);
    }

    bool Bond::equal_to(const BondPtr& other) const
    {
        auto itom = get_itom();
        auto jtom = get_jtom();
        auto other_itom = other->get_itom();
        auto other_jtom = other->get_jtom();
        return (itom == other_itom && jtom == other_jtom) ||
               (itom == other_jtom && jtom == other_itom);
    }

    bool Bond::operator==(const Bond &other) const
    {
        return equal_to(other);
    }

    BondProperty &Bond::operator[](const std::string &key)
    {
        return _properties.has(key) ? _properties[key] : (*_type)[key];
    }

    void Bond::set(const std::string &key, const BondProperty &value)
    {
        _properties.set(key, value);
    }

    // factory function
    BondPtr create_bond(AtomPtr itom, AtomPtr jtom)
    {
        return std::make_shared<Bond>(itom, jtom);
    }

}