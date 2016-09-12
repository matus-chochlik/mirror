/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_source_column
template <__std_meta_object O>
using get_source_column<__metaobject<O>> = __unsigned_<__unspecified /*<
The column number in the source file where the base-level entity
reflected by the argument was declared as returned by
[^__std_meta_get_source_column]. If the base-level entity does not have
an in-source declaration (for example a specifier, native type, etc.) then
an zero is returned.
>*/>;

using get_source_column<__none> = __empty_string;
//]

