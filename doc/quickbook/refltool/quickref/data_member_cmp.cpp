/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_equal_data_members
template <typename T = void>
struct equal_data_members
{
	constexpr bool operator()(const T& a, const T& b) const;
};

template <>
struct equal_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const;
};

constexpr const equal_data_members<> data_members_equal = {};
//]
//[refltool_not_equal_data_members
template <typename T = void>
struct not_equal_data_members
{
	constexpr bool operator()(const T& a, const T& b) const;
};

template <>
struct not_equal_data_members<void>
{
	template <typename T>
	constexpr bool operator()(const T& a, const T& b) const;
};

constexpr const not_equal_data_members<> data_members_not_equal = {};
//]

