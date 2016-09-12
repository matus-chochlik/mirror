/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_enumerators
template <__std_meta_Enum E>
using get_enumerators<__metaobject<E>>
 = __metaobject_sequence<__std_meta_get_enumerators_m<E>>;

template <__std_meta_Object O>
using get_enumerators<__metaobject<O>> = none /*<
For metaobjects which do not reflect an enumeration [^__none] is returned.
>*/;

using get_enumerators<__none> = __none;
//]

