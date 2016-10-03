/**
 * @file mire/ct/contains.hpp
 * @brief Implementation of the contains meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_CONTAINS_1105240825_HPP
#define MIRE_CT_CONTAINS_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/find.hpp>
#include <mire/ct/empty.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range1, typename Range2>
struct contains
 : nonempty<find<Range1, Range2>>
{ };

template <typename Range1, typename Range2>
struct lacks
 : empty<find<Range1, Range2>>
{ };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

