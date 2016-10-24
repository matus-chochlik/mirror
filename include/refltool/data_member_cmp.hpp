/**
 * @file refltool/data_member_cmp.hpp
 * @brief Implementation of generic per-data member comparisons
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_DATA_MEMBER_CMP_1105240825_HPP
#define REFLTOOL_DATA_MEMBER_CMP_1105240825_HPP

#include "tie_data_members.hpp"

namespace refltool {

// equal
template <typename T = void>
struct equal_data_members
{
	constexpr bool operator()(const T& a, const T& b) const
	{
		return tie_data_members(a) == tie_data_members(b);
	}
};

template <>
struct equal_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const
	{
		return equal_data_members<T>()(a, b);
	}
};

constexpr const equal_data_members<> data_members_equal = {};

// not-equal
template <typename T = void>
struct not_equal_data_members
{
	constexpr bool operator()(const T& a, const T& b) const
	{
		return tie_data_members(a) != tie_data_members(b);
	}
};

template <>
struct not_equal_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const
	{
		return not_equal_data_members<T>()(a, b);
	}
};

constexpr const not_equal_data_members<> data_members_not_equal = {};

// less
template <typename T = void>
struct less_data_members
{
	constexpr bool operator()(const T& a, const T& b) const
	{
		return tie_data_members(a) <  tie_data_members(b);
	}
};

template <>
struct less_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const
	{
		return less_data_members<T>()(a, b);
	}
};

constexpr const less_data_members<> data_members_less = {};

// less-equal
template <typename T = void>
struct less_equal_data_members
{
	constexpr bool operator()(const T& a, const T& b) const
	{
		return tie_data_members(a) <= tie_data_members(b);
	}
};

template <>
struct less_equal_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const
	{
		return less_equal_data_members<T>()(a, b);
	}
};

constexpr const less_equal_data_members<> data_members_less_equal = {};

// greater
template <typename T = void>
struct greater_data_members
{
	constexpr bool operator()(const T& a, const T& b) const
	{
		return tie_data_members(a) >  tie_data_members(b);
	}
};

template <>
struct greater_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const
	{
		return greater_data_members<T>()(a, b);
	}
};

constexpr const greater_data_members<> data_members_greater = {};

// greater-equal
template <typename T = void>
struct greater_equal_data_members
{
	constexpr bool operator()(const T& a, const T& b) const
	{
		return tie_data_members(a) >= tie_data_members(b);
	}
};

template <>
struct greater_equal_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const
	{
		return greater_equal_data_members<T>()(a, b);
	}
};

constexpr const greater_equal_data_members<> data_members_greater_equal = {};

} // namespace refltool

#endif //include guard

