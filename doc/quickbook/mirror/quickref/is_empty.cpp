/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_is_empty
template <__std_meta_ObjectSequence S>
using is_empty<__metaobject_sequence<S>> = __bool_<__std_meta_get_size_v<S> == 0>;

template <typename Char, Char ... C>
using is_empty<__basic_string<Char, C...>> = __bool_<sizeof...(C) == 0>;

template <typename ... P>
using is_empty<__range<P...>> = __bool_<sizeof...(P) == 0>;

using is_empty<__none> = __true_;
//]

