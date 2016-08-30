/**
 * @file lagoon/any_constant.hpp
 * @brief Declaration of any_constant type erasure
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_ANY_CONSTANT_1105240825_HPP
#define LAGOON_ANY_CONSTANT_1105240825_HPP

#include <type_traits>
#include <cstdint>

namespace lagoon {

using raw_const_t = std::uint64_t;

class any_constant
{
private:
	raw_const_t _v;

	template <typename T>
	static constexpr bool _is_compatible =
		std::is_integral<T>::value ||
		std::is_enum<T>::value;

	template <typename T>
	using _underlying_type = std::conditional_t<
		std::is_enum<T>::value,
		std::underlying_type_t<T>, T
	>;

	// TODO: some kind of type-info
public:

	constexpr inline
	any_constant(void)
	noexcept
	 : _v{0}
	{ }

	template <
		typename Src,
		typename = std::enable_if_t<_is_compatible<Src>>
	>
	constexpr inline
	any_constant(Src v)
	 : _v{static_cast<raw_const_t>(static_cast<_underlying_type<Src>>(v))}
	{ }

	constexpr inline
	raw_const_t get(void) const
	noexcept
	{
		return _v;
	}

	template <
		typename Dst,
		typename = std::enable_if_t<_is_compatible<Dst>>
	> constexpr inline
	Dst as(void) const
	{
		return static_cast<Dst>(static_cast<_underlying_type<Dst>>(_v));
	}
};

} // namespace lagoon

#endif //include guard

