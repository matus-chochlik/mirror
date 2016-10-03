/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_public_data_members
template <__std_meta_Record R>
using get_public_data_members<__metaobject<R>>
 = __metaobject_sequence<__std_meta_get_public_data_members_m<R>>;

template <__std_meta_Object O>
using get_public_data_members<__metaobject<O>> = none /*<
For metaobjects which do not reflect a class [^__none] is returned.
>*/;

using get_public_data_members<__none> = __none;
//]

