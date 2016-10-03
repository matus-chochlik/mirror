/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_element
template <__std_meta_ObjectSequence S, size_t I>
using get_element<__metaobject_sequence<S>, __size_const<I>>
 = __metaobject<__std_meta_get_element_m<S, I>>;

template <typename Char, Char ... C, size_t I>
using get_element<__basic_string<Char, C...>, size_const<I>>
 = __int_const<Char, __unspecified /*<
The ['I]-th character in the pack [^C].
>*/>;

template <typename ... P, size_t I>
using get_element<__range<P...>, size_const<I>>
 = __unspecified /*<
The ['I]-th type in the pack [^P].
>*/;

template <size_t I>
using get_element<__none, size_const<I>> = __none;
//]

