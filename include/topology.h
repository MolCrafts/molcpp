#pragma once
#include <vector>
#include <string>
#include <map>

// #include <chemfiles.hpp>

#include "item.h"
#include "algo.h"
#include "log.h"
#include "error.h"
#include "graph.h"

namespace molcpp
{
    class Topology
    {
        public:

            Topology(std::string name) : _name(name){};

            // Atom Section
            Atom& new_atom(std::string name);
            void del_atom(std::string name);
            void add_atom(Atom& atom);
            Atom& get_atom(std::string name);
            size_t get_natoms() const;

            // Bond Section
            Bond& new_bond(Atom& a1, Atom& a2);
            void del_bond(Bond& bond);
            void add_bond(Bond& bond);
            Bond& get_bond(Atom& a1, Atom& a2);
            void del_bond(Atom& a1, Atom& a2);
            size_t get_nbonds() const;


            // Topology Section
            Topology& new_topo(std::string name);
            void del_topo(std::string name);
            Topology& add_topo(Topology& topo);
            Topology& get_topo(std::string name);

            // Properties Section
            std::string get_name() const;

        private:
            std::map<std::string, Atom> _atoms;
            std::vector<Bond> _bonds;
            
            std::map<std::string, Topology> _topos;

            std::string _name;
    };
}