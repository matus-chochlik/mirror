#!/bin/bash
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
K=200
S=100
F="$(basename ${0} .sh)"
J=$(grep -c -e 'processor\s\+:\s\+[0-9]\+' < /proc/cpuinfo)
TIMEFORMAT=%3R
#
while getopts "k:s:j:f:" arg
do
	case ${arg} in
		k) K=${OPTARG};;
		s) S=${OPTARG};;
		j) J=${OPTARG};;
		f) F=${OPTARG};;
		*) exit 1;;
	esac
done
#
this_dir="$(realpath $(dirname ${0}))"
work_dir="$(mktemp -d)"
function cleanup {
	rm -r "${work_dir}"
}
trap cleanup EXIT
#
cat << EOD > "${work_dir}/Makefile"
all: measurements.csv

empty:
	touch \$@

src-%.time: src-%.cpp
	(TIMEFORMAT=%3R /bin/bash -c "time g++ -std=c++20 -ftemplate-depth=$((K * S + 10)) -o /dev/null \$<") 2> \$@

src-%.csv: src-%.time
	echo "\$*;\$(file <\$<)" | tr ',' '.' > \$@

measurements.csv: \\
EOD

for M in $(seq 1 ${K})
do
N=$((M * S))
#
echo "	src-${N}.csv \\" >> "${work_dir}/Makefile"
#
cat << EOD > "${work_dir}/src-${N}.cpp"
template <int I>
struct wrapper { consteval operator int() const { return I;} };

static int foo(wrapper<0>) {
    return 0;
}

template <int I>
int foo(wrapper<I>) {
    return foo(wrapper<I-1>{});
}

int main() {
	return foo(wrapper<$((N))>{});
}
EOD
done
cat << EOD >> "${work_dir}/Makefile"
	empty
	cat \$^ > \$@
EOD

cd "${work_dir}"
make -j ${J} && (
	echo "instantiations;compile-time [s]"
	cat measurements.csv
) > "${this_dir}/${F}-${K}x${S}.csv"
