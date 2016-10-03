/**
 * @file mire/ct/optional.hpp
 * @brief Compile-time optional type
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_OPTIONAL_1104130956_HPP
#define MIRE_CT_OPTIONAL_1104130956_HPP

#include <mire/ct/nil_type.hpp>

namespace mire {
namespace ct {

/// A single value container
/**
 *  @tparam T the element of the optional
 *  @see nil
 *  @see get
 *  @ingroup ct_utils
 */
template <typename T>
struct optional
{
	typedef optional type;
};

/// Convenience typedef for NIL optional
typedef optional<nil_t> nil_optional;

/// Convenience typedef for NIL optional
typedef optional<nil_t> empty_optional;

} // namespace ct
} // namespace mire

#endif //include guard

