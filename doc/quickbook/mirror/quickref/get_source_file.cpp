/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_source_file
template <__std_meta_Object O>
using get_source_file<__metaobject<O>> = __string<__unspecified /*<
The characters of the path to the source file where the base-level entity
reflected by the argument was declared as returned by
[^__std_meta_get_source_file]. If the base-level entity does not have
an in-source declaration (for example a specifier, native type, etc.) then
an empty string is returned.
>*/>;

using get_source_file<__none> = __empty_string;
//]

