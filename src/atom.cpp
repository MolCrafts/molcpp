#include "atom.h"

namespace molcpp
{
    Atom::Atom(const std::string& name, Vector3D pos) : _type{nullptr}, _properties{}, _id{reinterpret_cast<size_t>(this)}
    {
        _properties["name"] = name;
        _properties["pos"] = pos;
    }

    Atom::Atom(const Atom& other) : _type{other._type}, _properties{other._properties}, _id{reinterpret_cast<size_t>(this)}
    {
    }

    Atom::Atom(Atom&& other) noexcept : _type{std::move(other._type)}, _properties{std::move(other._properties)}, _id{other._id}
    {
    }

    Atom::~Atom()
    {

    }

    void Atom::set_type(AtomType* type)
    {
        _type = type;
    }

    AtomType* Atom::get_type()
    {
        if (_type == nullptr)
        {
            throw AttributeError("Atom::get_type: atom type not set");
        }
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

    bool Atom::equal_to(Atom* rhs)
    {
        return get_id() == rhs->get_id();
    }

    bool Atom::equal_to(const Atom& rhs)
    {
        return get_id() == rhs.get_id();
    }

    bool Atom::operator==(Atom* rhs)
    {
        return equal_to(rhs);
    }

    bool Atom::operator==(const Atom& rhs)
    {
        return equal_to(rhs);
    }

    size_t Atom::get_id() const
    {
        return _id;
    }

    Atom& Atom::operator=(const Atom& rhs)
    {
        if (this != &rhs){
            _type = rhs._type;
            _properties = rhs._properties;
            _id = rhs._id;
        }
        return *this;
    }

    Atom& Atom::operator=(Atom&& rhs) noexcept
    {
        if (this != &rhs){
            _type = std::move(rhs._type);
            _properties = std::move(rhs._properties);
            _id = rhs._id;
        }
        return *this;
    }

    std::unique_ptr<Atom> from_chemfiles(const chemfiles::Atom& chflAtom)
    {

        auto atom = std::make_unique<Atom>();
        atom->set("name", chflAtom.name());
        atom->set("type", chflAtom.type());
        atom->set("mass", chflAtom.mass());
        atom->set("charge", chflAtom.charge());
        if (chflAtom.properties())
        {
            for (auto prop : *chflAtom.properties())
            {
                if (prop.second.kind() == chemfiles::Property::Kind::BOOL)
                atom->set(prop.first, prop.second.as_bool());
                else if (prop.second.kind() == chemfiles::Property::Kind::DOUBLE)
                atom->set(prop.first, prop.second.as_double());
                else if (prop.second.kind() == chemfiles::Property::Kind::STRING)
                atom->set(prop.first, prop.second.as_string());
                // else if (prop.second.kind() == chemfiles::Property::Kind::VECTOR3D)
                // atom.set(prop.first, prop.second.as_vector3d());
                else throw std::runtime_error("Unsupported property type");
            }
        }
        return atom;
    }

    chemfiles::Atom to_chemfiles(Atom* atom)
    {
        chemfiles::Atom chflAtom(atom->get<std::string>("name", ""));
        chflAtom.set_charge(atom->get<double>("charge", 0.0));
        chflAtom.set_mass(atom->get<double>("mass", 0.0));
        chflAtom.set_type(atom->get<std::string>("type", ""));

        return chflAtom;
    }

    std::unique_ptr<Atom> create_atom(const std::string& name, Vector3D pos)
    {
        return std::make_unique<Atom>(name, pos);
    }

}