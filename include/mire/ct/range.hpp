/**
 * @file mire/ct/range.hpp
 * @brief Declaration of the compile-time forward range
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_RANGE_1105240825_HPP
#define MIRE_CT_RANGE_1105240825_HPP

namespace mire {
namespace ct {

/// Range of types supporting forward traversal
/**
 *  @tparam P the pack of elements in the range
 *  @see empty
 *  @see size
 *  @see front
 *  @see next
 *  @see at
 *  @see at_c
 *  @ingroup ct_utils
 */
template <typename ... P>
struct range
{
	typedef range type;
};

/// Convenience typedef for empty range
typedef range<> empty_range;

} // namespace ct
} // namespace mire

#endif //include guard

