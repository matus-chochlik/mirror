#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

add_mire_exec_test("mirror" traits)
add_mire_exec_test("mirror" compare)
add_mire_exec_test("mirror" original_type)
add_mire_exec_test("mirror" base_name)
add_mire_exec_test("mirror" full_name)
add_mire_exec_test("mirror" scope)

add_mire_exec_test("mirror" typedef_type)
