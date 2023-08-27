// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#include <cassert>
#include <array>
#include <error.h>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "connectivity.h"

using namespace molcpp;

BondIdx::BondIdx(size_t i, size_t j): data_({{0}}) {
    if (i == j) {
        throw ValueError("can not have a bond between an atom and itself");
    }

    data_[0] = std::min(i, j);
    data_[1] = std::max(i, j);
}

size_t BondIdx::operator[](size_t i) const {
    if (i >= 2) {
        throw IndexError("can not access atom n° " + std::to_string(i) + " in bond");
    }
    return data_[i];
}

AngleIdx::AngleIdx(size_t i, size_t j, size_t k): data_({{0}}) {
    if (i == j || i == k || j == k) {
        throw ValueError("can not have the same atom twice in an angle");
    }

    data_[0] = std::min(i, k);
    data_[1] = j;
    data_[2] = std::max(i, k);
}

size_t AngleIdx::operator[](size_t i) const {
    if (i >= 3) {
        throw IndexError("can not access atom n° " + std::to_string(i) + " in angle");
    }
    return data_[i];
}

DihedralIdx::DihedralIdx(size_t i, size_t j, size_t k, size_t m): data_({{0}}) {
    if (i == j || j == k || k == m) {
        throw ValueError("can not have an atom linked to itself in a dihedral angle");
    }

    if (i == k || j == m || i == m) {
        throw ValueError("can not have an atom twice in a dihedral angle");
    }

    if (std::max(i, j) < std::max(k, m)) {
        data_[0] = i;
        data_[1] = j;
        data_[2] = k;
        data_[3] = m;
    } else {
        data_[0] = m;
        data_[1] = k;
        data_[2] = j;
        data_[3] = i;
    }
}

size_t DihedralIdx::operator[](size_t i) const {
    if (i >= 4) {
        throw IndexError("can not access atom n° " + std::to_string(i) + " in dihedral");
    }
    return data_[i];
}

ImproperIdx::ImproperIdx(size_t i, size_t j, size_t k, size_t m): data_({{0}}) {
    if (j == i || j == k || j == m) {
        throw ValueError("can not have an atom linked to itself in an improper dihedral angle");
    }

    if (i == k || i == m || k == m) {
        throw ValueError("can not have an atom twice in an improper dihedral angle");
    }

    std::array<size_t, 3> others = {{i, k, m}};
    std::sort(others.begin(), others.end());
    data_[0] = others[0];
    data_[1] = j;
    data_[2] = others[1];
    data_[3] = others[2];
}

size_t ImproperIdx::operator[](size_t i) const {
    if (i >= 4) {
        throw IndexError("can not access atom n° " + std::to_string(i) + " in improper");
    }
    return data_[i];
}

void Connectivity::recalculate() const {
    angles_.clear();
    dihedrals_.clear();
    impropers_.clear();

    // Generate the list of which atom is bonded to which one
    auto bonded_to = std::vector<std::vector<size_t>>(biggest_atom_ + 1);
    for (auto const& bond: bonds_) {
        assert(bond[0] < bonded_to.size());
        assert(bond[1] < bonded_to.size());
        bonded_to[bond[0]].push_back(bond[1]);
        bonded_to[bond[1]].push_back(bond[0]);
    }

    // Generate the list of angles
    for (auto const& bond: bonds_) {
        auto i = bond[0];
        auto j = bond[1];
        for (auto k: bonded_to[i]) {
            if (k != j) {
                angles_.insert(AngleIdx(k, i, j));
            }
        }

        for (auto k: bonded_to[j]) {
            if (k != i) {
                angles_.insert(AngleIdx(i, j, k));
            }
        }
    }

    // Generate the list of dihedrals
    for (auto const& angle: angles_) {
        auto i = angle[0];
        auto j = angle[1];
        auto k = angle[2];
        for (auto m: bonded_to[i]) {
            if (m != j && m != k) {
                dihedrals_.insert(DihedralIdx(m, i, j, k));
            }
        }

        for (auto m: bonded_to[k]) {
            if (m != i && m != j) {
                dihedrals_.insert(DihedralIdx(i, j, k, m));
            }
        }

        for (auto m: bonded_to[j]) {
            if (m != i && m != k) {
                impropers_.insert(ImproperIdx(i, j, k, m));
            }
        }
    }

    uptodate_ = true;
}

const sorted_set<BondIdx>& Connectivity::bonds() const {
    return bonds_;
}

size_t Connectivity::get_nbonds() const {
    return bonds_.size();
}

const std::vector<BondOrder>& Connectivity::bond_orders() const {
    return bond_orders_;
}

const sorted_set<AngleIdx>& Connectivity::angles() const {
    if (!uptodate_) {
        recalculate();
    }
    return angles_;
}

const sorted_set<DihedralIdx>& Connectivity::dihedrals() const {
    if (!uptodate_) {
        recalculate();
    }
    return dihedrals_;
}

const sorted_set<ImproperIdx>& Connectivity::impropers() const {
    if (!uptodate_) {
        recalculate();
    }
    return impropers_;
}

// auto Connectivity::add_bond(size_t i, size_t j, KV & ... args) {
//     uptodate_ = false;
//     auto result = bonds_.emplace(i, j);
//     if (i > biggest_atom_) {biggest_atom_ = i;}
//     if (j > biggest_atom_) {biggest_atom_ = j;}

//     if (result.second) {
//         auto diff = std::distance(bonds_.cbegin(), result.first);
//         ([&](const auto& arg) {
//             _bond_properties[arg.first].insert(_bond_properties[arg.first].begin() + diff, arg.second);
//         }, ...);        
//     }

//     return result;
// }

void Connectivity::add_bond(size_t i, size_t j, BondOrder bond_order) {
    uptodate_ = false;
    auto result = bonds_.emplace(i, j);
    if (i > biggest_atom_) {biggest_atom_ = i;}
    if (j > biggest_atom_) {biggest_atom_ = j;}

    if (result.second) {
        auto diff = std::distance(bonds_.cbegin(), result.first);
        bond_orders_.insert(bond_orders_.begin() + diff, bond_order);
    }
}

void Connectivity::remove_bond(size_t i, size_t j) {
    auto pos = bonds_.find(BondIdx(i, j));
    if (pos != bonds_.end()) {
        uptodate_ = false;
        auto result = bonds_.erase(pos);

        auto diff = std::distance(bonds_.cbegin(), result);
        bond_orders_.erase(bond_orders_.begin() + diff);
        assert(bond_orders_.size() == bonds_.size());
    }
}

void Connectivity::atom_removed(size_t index) {
    auto to_remove = std::vector<BondIdx>();
    auto to_add = std::vector<BondIdx>();
    auto bo_add = std::vector<BondOrder>();

    const auto& bonds = bonds_.as_vec();
    for (size_t idx = 0; idx < bonds_.size(); idx++) {
        const auto& bond = bonds[idx];

        if (bond[0] == index || bond[1] == index) {
            throw ValueError("can not shift atomic indexes that still have a bond");
        }
        if (bond[0] > index || bond[1] > index) {
            to_remove.push_back(bond);

            auto i = bond[0] > index ? bond[0] - 1 : bond[0];
            auto j = bond[1] > index ? bond[1] - 1 : bond[1];
            to_add.emplace_back(i, j);
            bo_add.push_back(bond_orders_[idx]);
        }
    }

    for (auto bond: to_remove) {
        this->remove_bond(bond[0], bond[1]);
    }

    for (size_t idx = 0; idx < to_add.size(); idx++) {
        const auto& bond = to_add[idx];
        this->add_bond(bond[0], bond[1], bo_add[idx]);
    }
}

BondOrder Connectivity::bond_order(size_t i, size_t j) const {
    auto pos = bonds_.find(BondIdx(i, j));
    if (pos != bonds_.end()) {
        auto diff = std::distance(bonds_.cbegin(), pos);
        return bond_orders_[static_cast<size_t>(diff)];
    }

    throw ValueError(
        "out of bounds atomic index in `Connectivity::bond_order`: "
        "No bond between " + std::to_string(i) + " and " + std::to_string(j) + " exists"
    );
}
