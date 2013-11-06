/**
 * @file mire/ct/skip_front.hpp
 * @brief Implementation of the skip_front meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_SKIP_FRONT_1105240825_HPP
#define MIRE_CT_SKIP_FRONT_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/tail.hpp>
#include <mire/ct/size.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range, typename Size>
struct skip_front
 : tail<
	typename Range::type,
	integral_constant<
		size_t,
		size<Range>::value - Size::value
	>
> { };

template <typename Range, size_t Count>
struct skip_front_c
 : skip_front<
	typename Range::type,
	integral_constant<size_t, Count>
>{ };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

