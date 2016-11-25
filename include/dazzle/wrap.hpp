/**
 * @file dazzle/wrap.hpp
 * @brief Declaration of wrapped
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_WRAPPED_1105240825_HPP
#define DAZZLE_WRAPPED_1105240825_HPP

namespace dazzle {

template <typename X>
struct wrapped;

template <typename X>
static constexpr inline
wrapped<X> wrap(X)
noexcept { return {}; }

template <typename Func>
static constexpr inline
auto wrap_args_of(Func func)
{
	return [=](auto ... x) { return func(wrap(x)...); };
}


} // namespace dazzle

#endif //include guard

