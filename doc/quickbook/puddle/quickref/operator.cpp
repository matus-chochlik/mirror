/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddled_operator_definition
#define PUDDLED(X) __MIRRORED(X){}
//]

//[puddled_operator_example_1
auto meta_int = __PUDDLED(int);
auto meta_std = PUDDLED(std);
//]

