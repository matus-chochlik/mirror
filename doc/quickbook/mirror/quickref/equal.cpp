/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_equal
template <typename Char, Char ... C1, Char ... C2>
using equal<__basic_string<Char, C1...>, basic_string<Char, C2...>>
 = __bool_<__unspecified /*<
[^true] if the strings are equal, [^false] otherwise.
>*/>;

template <typename ... P1, typename ... P2>
using equal<__range<P1...>, range<P2...>>
 = __bool_<__unspecified /*<
[^true] if the ranges are equal, [^false] otherwise.
>*/>;
//]

