/**
 * @file reflbase/string.hpp
 * @brief compile-time string
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLBASE_STRING_1105240825_HPP
#define REFLBASE_STRING_1105240825_HPP

#include <cstdint>

namespace reflbase {

template <char ... C>
struct string
{
	static constexpr const std::size_t size = sizeof...(C);
	static constexpr const char cvalue[sizeof...(C)+1] = {C...,'\0'};
	static constexpr const char  value[sizeof...(C)+1] = {C...,'\0'};
};

template <char ... C>
constexpr const char string<C...>::value[sizeof...(C)+1];

using empty_string = string<>;

} // namespace reflbase

#endif //include guard

