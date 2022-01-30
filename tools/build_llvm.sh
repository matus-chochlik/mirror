#!/bin/bash
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
tool_dir=$(realpath "$(dirname ${0})")
root_dir=$(dirname "${tool_dir}")
llvm_install_dir=/opt/mirror/llvm
llvm_build_dir="${tool_dir}/_build"
compile_jobs=$(grep -c -e 'processor\s\+:\s\+[0-9]\+' < /proc/cpuinfo)
link_jobs=$(grep MemTotal /proc/meminfo | awk '{printf "%.0f",  $2/(1024*1024*6)}')
clean="false"

if [[ -x "$(which distcc)" ]]
then compile_jobs="$(distcc -j)"
fi

if [[ -f "${root_dir}/LLVM_PREFIX" ]]
then llvm_install_dir=$(< "${root_dir}/LLVM_PREFIX")
fi

while getopts "b:i:C:L:c" arg
do
	case ${arg} in
		b) llvm_build_dir=${OPTARG};;
		i) llvm_install_dir=${OPTARG};;
		C) compile_jobs=${OPTARG};;
		L) link_jobs=${OPTARG};;
		c) clean="true";;
		*) exit 1;;
	esac
done

if [[ "x${llvm_build_dir}" == "x" ]]
then echo "invalid build directory path '${llvm_build_dir}'"; exit 2
fi

if [[ "x${clean}" == "xtrue" ]]
then rm -rf "${llvm_build_dir}/*"
fi

cmake_args=()
cmake_args+=(-G Ninja)
cmake_args+=(-DCMAKE_INSTALL_PREFIX="${llvm_install_dir}")
if [[ -f "${tool_dir}/toolchain.cmake" ]]
then cmake_args+=(-DCMAKE_TOOLCHAIN_FILE="${tool_dir}/toolchain.cmake")
fi

ninja_args=(-j ${compile_jobs})

mkdir -p "${llvm_build_dir}" && \
pushd "${llvm_build_dir}" && \
cmake \
	"${cmake_args[@]}" \
	-DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
	-DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
	-DLLVM_INCLUDE_BENCHMARKS=Off \
	-DLLVM_PARALLEL_COMPILE_JOBS=${compile_jobs} \
	-DLLVM_PARALLEL_LINK_JOBS=${link_jobs} \
	"${root_dir}/submodules/llvm-project/llvm" && \
ninja "${ninja_args[@]}" install install-cxx install-cxxabi && \
popd
