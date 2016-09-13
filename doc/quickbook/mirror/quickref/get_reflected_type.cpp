/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_reflected_type
template <__std_meta_Type T>
using get_reflected_type<__metaobject<T>>
 = __std_meta_get_reflected_type_t<T>;

template <__std_meta_Object O>
using get_reflected_type<__metaobject<O>> = none /*<
For metaobjects which do not reflect a type [^__none] is returned.
>*/;

using get_reflected_type<__none> = __none;
//]

