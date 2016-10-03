/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_type
template <__std_meta_Typed T>
using get_type<__metaobject<T>>
 = __metaobject<__std_meta_get_type_m<T>>;

template <__std_meta_Object O>
using get_type<__metaobject<O>> = none /*<
For metaobjects which do not reflect typed declarations [^__none] is returned.
>*/;

using get_type<__none> = __none;
//]

