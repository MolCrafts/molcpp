#include "cgmodel.h"

namespace molcpp
{

    namespace cg
    {

        bool Atom::add_bond(BondPtr bond)
        {
            return add_edge(bond);
        }

        bool Atom::has_bond(BondPtr bond)
        {
            return has_edge(bond);
        }

        bool Atom::del_bond(BondPtr bond)
        {
            return del_edge(bond);
        }

        AtomVec Atom::get_neighbors()
        {
            AtomVec _nbrs;
            for (const auto edge : _edges)
            {
                if (edge->get_bgn().get() == this)
                {
                    _nbrs.push_back(edge->get_end());
                }
                else if (edge->get_end().get() == this)
                {
                    _nbrs.push_back(edge->get_bgn());
                }
            }
            return _nbrs;
        }

    }

}