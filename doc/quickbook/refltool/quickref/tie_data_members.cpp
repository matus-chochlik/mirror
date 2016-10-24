/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_tie_data_members
template <typename T>
constexpr __std_tuple<__unspecified&...> tie_data_members(T& v);
//]
//[refltool_tie_public_data_members
template <typename T>
constexpr __std_tuple<__unspecified&...> tie_public_data_members(T& v);
//]

