/**
 * @file mirror/range.hpp
 * @brief Declaration of the compile-time basic_range and range
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_RANGE_1105240825_HPP
#define MIRROR_RANGE_1105240825_HPP

namespace mirror {

template <typename ... P>
struct range
{
	using type = range;
};

using empty_range = range<> ;

} // namespace mirror

#endif //include guard

