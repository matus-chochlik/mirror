/**
 * @file mire/ct/starts_with.hpp
 * @brief Implementation of the starts_with meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_STARTS_WITH_1105240825_HPP
#define MIRE_CT_STARTS_WITH_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/head.hpp>
#include <mire/ct/size.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range1, typename Range2>
struct starts_with
 : equal<
	head<Range1, size<Range2>>,
	Range2
> { };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

