#include "bond.h"

namespace molcpp
{

    Bond::Bond(Atom* itom, Atom* jtom) : _itom{itom}, _jtom{jtom} , _type{nullptr}
    {

    }

    Bond::Bond(const Bond& other) : _itom{other._itom}, _jtom{other._jtom}, _type{other._type}, _properties{other._properties}
    {

    }

    Bond::Bond(Bond&& other) noexcept : _itom{other._itom}, _jtom{other._jtom}, _type{std::move(other._type)}, _properties{std::move(other._properties)}
    {

    }

    Bond::~Bond()
    {
        // Bond doesn't need to delete _itom and _jtom
        // It must be delete from atom container
    }

    Atom* Bond::get_itom()
    {
        return _itom;
    }

    Atom* Bond::get_jtom()
    {
        return _jtom;
    }

    BondType* Bond::get_type() const
    {
        return _type;
    }

    void Bond::set_type(BondType* type)
    {
        _type = type;
    }

    bool Bond::equal_to(Bond* rhs)
    {
        Atom* itom = get_itom();
        Atom* jtom = get_jtom();
        Atom* rhs_itom = rhs->get_itom();
        Atom* rhs_jtom = rhs->get_jtom();
        return (itom->equal_to(rhs_itom) && jtom->equal_to(rhs_jtom)) || (itom->equal_to(rhs_jtom) && jtom->equal_to(rhs_itom));
    }

    bool Bond::operator==(Bond* rhs)
    {
        return equal_to(rhs);
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

    std::unique_ptr<Bond> create_bond(Atom* itom, Atom* jtom)
    {
        return std::make_unique<Bond>(itom, jtom);
    }

}