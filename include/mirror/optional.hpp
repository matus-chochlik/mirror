/**
 * @file mirror/optional.hpp
 * @brief Compile-time optional type
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_OPTIONAL_1105240825_HPP
#define MIRROR_OPTIONAL_1105240825_HPP

namespace mirror {

/// A single value container
/**
 *  @tparam T the element of the optional
 *  @see none
 *  @see get
 *  @ingroup ct_utils
 */
template <typename T>
struct optional
{
	typedef optional type;
};

/// Convenience typedef for empty optional
typedef optional<none> empty_optional;

} // namespace mirror

#endif //include guard

