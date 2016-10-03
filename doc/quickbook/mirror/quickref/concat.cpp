/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_concat
using concat<__none, none> = none;

template <typename R>
using concat<R> = R;

template <typename R>
using concat<__none, R> = R;

template <typename R>
using concat<R, __none> = R;

template <typename Char, Char ... C1, Char ... C2>
using concat<__basic_string<Char, C1...>, basic_string<Char, C2...>>
 = __basic_string<Char, C1..., C2...>;

template <typename ... P1, typename ... P2>
using concat<__range<P1...>, range<P2...>> = __range<P1..., P2...>;

template <typename R1, typename R2, typename ... Rn>
using concat<R1, R2, Rn...> = concat<concat<R1, R2>, Rn...>;
//]

