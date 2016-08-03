/**
 * @file mire/ct/skip.hpp
 * @brief Implementation of the skip meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_SKIP_1105240825_HPP
#define MIRE_CT_SKIP_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/tail.hpp>
#include <mire/ct/size.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range, typename Size>
struct skip
 : tail<
	typename Range::type,
	size_constant<size<Range>::value - Size::value>
> { };

template <typename Range, size_t Count>
struct skip_c
 : skip<
	typename Range::type,
	size_constant<Count>
>{ };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

