/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_make_enum_to_string_map
template <typename T /*< Must be an enumeration type >*/>
static constexpr inline
__std_map<T, __std_string> make_enum_to_string_map(void);
//]
//[refltool_enum_to_string
template <typename T>
static inline
const __std_string& enum_to_string(T v);
//]

