/**
 * @file mire/ct/ends_with.hpp
 * @brief Implementation of the ends_with meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ENDS_WITH_1105240825_HPP
#define MIRE_CT_ENDS_WITH_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/tail.hpp>
#include <mire/ct/size.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range1, typename Range2>
struct ends_with
 : equal<
	tail<Range1, size<Range2>>,
	Range2
> { };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

