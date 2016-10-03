/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_size
template <__std_meta_ObjectSequence S>
using get_size<__metaobject_sequence<S>> = __size_const<__std_meta_get_size_v<S>>;

template <typename Char, Char ... C>
using get_size<__basic_string<Char, C...>> = __size_const<sizeof...(C)>;

template <typename ... P>
using get_size<__range<P...>> = __size_const<sizeof...(P)>;

using get_size<__none> = __size_const<0>;

template <typename X>
using size = get_size<X>;
//]

