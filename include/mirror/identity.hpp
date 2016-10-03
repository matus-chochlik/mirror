/**
 * @file mirror/identity.hpp
 * @brief Identity template returning the type passed * as argument.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IDENTITY_1105240825_HPP
#define MIRROR_IDENTITY_1105240825_HPP

namespace mirror {

template <typename T>
struct identity
{
	using type = T;
};

template <typename X>
using eval = typename X::type;

} // namespace mirror

#endif //include guard

