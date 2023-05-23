#include "bond.h"

namespace molcpp
{

    Bond::Bond(Atom& itom, Atom& jtom) : _itom{itom}, _jtom{jtom} 
    {

    }

    Bond::Bond(const Bond& other) : _itom{other._itom}, _jtom{other._jtom}, _type{other._type}, _properties{other._properties}
    {

    }

    Bond::Bond(Bond&& other) : _itom{other._itom}, _jtom{other._jtom}, _type{std::move(other._type)}, _properties{std::move(other._properties)}
    {

    }

    Atom& Bond::get_itom() const
    {
        return _itom;
    }

    Atom& Bond::get_jtom() const
    {
        return _jtom;
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

    Bond& Bond::operator=(Bond&& other)
    {
        return other;
    }

}