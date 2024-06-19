#!/bin/bash

# Clone and build xtl
git clone https://github.com/xtensor-stack/xtl.git --depth 1 -b master /opt/xtl
mkdir /opt/xtl/build
cmake -S /opt/xtl -B /opt/xtl/build && cmake --build /opt/xtl/build --target install

# Clone and build xtensor
git clone https://github.com/xtensor-stack/xtensor.git --depth 1 -b master /opt/xtensor
mkdir /opt/xtensor/build
cmake -S /opt/xtensor -B /opt/xtensor/build && cmake --build /opt/xtensor/build --target install

# Clone and build xtensor-blas
git clone https://github.com/xtensor-stack/xtensor-blas.git --depth 1 -b master /opt/xtensor-blas
mkdir /opt/xtensor-blas/build
cmake -S /opt/xtensor-blas -B /opt/xtensor-blas/build && cmake --build /opt/xtensor-blas/build --target install

git clone https://github.com/doctest/doctest --depth 1 -b master /opt/doctest
mkdir /opt/doctest/build
cmake -S /opt/doctest -B /opt/doctest/build && cmake --build /opt/doctest/build --target install

# Define arguments
base_tag=jammy
llvm_version=16

# Install necessary packages
apt-get install -y --no-install-recommends \
    gnupg2 \
    gnupg-agent \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Add LLVM GPG key and repository
curl --fail --silent --show-error --location https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
echo "deb http://apt.llvm.org/$base_tag/ llvm-toolchain-$base_tag-$llvm_version main" >> /etc/apt/sources.list.d/llvm.list

# Update and upgrade system again
apt-get update --fix-missing && apt-get -y upgrade

# Install clang tools
apt-get install -y --no-install-recommends \
    clang-format-${llvm_version} \
    clang-tidy-${llvm_version} \
    && rm -rf /var/lib/apt/lists/*

# Create symbolic links for clang tools
ln -s /usr/bin/clang-format-${llvm_version} /usr/local/bin/clang-format
ln -s /usr/bin/clang-tidy-${llvm_version} /usr/local/bin/clang-tidy
