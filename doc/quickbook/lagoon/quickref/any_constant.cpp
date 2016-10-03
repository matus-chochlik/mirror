/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[lagoon_any_constant_1
class any_constant
{
public:
	constexpr inline
	any_constant(void)
	noexcept;

	template <typename Src /*< Integral or enum type >*/>
	constexpr inline
	any_constant(Src v);

	using value_type = __unspecified /*<
	As least 64-bit wide unsigned integral type.
	>*/; 

	constexpr inline
	value_type get(void) const
	noexcept;

	template <typename Dst /*<
	Integral or enum type. This must be the same type which was used
	to initialize the [^any_constant], otherwise the result is undefined.
	>*/>
	constexpr inline
	Dst as(void) const;
};
//]

