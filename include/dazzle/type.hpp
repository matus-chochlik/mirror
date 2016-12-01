/**
 * @file dazzle/type.hpp
 * @brief Declaration of type wrapper
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_TYPE_1105240825_HPP
#define DAZZLE_TYPE_1105240825_HPP

#include <mirror/identity.hpp>
#include "int_const.hpp"
#include "envelope.hpp"

namespace dazzle {

template <typename T>
struct wrapped<mirror::identity<T>>
{
	using impl = mirror::identity<T>;
};

template <typename T>
constexpr envelope<mirror::identity<T>> type = {};

template <typename T>
static constexpr inline
envelope<mirror::true_>
operator == (wrapped<mirror::identity<T>>, wrapped<mirror::identity<T>>)
noexcept { return {}; }

template <typename U, typename V>
static constexpr inline
envelope<mirror::false_>
operator == (wrapped<mirror::identity<U>>, wrapped<mirror::identity<V>>)
noexcept { return {}; }

template <typename T>
static constexpr inline
envelope<mirror::false_>
operator != (wrapped<mirror::identity<T>>, wrapped<mirror::identity<T>>)
noexcept { return {}; }

template <typename U, typename V>
static constexpr inline
envelope<mirror::true_>
operator != (wrapped<mirror::identity<U>>, wrapped<mirror::identity<V>>)
noexcept { return {}; }

} // namespace dazzle

#endif //include guard

