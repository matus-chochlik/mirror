/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_make_string_to_enum_map
template <typename T /*< Must be an enumeration type >*/>
constexpr __std_map<__std_string, T> make_string_to_enum_map(void);
//]
//[refltool_string_to_enum
template <typename T /*< Must be an enumeration type >*/>
T string_to_enum(const __std_string& s);
//]

