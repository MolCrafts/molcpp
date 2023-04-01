#include "atom.h"
#include "bond.h"

namespace molcpp
{

    Atom::Atom() {}

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
        auto results = std::find_if(_bonds.begin(), _bonds.end(), [bond](BondPtr b) {
            return *b == *bond;
        });
        return results == _bonds.end() ? false : true;
    }

    bool Atom::is_nbr(AtomPtr atom)
    {
        auto nbrs = this->get_nbrs();
        auto isInNbrs = find_in_container<std::vector<AtomPtr>, AtomPtr>(nbrs, atom).has_value();
        return isInNbrs;
    }

    bool Atom::del_bond(BondPtr bond)
    {
        auto result = find_in_container<std::vector<BondPtr>, BondPtr>(_bonds, bond);
        if (result.has_value())
        {
            _bonds.erase(_bonds.begin() + result.value());
            return true;
        }
        else
        {
            return false;
        }
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

    AtomPtr create_atom()
    {
        return std::make_shared<Atom>();
    }

}