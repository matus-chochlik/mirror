#!/bin/bash
#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if [ $# -lt 2 ]
then
	echo "Error: Missing argument(s)"
	echo "Usage $(basename ${0}) <library> <example-1> [example-2] ..."
	exit
fi

LIB=${1}
shift

cd "$(dirname ${0})/../_build/" &&
cmake .. &&
cd "example/mire/${LIB}" &&
for EXAMPLE
do make ${EXAMPLE} && ./${EXAMPLE}
done
