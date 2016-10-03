/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_has_source_info
template <__std_meta_Object O>
using has_source_info<__metaobject<O>> = __bool_<__unspecified /*<
Returns [^__true_] if the base-level entity reflected by the argument was
declared in source code.  If the base-level entity does not have
an in-source declaration (for example a specifier, native type, etc.) then
an [^__false_] is returned.
>*/>;

using has_source_info<__none> = __false_;
//]

