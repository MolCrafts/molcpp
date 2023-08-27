#pragma once

#include <algorithm> // IWYU pragma: keep
#include <array>
#include <vector>

#include "sorted_set.h"
#include "dict.h"

namespace molcpp
{

enum BondOrder
{
    UNKNOWN = 0,    ///< Bond order is unknown or unspecified
    SINGLE = 1,     ///< Single bond
    DOUBLE = 2,     ///< Double bond
    TRIPLE = 3,     ///< Triple bond
    QUADRUPLE = 4,  ///< Quadruplet bond
    QUINTUPLET = 5, ///< Quintuplet bond

    // space for more bond types if needed
    DOWN = 250,     ///< Single bond direction from first atom to second is 'down'. Used for cis-trans isomers
    UP = 251,       ///< Single bond direction from first atom to second is 'up'. Used for cis-trans isomers
    DATIVE_R = 252, ///< Dative bond where the electrons are localized to the first atom
    DATIVE_L = 253, ///< Dative bond where the electrons are localized to the second atom
    AMIDE = 254,    ///< Amide bond (C(=O)-NH)
    AROMATIC = 255, ///< Aromatic bond (for example the ring bonds in benzene)
};

/// The `BondIdx` class ensure a canonical representation of a bond two atoms.
///
/// This class implements all the comparison operators, as well as indexing.
///
/// @example{connectivity/bond.cpp}
class BondIdx final
{
  public:
    /// Create a new `BondIdx` containing the atoms `i` and `j`.
    ///
    /// @throw Error if `i == j`
    BondIdx(size_t i, size_t j);

    ~BondIdx() = default;
    BondIdx(BondIdx &&) noexcept = default;
    BondIdx &operator=(BondIdx &&) noexcept = default;
    BondIdx(const BondIdx &) = default;
    BondIdx &operator=(const BondIdx &) = default;

    /// Get the index of the `i`th atom (`i == 0` or `i == 1`) in the bond.
    ///
    /// @throws OutOfBounds if `i` is not 0 or 1
    size_t operator[](size_t i) const;

  private:
    std::array<size_t, 2> data_;

    friend bool operator==(const BondIdx &lhs, const BondIdx &rhs);
    friend bool operator!=(const BondIdx &lhs, const BondIdx &rhs);
    friend bool operator<(const BondIdx &lhs, const BondIdx &rhs);
    friend bool operator<=(const BondIdx &lhs, const BondIdx &rhs);
    friend bool operator>(const BondIdx &lhs, const BondIdx &rhs);
    friend bool operator>=(const BondIdx &lhs, const BondIdx &rhs);
};

inline bool operator==(const BondIdx &lhs, const BondIdx &rhs)
{
    return lhs.data_ == rhs.data_;
}

inline bool operator!=(const BondIdx &lhs, const BondIdx &rhs)
{
    return lhs.data_ != rhs.data_;
}

inline bool operator<(const BondIdx &lhs, const BondIdx &rhs)
{
    return lhs.data_ < rhs.data_;
}

inline bool operator<=(const BondIdx &lhs, const BondIdx &rhs)
{
    return lhs.data_ <= rhs.data_;
}

inline bool operator>(const BondIdx &lhs, const BondIdx &rhs)
{
    return lhs.data_ > rhs.data_;
}

inline bool operator>=(const BondIdx &lhs, const BondIdx &rhs)
{
    return lhs.data_ >= rhs.data_;
}

/// The `AngleIdx` class ensure a canonical representation of an angle between
/// three atoms.
///
/// An angle is formed by two consecutive bonds:
///
///     |  i       k  |
///     |    \   /    |
///     |      j      |
///
/// This class implements all the comparison operators, as well as indexing.
///
/// @example{connectivity/angle.cpp}
class AngleIdx final
{
  public:
    /// Create a new `AngleIdx` containing the atoms `i`, `j` and `k`.
    ///
    /// @throw Error if `i == j`, `j == k` or `i == k`
    AngleIdx(size_t i, size_t j, size_t k);

    ~AngleIdx() = default;
    AngleIdx(AngleIdx &&) noexcept = default;
    AngleIdx &operator=(AngleIdx &&) noexcept = default;
    AngleIdx(const AngleIdx &) = default;
    AngleIdx &operator=(const AngleIdx &) = default;

    /// Get the index of the `i`th atom (`i == 0`, `i == 1` or `i == 2`) in the
    /// angle.
    ///
    /// @throws OutOfBounds if `i` is not 0, 1 or 2
    size_t operator[](size_t i) const;

  private:
    std::array<size_t, 3> data_;

    friend bool operator==(const AngleIdx &lhs, const AngleIdx &rhs);
    friend bool operator!=(const AngleIdx &lhs, const AngleIdx &rhs);
    friend bool operator<(const AngleIdx &lhs, const AngleIdx &rhs);
    friend bool operator<=(const AngleIdx &lhs, const AngleIdx &rhs);
    friend bool operator>(const AngleIdx &lhs, const AngleIdx &rhs);
    friend bool operator>=(const AngleIdx &lhs, const AngleIdx &rhs);
};

inline bool operator==(const AngleIdx &lhs, const AngleIdx &rhs)
{
    return lhs.data_ == rhs.data_;
}

inline bool operator!=(const AngleIdx &lhs, const AngleIdx &rhs)
{
    return lhs.data_ != rhs.data_;
}

inline bool operator<(const AngleIdx &lhs, const AngleIdx &rhs)
{
    return lhs.data_ < rhs.data_;
}

inline bool operator<=(const AngleIdx &lhs, const AngleIdx &rhs)
{
    return lhs.data_ < rhs.data_;
}

inline bool operator>(const AngleIdx &lhs, const AngleIdx &rhs)
{
    return lhs.data_ > rhs.data_;
}

inline bool operator>=(const AngleIdx &lhs, const AngleIdx &rhs)
{
    return lhs.data_ > rhs.data_;
}

/// The `DihedralIdx` class ensure a canonical representation of a dihedral angle
/// between four atoms.
///
/// A dihedral angle is formed by three consecutive bonds:
///
///     |  i       k     |
///     |    \   /   \   |
///     |      j      m  |
///
/// This class implements all the comparison operators, as well as indexing.
///
/// @example{connectivity/dihedral.cpp}
class DihedralIdx final
{
  public:
    /// Create a new `DihedralIdx` containing the atoms `i`, `j`, `k` and `m`.
    ///
    /// @throw Error if any of `i`, `j`, `k`, `m` has the same value as another
    DihedralIdx(size_t i, size_t j, size_t k, size_t m);

    ~DihedralIdx() = default;
    DihedralIdx(DihedralIdx &&) noexcept = default;
    DihedralIdx &operator=(DihedralIdx &&) noexcept = default;
    DihedralIdx(const DihedralIdx &) = default;
    DihedralIdx &operator=(const DihedralIdx &) = default;

    /// Get the index of the `i`th atom (`i` can be 0, 1, 2 or 3) in the
    /// dihedral.
    ///
    /// @throws OutOfBounds if `i` is not 0, 1, 2 or 3.
    size_t operator[](size_t i) const;

  private:
    std::array<size_t, 4> data_;

    friend bool operator==(const DihedralIdx &lhs, const DihedralIdx &rhs);
    friend bool operator!=(const DihedralIdx &lhs, const DihedralIdx &rhs);
    friend bool operator<(const DihedralIdx &lhs, const DihedralIdx &rhs);
    friend bool operator<=(const DihedralIdx &lhs, const DihedralIdx &rhs);
    friend bool operator>(const DihedralIdx &lhs, const DihedralIdx &rhs);
    friend bool operator>=(const DihedralIdx &lhs, const DihedralIdx &rhs);
};

inline bool operator==(const DihedralIdx &lhs, const DihedralIdx &rhs)
{
    return lhs.data_ == rhs.data_;
}

inline bool operator!=(const DihedralIdx &lhs, const DihedralIdx &rhs)
{
    return lhs.data_ != rhs.data_;
}

inline bool operator<(const DihedralIdx &lhs, const DihedralIdx &rhs)
{
    return lhs.data_ < rhs.data_;
}

inline bool operator<=(const DihedralIdx &lhs, const DihedralIdx &rhs)
{
    return lhs.data_ <= rhs.data_;
}

inline bool operator>(const DihedralIdx &lhs, const DihedralIdx &rhs)
{
    return lhs.data_ > rhs.data_;
}

inline bool operator>=(const DihedralIdx &lhs, const DihedralIdx &rhs)
{
    return lhs.data_ >= rhs.data_;
}

/// The `ImproperIdx` class ensure a canonical representation of an improper
/// dihedral angle between four atoms.
///
/// An improper dihedral angle is formed by three bonds around a central atom:
///
///     |  i       k  |
///     |    \   /    |
///     |      j      |
///     |      |      |
///     |      m      |
///
/// This class implements all the comparison operators, as well as indexing.
///
/// The second atom of the improper is always the central atom.
///
/// @example{connectivity/improper.cpp}
class ImproperIdx final
{
  public:
    /// Create a new `ImproperIdx` containing the atoms `i`, `j`, `k` and `m`. `j`
    /// must be the central atom of the improper.
    ///
    /// @throw Error if any of `i`, `j`, `k`, `m` has the same value as another
    ImproperIdx(size_t i, size_t j, size_t k, size_t m);

    ~ImproperIdx() = default;
    ImproperIdx(ImproperIdx &&) noexcept = default;
    ImproperIdx &operator=(ImproperIdx &&) noexcept = default;
    ImproperIdx(const ImproperIdx &) = default;
    ImproperIdx &operator=(const ImproperIdx &) = default;

    /// Get the index of the `i`th atom (`i` can be 0, 1, 2 or 3) in the
    /// improper.
    ///
    /// @throws OutOfBounds if `i` is not 0, 1, 2 or 3.
    size_t operator[](size_t i) const;

  private:
    std::array<size_t, 4> data_;

    friend bool operator==(const ImproperIdx &lhs, const ImproperIdx &rhs);
    friend bool operator!=(const ImproperIdx &lhs, const ImproperIdx &rhs);
    friend bool operator<(const ImproperIdx &lhs, const ImproperIdx &rhs);
    friend bool operator<=(const ImproperIdx &lhs, const ImproperIdx &rhs);
    friend bool operator>(const ImproperIdx &lhs, const ImproperIdx &rhs);
    friend bool operator>=(const ImproperIdx &lhs, const ImproperIdx &rhs);
};

inline bool operator==(const ImproperIdx &lhs, const ImproperIdx &rhs)
{
    return lhs.data_ == rhs.data_;
}

inline bool operator!=(const ImproperIdx &lhs, const ImproperIdx &rhs)
{
    return lhs.data_ != rhs.data_;
}

inline bool operator<(const ImproperIdx &lhs, const ImproperIdx &rhs)
{
    return lhs.data_ < rhs.data_;
}

inline bool operator<=(const ImproperIdx &lhs, const ImproperIdx &rhs)
{
    return lhs.data_ <= rhs.data_;
}

inline bool operator>(const ImproperIdx &lhs, const ImproperIdx &rhs)
{
    return lhs.data_ > rhs.data_;
}

inline bool operator>=(const ImproperIdx &lhs, const ImproperIdx &rhs)
{
    return lhs.data_ >= rhs.data_;
}

/// The connectivity struct store a cache of the bonds, angles and dihedrals
/// in the system. The `recalculate` function should be called when bonds are
/// added or removed. The `bonds` set is the main source of information, all the
/// other data are cached from it.
class Connectivity final
{
  public:
    Connectivity() = default;

    /// Get the bonds in this connectivity
    const sorted_set<BondIdx> &bonds() const;

    size_t get_nbonds() const;

    /// Get the bond orders in this connectivity
    const std::vector<BondOrder> &bond_orders() const;

    /// Get the angles in this connectivity
    const sorted_set<AngleIdx> &angles() const;

    /// Get the dihedrals in this connectivity
    const sorted_set<DihedralIdx> &dihedrals() const;

    /// Get the impropers in this connectivity
    const sorted_set<ImproperIdx> &impropers() const;

    /// Add a bond between the atoms `i` and `j`
    void add_bond(size_t i, size_t j, BondOrder order = BondOrder::UNKNOWN);
    
    /// template <typename... KV> void add_bond(size_t i, size_t j, KV &...args);

    /// Remove any bond between the atoms `i` and `j`
    void remove_bond(size_t i, size_t j);

    /// Update the indexes of the bonds after atom removal
    ///
    /// This function shifts all indexes bigger than `index` in the
    /// bonds/angles/dihedrals/impropers lists by -1.
    void atom_removed(size_t index);

    /// Get the bond order of the bond between i and j
    BondOrder bond_order(size_t i, size_t j) const;

  private:
    /// Recalculate the angles and the dihedrals from the bond list
    void recalculate() const;

    /// Biggest index within the atoms we know about. Used to pre-allocate
    /// memory when recomputing bonds.
    size_t biggest_atom_ = 0;
    /// Bonds in the system
    sorted_set<BondIdx> bonds_;
    /// Angles in the system
    mutable sorted_set<AngleIdx> angles_;
    /// DihedralIdx angles in the system
    mutable sorted_set<DihedralIdx> dihedrals_;
    /// ImproperIdx dihedral angles in the system
    mutable sorted_set<ImproperIdx> impropers_;
    /// Is the cached content up to date ?
    mutable bool uptodate_ = false;
    /// Store the bond properties
    std::vector<BondOrder> bond_orders_;
    /// Dict _bond_properties;
};

} // namespace molcpp