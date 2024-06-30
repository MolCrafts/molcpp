#pragma once

#include "xtensor/xarray.hpp"

#include "molcpp/export.hpp"
#include "molcpp/types.hpp"
#include "molcpp/topology.hpp"

namespace molcpp
{
    class Struct
    {
        using StructProp = std::variant<xt::xarray<int>, xt::xarray<double>, xt::xarray<std::string>>;
        using StructProps = Property<xt::xarray<int>, xt::xarray<double>, xt::xarray<std::string>>;

      public:
        /// Default constructor
        Struct() = default;

        virtual ~Struct() = default;

        /// Declare copy constructor
        Struct(const Struct &) = default;

        /// Declare copy assignment operator
        auto operator=(const Struct &) -> Struct & = default;

        /// Declare move constructor
        Struct(Struct &&) = default;

        /// Declare move assignment operator
        auto operator=(Struct &&) -> Struct & = default;

        void add_atom_prop(std::string key, StructProp value)
        {
            _atoms.set(key, value);
        }

      private:

        Topology _topology;

        StructProps _atoms;
        StructProps _bonds;
        StructProps _angles;
    };
}