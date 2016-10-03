/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_push_back
template <typename Char, Char ... C1, Char C2>
using push_back<__basic_string<Char, C1...>, __int_const<Char, C2>>
 = __basic_string<Char, C1..., C2>;

template <typename ... P1, typename P2>
using push_back<__range<P1...>, P2> = __range<P1..., P2>;

template <typename R>
using push_back<R, __none> = R;
//]

