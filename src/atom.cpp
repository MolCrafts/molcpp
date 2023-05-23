#include "atom.h"

namespace molcpp
{
    Atom::Atom(const std::string& name, Vector3D pos) : _type{new_atomtype(name)}, _properties{}, _id{reinterpret_cast<size_t>(this)}, _pos{pos}
    {
    }

    Atom::Atom(const Atom& other) : _type{other._type}, _properties{other._properties}, _id{reinterpret_cast<size_t>(this)}, _pos{other._pos}
    {
    }

    Atom::Atom(Atom&& other) : _type{std::move(other._type)}, _properties{std::move(other._properties)}, _id{other._id}, _pos{std::move(other._pos)}
    {
    }

    void Atom::set_type(const AtomTypePtr &type)
    {
        _type = type;
    }

    const AtomTypePtr &Atom::get_type()
    {
        return _type;
    }

    void Atom::set(const std::string &key, const AtomProperty &value)
    {
        _properties.set(key, value);
    }

    bool Atom::has(const std::string &key)
    {
        return _properties.has(key);
    }

    bool Atom::equal_to(const Atom &other) const
    {
        return get_id() == other.get_id();
    }

    bool Atom::operator==(const Atom &other) const
    {
        return equal_to(other);
    }

    const size_t Atom::get_id() const
    {
        return _id;
    }

    void Atom::set_position(const Vector3D  &pos)
    {
        _pos = pos;
    }

    const Vector3D & Atom::get_position() const
    {
        return _pos;
    }

    Atom from_chemfiles(const chemfiles::Atom& chflAtom)
    {

        auto atom = Atom();
        atom.set("name", chflAtom.name());
        atom.set("type", chflAtom.type());
        atom.set("mass", chflAtom.mass());
        atom.set("charge", chflAtom.charge());
        if (chflAtom.properties())
        {
            for (auto prop : *chflAtom.properties())
            {
                if (prop.second.kind() == chemfiles::Property::Kind::BOOL)
                atom.set(prop.first, prop.second.as_bool());
                else if (prop.second.kind() == chemfiles::Property::Kind::DOUBLE)
                atom.set(prop.first, prop.second.as_double());
                else if (prop.second.kind() == chemfiles::Property::Kind::STRING)
                atom.set(prop.first, prop.second.as_string());
                // else if (prop.second.kind() == chemfiles::Property::Kind::VECTOR3D)
                // atom.set(prop.first, prop.second.as_vector3d());
                else throw std::runtime_error("Unsupported property type");
            }
        }
        
        return atom;

    }

    chemfiles::Atom to_chemfiles(const Atom &atom)
    {
        chemfiles::Atom chflAtom(atom.get<std::string>("name", ""));
        chflAtom.set_charge(atom.get<double>("charge", 0.0));
        chflAtom.set_mass(atom.get<double>("mass", 0.0));
        chflAtom.set_type(atom.get<std::string>("type", ""));

        return chflAtom;
    }

}