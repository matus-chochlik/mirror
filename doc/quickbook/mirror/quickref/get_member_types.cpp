/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_member_types
template <__std_meta_Record R>
using get_member_types<__metaobject<R>>
 = __metaobject_sequence<__std_meta_get_member_types_m<R>>;

template <__std_meta_Object O>
using get_member_types<__metaobject<O>> = none /*<
For metaobjects which do not reflect a class [^__none] is returned.
>*/;

using get_member_types<__none> = __none;
//]

