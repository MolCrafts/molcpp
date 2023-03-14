#ifndef MOLECULE_H
#define MOLECULE_H

#include "topology.h"
#include "parsmart.h"
#include "atom.h"
#include "bond.h"
#include "utils.h"
#include "mplog.h"
#include <utility>

namespace MolCpp
{

    enum HydrogenType { AllHydrogen, PolarHydrogen, NonPolarHydrogen };

    // Class OBMol
    // MOL Property Macros (flags) -- 32+ bits
    //! Smallest Set of Smallest Rings (SSSR) done. See OBRing and OBMol::FindSSSR
    const int SSSR_MOL = 1 << 1;
    //! Ring flags have been set: See OBRing::FindRingAtomsAndBonds
    const int RINGFLAGS_MOL = 1 << 2;
    //! Aromatic flags have been set for atoms and bonds
    const int AROMATIC_MOL = 1 << 3;
    //! Atom typing has been performed. See OBAtomTyper
    const int ATOMTYPES_MOL = 1 << 4;
    //! Chirality detection has been performed.
    const int CHIRALITY_MOL = 1 << 5;
    //! Partial charges have been set or percieved
    const int PCHARGE_MOL = 1 << 6;
    //! Atom hybridizations have been set. See OBAtomTyper
    const int HYBRID_MOL = 1 << 8;
    //! Ring "closure" bonds have been set. See OBBond::IsClosure
    const int CLOSURE_MOL = 1 << 11;
    //! Hyrdogen atoms have been added where needed. See OBMol::AddHydrogens
    const int H_ADDED_MOL = 1 << 12;
    //! pH correction for hydrogen addition has been performed.
    const int PH_CORRECTED_MOL = 1 << 13;
    //! Biomolecular chains and residues have been set. See OBChainsParser
    const int CHAINS_MOL = 1 << 15;
    //! Total charge on this molecule has been set. See OBMol::SetTotalCharge
    const int TCHARGE_MOL = 1 << 16;
    //! Total spin on this molecule has been set. See OBMol::SetTotalSpinMultiplicity
    const int TSPIN_MOL = 1 << 17;
    //! Ring typing has been performed. See OBRingTyper
    const int RINGTYPES_MOL = 1 << 18;
    //! A pattern, not a complete molecule.
    const int PATTERN_STRUCTURE = 1 << 19;
    //! Largest Set of Smallest Rings = LSSR; done. See OBRing and OBMol::FindLSSR
    const int LSSR_MOL = 1 << 20;
    //! SpinMultiplicities on atoms have been set in OBMol::AssignSpinMultiplicity= ;
    const int ATOMSPIN_MOL = 1 << 21;
    //! Treat as reaction
    const int REACTION_MOL = 1 << 22;
    //! Molecule is repeating in a periodic unit cell
    const int PERIODIC_MOL = 1 << 23;
    // flags 24-32 unspecified

    class Molecule : public Topology
    {

    public:
        Molecule();
        Molecule(const Pattern *);

        bool add_new_hydrogens(HydrogenType whichHydrogen, bool correctForPh, double pH=7.4);

        bool is_corrected_for_ph() { return has_flag(_flags, PH_CORRECTED_MOL); }
        bool has_hydrogens_added() { return has_flag(_flags, H_ADDED_MOL); }
        bool has_chirality_perceived() { return has_flag(_flags, CHIRALITY_MOL); }
        bool is_empty() { return _atoms.empty() && _subgraphs.empty(); }
        void set_hydrogens_added() { switch_flag(_flags, H_ADDED_MOL); }
        void set_chirality_perceived() { switch_flag(_flags, CHIRALITY_MOL); }

    private:
        int _flags;
        std::vector<double*> _conformers;


    };



}

#endif