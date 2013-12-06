#!/bin/bash
#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cd "$(dirname ${0})/../_build/" &&
cmake .. &&
cd "test/mire/" &&
ctest
