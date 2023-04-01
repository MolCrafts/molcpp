#include "molecule.h"

namespace molcpp
{

    Molecule::Molecule(): Topology{}, _flags{0}
    {
        // ctor
    }

    size_t Molecule::get_natoms() const
    {
        return _nodes.size();
    }

    // bool Molecule::add_new_hydrogens(HydrogenType whichHydrogen, bool correctForPH, double pH)
    // {
    //     if (!is_corrected_for_ph() && correctForPH)
    //         // CorrectForPH(pH);

    //     if (has_hydrogens_added())
    //         return (true);

    //     bool hasChiralityPerceived = this->has_hydrogens_added(); // remember

    //     /*
    //     //
    //     // This was causing bug #1892844 in avogadro. We also want to add hydrogens if the molecule has no bonds.
    //     //
    //     if(NumBonds()==0 && NumAtoms()!=1)
    //     {
    //     obErrorLog.ThrowError(__FUNCTION__,
    //     "Did not run OpenBabel::AddHydrogens on molecule with no bonds", obAuditMsg);
    //     return true;
    //     }
    //     */
    //     if (whichHydrogen == AllHydrogen)
    //         LOG_INFO("Adding hydrogens to molecule");
    //     else if (whichHydrogen == PolarHydrogen)
    //         LOG_INFO("Adding polar hydrogens to molecule");
    //     else
    //         LOG_INFO("Adding non-polar hydrogens to molecule");

    //     // TODO: depends how to store comformer
    //     // Make sure we have conformers (PR#1665519)
    //     // if (!_conformers.empty() && !is_empty())
    //     // {
    //     //     for (auto atom : get_atoms())
    //     //     {
    //     //         if (atom->get_vector().size() == 0)
    //     //         {
    //     //             atom->set_vector(_conformers[0][atom->get_index()]);
    //     //         }
    //     //     }
    //     // }

    //     set_hydrogens_added(); // This must come after EndModify() as EndModify() wipes the flags
    //     // If chirality was already perceived, remember this (to avoid wiping information
    //     if (hasChiralityPerceived)
    //         this->set_chirality_perceived();

    //     // count up number of hydrogens to add
    //     AtomPtr atom, h;
    //     int hcount, count = 0;
    //     std::vector<std::pair<AtomPtr, int>> vhadd;
    //     for (auto atom : get_atoms())
    //     {
    //         if (whichHydrogen == PolarHydrogen && !atom->get_element().is_NOSP())
    //             continue;
    //         if (whichHydrogen == NonPolarHydrogen && atom->get_element().is_NOSP())
    //             continue;

    //         hcount = atom->get_implicit_hcount();
    //         atom->set_implicit_hcount(0);

    //         if (hcount)
    //         {
    //             vhadd.push_back(std::pair<AtomPtr, int>(atom, hcount));
    //             count += hcount;
    //         }
    //     }

    //     if (count == 0)
    //     {
    //         // Make sure to clear SSSR and aromatic flags we may have tripped above
    //         _flags &= (~(SSSR_MOL | AROMATIC_MOL));
    //         return (true);
    //     }

    //     // TODO: add the hydrogens
    //     // 

    //     // reset atom type and partial charge flags
    //     _flags &= (~(PCHARGE_MOL | ATOMTYPES_MOL | SSSR_MOL | AROMATIC_MOL | HYBRID_MOL));

    //     return (true);
    // }

}