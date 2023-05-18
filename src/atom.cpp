#include "atom.h"
#include "bond.h"

namespace molcpp
{
    Atom::Atom(const std::string& name, xt::xarray<double>pos) : _type{new_atomtype(name)}, _properties{}, _bonds{}, _pos{pos}
    {
    }

    bool Atom::add_bond(BondPtr bond)
    {
        if (has_bond(bond))
        {
            return false;
        }
        else
        {
            _bonds.push_back(bond);
            return true;
        }
    }

    bool Atom::has_bond(BondPtr bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b)
                                    { return *b == *bond; });
        return results == _bonds.end() ? false : true;
    }

    bool Atom::del_bond(BondPtr bond)
    {
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b)
                                    { return *b == *bond; });
        if (results == _bonds.end())
        {
            return false;
        }
        else
        {
            _bonds.erase(results);
            return true;
        }
    }

    bool Atom::is_nbr(AtomPtr atom)
    {
        auto nbrs = this->get_nbrs();
        auto results = std::find_if(nbrs.begin(), nbrs.end(), [atom](AtomPtr a)
                                    { return *a == *atom; });
        return results == nbrs.end() ? false : true;
    }

    std::vector<AtomPtr> Atom::get_nbrs()
    {
        std::vector<AtomPtr> nbrs;
        for (auto bond : _bonds)
        {
            auto itom = bond->get_itom();
            auto jtom = bond->get_jtom();
            if (itom.get() == this)
            {
                nbrs.push_back(jtom);
            }
            else
            {
                nbrs.push_back(itom);
            }
        }
        return nbrs;
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

    bool Atom::equal_to(const AtomPtr &other) const
    {
        return get_id() == other->get_id();
    }

    bool Atom::operator==(const Atom &other) const
    {
        return equal_to(other);
    }

    const size_t Atom::get_id() const
    {
        return _id;
    }

    void Atom::set_position(const xt::xarray<double> &pos)
    {
        _pos = pos;
    }

    const xt::xarray<double>& Atom::get_position() const
    {
        return _pos;
    }

    AtomPtr new_atom(const std::string& name)
    {
        return std::make_shared<Atom>(name);
    }

    AtomPtr new_atom(const AtomTypePtr &type)
    {
        auto atom = new_atom();
        atom->set_type(type);
        return atom;
    }

    AtomPtr new_atom(const chemfiles::Atom& chflAtom)
    {

        auto atom = new_atom();
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
                // atom->set(prop.first, prop.second.as_vector3d());
                else throw std::runtime_error("Unsupported property type");
            }
        }
        
        return atom;

    }

    // to_chemfiles
    chemfiles::Atom to_chemfiles(const AtomPtr &atom)
    {
        chemfiles::Atom chflAtom(atom->get<std::string>("name", ""));
        chflAtom.set_charge(atom->get<double>("charge", 0.0));
        chflAtom.set_mass(atom->get<double>("mass", 0.0));
        chflAtom.set_type(atom->get<std::string>("type", ""));

        return chflAtom;
    }

}