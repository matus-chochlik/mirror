/**
 * @file mire/ct/at.hpp
 * @brief Implementation of the at meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_AT_1105240825_HPP
#define MIRE_CT_AT_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/front.hpp>
#include <mire/ct/skip.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range, typename Position>
struct at
 : front<skip<Range, Position>>
{ };

template <typename Range, size_t Position>
struct at_c
 : front<skip_c<Range, Position>>
{ };

#endif // !MIRROR_DOCUMENTATION_ONLY

} // namespace ct
} // namespace mire

#endif //include guard

