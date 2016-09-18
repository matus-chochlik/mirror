/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_wrap_if_not_special_1
template <typename T>
using wrap_if_not_special = __identity<T>; /*<
For all types except the special cases below, the parameter [^T] is wrapped
by the [^__identity] template.
>*/
//]
//[mirror_op_wrap_if_not_special_2
template <>
using wrap_if_not_special<__none> = none; /*<
For the following special types, [^wrap_if_not_special] returns the argument
unchanged.
>*/

template <typename Int, Int I>
using wrap_if_not_special<__int_const<Int, I>> = int_const<Int, I>;

template <typename ... P>
using wrap_if_not_special<__range<P...>> = range<P...>;

template <typename Char, Char ... C>
using wrap_if_not_special<__basic_string<Char, C...>>
 = basic_string<Char, C...>;

template <typename O>
using wrap_if_not_special<__metaobject<O>> = metaobject<O>;

template <typename S>
using wrap_if_not_special<__metaobject_sequence<S>> = metaobject_sequence<S>;
//]

