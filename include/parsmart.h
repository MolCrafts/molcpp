#ifndef PARSMART_H
#define PARSMART_H

#include <string>
#include <vector>
#include <bitset>
#include <cstring>
#include "molecule.h"

using bitset = std::bitset<10>;

void SetBitsOn(bitset & bitset, const std::vector<int> & bit_offsets) {
  for (auto offset : bit_offsets) {
    bitset.set(offset, true);
  }
}

namespace MolCpp
{

    //! \union _AtomExpr parsmart.h <openbabel/parsmart.h>
    //! \brief An internal (SMARTS parser) atomic expression
    typedef union _AtomExpr
    {
        int type;
        struct
        {
            int type;
            int value;
        } leaf;
        struct
        {
            int type;
            void *recur;
        } recur;
        struct
        {
            int type;
            union _AtomExpr *arg;
        } mon; // unary
        struct
        {
            int type;
            union _AtomExpr *lft;
            union _AtomExpr *rgt;
        } bin; // binary
    } AtomExpr;

    //! \union _BondExpr parsmart.h <openbabel/parsmart.h>
    //! \brief An internal (SMARTS parser) bond expression
    typedef union _BondExpr
    {
        int type;
        struct
        {
            int type;
            union _BondExpr *arg;
        } mon; // unary
        struct
        {
            int type;
            union _BondExpr *lft;
            union _BondExpr *rgt;
        } bin; // binary
    } BondExpr;

    //! \struct BondSpec parsmart.h <openbabel/parsmart.h>
    //! \brief An internal (SMARTS parser) bond specification
    typedef struct
    {
        BondExpr *expr;
        int src, dst;
        int visit;
        bool grow;
    } BondSpec;

    //! \struct AtomSpec parsmart.h <openbabel/parsmart.h>
    //! \brief An internal (SMARTS parser) atom specification
    typedef struct
    {
        AtomExpr *expr;
        int visit;
        int part;
        int chiral_flag;
        int vb;
        std::vector<int> nbrs;
    } AtomSpec;

    //! \struct Pattern parsmart.h <openbabel/parsmart.h>
    //! \brief A SMARTS parser internal pattern
    typedef struct
    {
        int aalloc, acount;
        int balloc, bcount;
        bool ischiral;
        AtomSpec *atom; // array of atoms, len(atom) == acount
        BondSpec *bond;
        int parts;
        bool hasExplicitH;
    } Pattern;

    //! \struct ParseState parsmart.h <openbabel/parsmart.h>
    //! \brief A SMARTS parser internal state
    typedef struct
    {
        BondExpr *closord[100];
        int closure[100];
        int closindex;
    } ParseState;

    //! Internal class for extending SmartsPattern
    class SmartsPrivate;

    ///@addtogroup substructure Substructure Searching
    ///@{

    // class introduction in parsmart.cpp
    //! \brief SMARTS (SMiles ARbitrary Target Specification) substructure searching
    class SmartsPattern
    {
    protected:
        SmartsPrivate *_d;                    //!< Internal data storage for future expansion
        std::vector<std::vector<int>> _mlist; //!< The list of matches
        Pattern *_pat;                        //!< The parsed SMARTS pattern
        std::string _str;                     //!< The string of the SMARTS expression

        char *_buffer;
        char *LexPtr;
        char *MainPtr;

        Pattern *ParseSMARTSPattern(void);
        Pattern *ParseSMARTSPart(Pattern *, int);
        Pattern *SMARTSError(Pattern *pat);
        Pattern *ParseSMARTSError(Pattern *pat, BondExpr *expr);
        AtomExpr *ParseSimpleAtomPrimitive(void);
        AtomExpr *ParseComplexAtomPrimitive(void);
        AtomExpr *ParseAtomExpr(int level);
        BondExpr *ParseBondPrimitive(void);
        BondExpr *ParseBondExpr(int level);
        Pattern *ParseSMARTSString(char *ptr);
        Pattern *ParseSMARTSRecord(char *ptr);
        int GetVectorBinding();
        Pattern *SMARTSParser(Pattern *pat, ParseState *stat,
                              int prev, int part);

    public:
        SmartsPattern() : _pat(nullptr), _buffer(nullptr), LexPtr(nullptr), MainPtr(nullptr) {}
        virtual ~SmartsPattern();

        SmartsPattern(const SmartsPattern &cp) : _pat(nullptr), _buffer(nullptr), LexPtr(nullptr), MainPtr(nullptr)
        {
            *this = cp;
        }

        SmartsPattern &operator=(const SmartsPattern &cp)
        {
            if (this == &cp)
                return *this;

            if (_pat)
                delete[] _pat;
            if (_buffer)
                delete[] _buffer;
            _buffer = nullptr;
            _pat = nullptr;
            std::string s = cp._str;
            Init(s);
            return (*this);
        }

        //! \name Initialization Methods
        //@{
        //! Parse the @p pattern SMARTS string.
        //! \return Whether the pattern is a valid SMARTS expression
        bool Init(const char *pattern);
        //! Parse the @p pattern SMARTS string.
        //! \return Whether the pattern is a valid SMARTS expression
        bool Init(const std::string &pattern);
        //@}

        //! \name Pattern Properties
        //@{
        //! \return the SMARTS string which is currently used
        const std::string &GetSMARTS() const { return _str; }
        //! \return the SMARTS string which is currently used

        std::string &GetSMARTS()
        {
            return _str;
        }

        Pattern *GetPattern() const { return _pat; }

        //! \return If the SMARTS pattern is an empty expression (e.g., invalid)
        bool Empty() const { return (_pat == nullptr); }
        //! \return If the SMARTS pattern is a valid expression
        bool IsValid() const { return (_pat != nullptr); }

        //! \return the number of atoms in the SMARTS pattern
        unsigned int NumAtoms() const
        {
            return _pat ? _pat->acount : 0;
        }
        //! \return the number of bonds in the SMARTS pattern
        unsigned int NumBonds() const
        {
            return _pat ? _pat->bcount : 0;
        }

        //! Access the bond @p idx in the internal pattern
        //! \param src The index of the beginning atom
        //! \param dst The index of the end atom
        //! \param ord The bond order of this bond
        //! \param idx The index of the bond in the SMARTS pattern
        void GetBond(int &src, int &dst, int &ord, int idx);
        //! \return the atomic number of the atom @p idx in the internal pattern
        int GetAtomicNum(int idx);
        //! \return the formal charge of the atom @p idx in the internal pattern
        int GetCharge(int idx);

        //! \return the vector binding of the atom @p idx in the internal pattern
        int GetVectorBinding(int idx) const
        {
            return (_pat->atom[idx].vb);
        }
        //@}

        // number and kind of matches to return
        enum MatchType
        {
            All,
            Single,
            AllUnique
        };

        // TODO : match methods

        //! \name Matching methods (SMARTS on a specific Molecule)
        //@{
        //! Perform SMARTS matching for the pattern specified using Init().
        //! \param mol The molecule to use for matching
        //! \param single Whether only a single match is required (faster). Default is false.
        //! \return Whether matches occurred
        bool Match(Molecule &mol, bool single = false);

        //! \name Matching methods (SMARTS on a specific Molecule)
        //@{
        //! Perform SMARTS matching for the pattern specified using Init().
        //! This version is (more) thread safe.
        //! \param mol The molecule to use for matching
        //! \param mlist The resulting match list
        //! \param mtype The match type to use. Default is All.
        //! \return Whether matches occurred
        bool Match(Molecule &mol, std::vector<std::vector<int>> &mlist, MatchType mtype = All) const;

        //! \name Matching methods (SMARTS on a specific Molecule)
        //@{
        //! Thread safe check for any SMARTS match
        //! \param mol The molecule to use for matching
        //! \return Whether there exists any match
        bool HasMatch(Molecule &mol) const;

        bool RestrictedMatch(Molecule &mol, std::vector<std::pair<int, int>> &pairs, bool single = false);

        bool RestrictedMatch(Molecule &mol, bitset &bv, bool single = false);
        //! \return the number of non-unique SMARTS matches
        //! To get the number of unique SMARTS matches, query GetUMapList()->size()
        unsigned int NumMatches() const
        {
            return static_cast<unsigned int>(_mlist.size());
        }

        //! \return the entire list of non-unique matches for this pattern
        //! \see GetUMapList()
        std::vector<std::vector<int>> &GetMapList()
        {
            return (_mlist);
        }
        //! \return An iterator over the (non-unique) match list, starting at the beginning
        std::vector<std::vector<int>>::iterator BeginMList()
        {
            return (_mlist.begin());
        }
        //! \return An iterator over the non-unique match list, set to the end
        std::vector<std::vector<int>>::iterator EndMList()
        {
            return (_mlist.end());
        }

        //! \return the entire list of unique matches for this pattern
        /**
         A unique match is defined as one which does not cover the
        identical atoms that a previous match has covered.
        For instance, the pattern [OD1]~C~[OD1] describes a
        carboxylate group. This pattern will match both atom number
        permutations of the carboxylate, and if GetMapList() is called, both
        matches will be returned. If GetUMapList() is called only unique
        matches of the pattern will be returned.
        **/
        std::vector<std::vector<int>> &GetUMapList();
        //@}

        //! Debugging -- write a list of matches to the output stream
        void WriteMapList(std::ostream &);
    };

    enum ErrorCode
    {
        ////////////////////////////////////////
        //
        // SyntaxError
        //
        ////////////////////////////////////////
        /**
         * No error
         */
        None,
        /**
         * Example: "[C"
         */
        NoClosingAtomBracket = 1,
        /**
         * Examples: "[]", "[13]", "[+]"
         */
        NoSymbolInBracketAtom = 2,
        /**
         * Examples: "[C@@T]", "[C@@A]", "[C@@TB]", "[C@@TH99]", "[C@@OH0]"
         */
        InvalidChirality = 3,
        /**
         * Example: "[C:]"
         */
        NoAtomClass = 4,
        /**
         * Example: "CC(C"
         */
        UnmatchedBranchOpening = 5,
        /**
         * Example: "CC)C"
         */
        UnmatchedBranchClosing = 6,
        /**
         * Examples: "Q", "!", "&", "Mm", "r"
         */
        InvalidAtomExpr = 7,
        /**
         * Example: "[13C$]", "[NP]"
         */
        TrailingCharInBracketAtom = 8,
        /**
         * Example: ".C"
         */
        LeadingDot = 9,
        /**
         * Example: "C."
         */
        TrailingDot = 10,
        /**
         * Example: "C-", "C/"
         */
        TrailingExplicitBond = 11,
        /**
         * Example: "C%123CC%123", "C%CC%"
         */
        InvalidRingBondNumber = 12,
        //////////////////
        // SMARTS
        //////////////////
        /**
         * Example: "[&C]"
         */
        BinaryOpWithoutLeftOperand = 13,
        /**
         * Example: "[C&]"
         */
        BinaryOpWithoutRightOperand = 14,
        /**
         * Example: "[C!]"
         */
        UnaryOpWithoutArgument = 15,
        /**
         * Example: "[Q]"
         */
        InvalidAtomPrimitive = 16,
        /**
         * Example: "C^C"
         */
        InvalidBondPrimitive = 17,
        ////////////////////////////////////////
        //
        // SemanticsError
        //
        ////////////////////////////////////////
        /**
         * Example: "[HH1]"
         */
        HydrogenHydrogenCount = 32,
        /**
         * Example: "C1CC"
         */
        UnmatchedRingBond = 64,
        /**
         * Example: "C-1CCCC=1"
         */
        ConflictingRingBonds = 128,
        /**
         * Example: "C12CCCCC12", "C11"
         */
        InvalidRingBond = 256,
        /**
         * Example: "C[C@H](F)(Cl)(Br)I", "O[C@]"
         */
        InvalidChiralValence = 512,
        /**
         * Example: "N[C@H2](F)I"
         */
        InvalidChiralHydrogenCount = 1024
    };

    /**
     * Exception class.
     */
    class Exception
    {
    public:
        /**
         * Exception type.
         */
        enum Type
        {
            NoError,
            SyntaxError,
            SemanticsError
        };

        /**
         * Default Constructor.
         */
        Exception() : m_type(NoError), m_errorCode(None), m_pos(0), m_length(0)
        {
        }

        /**
         * Constructor.
         *
         * @param type The exception type.
         * @param errorCode The numeric error code.
         * @param what Details of the exception.
         * @param pos The position in the SMILES/SMARTS string.
         * @param length The length of the error in the SMILES/SMARTS string.
         */
        Exception(Type type, ErrorCode errorCode, const std::string &what, std::size_t pos, std::size_t length = 1)
            : m_type(type), m_errorCode(errorCode), m_what(what), m_pos(pos), m_length(length)
        {
        }

        /**
         * The type of the exception.
         */
        Type type() const
        {
            return m_type;
        }

        /**
         * The ErrorCode for the exception.
         */
        ErrorCode errorCode() const
        {
            return m_errorCode;
        }

        /**
         * Details concerning the exception.
         */
        const std::string &what() const
        {
            return m_what;
        }

        /**
         * The position in the specified string where the error starts.
         */
        std::size_t pos() const
        {
            return m_pos;
        }

        /**
         * The length of the error.
         */
        std::size_t length() const
        {
            return m_length;
        }

    private:
        Type m_type;
        ErrorCode m_errorCode;
        std::string m_what;
        std::size_t m_pos;
        std::size_t m_length;
    };

    //! \class OBSmartsMatcher parsmart.h <openbabel/parsmart.h>
    //! \brief Internal class: performs matching; a wrapper around previous
    //! C matching code to make it thread safe.
    class SmartsMatcher
    {
    protected:
        // recursive smarts cache
        std::vector<std::pair<const Pattern *, std::vector<bool>>> RSCACHE;
        // list of fragment patterns (e.g., (*).(*)
        std::vector<const Pattern *> Fragments;
        bool EvalAtomExpr(AtomExpr *expr, AtomPtr atom);
        bool EvalBondExpr(BondExpr *expr, BondPtr bond);
        void SetupAtomMatchTable(std::vector<std::vector<bool>> &ttab,
                                 const Pattern *pat, Molecule &mol);
        void FastSingleMatch(Molecule &mol, const Pattern *pat,
                             std::vector<std::vector<int>> &mlist);

        friend class SSMatch;

    public:
        SmartsMatcher() {}
        virtual ~SmartsMatcher() {}

        bool match(Molecule &mol, const Pattern *pat, std::vector<std::vector<int>> &mlist, bool single = false);
    };

    //! \class SSMatch parsmart.h <openbabel/parsmart.h>
    //! \brief Internal class: performs fast, exhaustive matching used to find
    //! just a single match in match() using recursion and explicit stack handling.
    class SSMatch
    {
    protected:
        bool *_uatoms;
        Molecule *_mol;
        const Pattern *_pat;
        std::vector<int> _map;

    public:
        SSMatch(Molecule &, const Pattern *);
        ~SSMatch();
        void Match(std::vector<std::vector<int>> &v, int bidx = -1);
    };

    void SmartsLexReplace(std::string &,
                                std::vector<std::pair<std::string, std::string>> &);
}

#endif