/**
 *  @file mire/mirror/position.hpp
 *  @brief Implementation of the position metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_POSITION_1310291537_HPP
#define MIRE_MIRROR_POSITION_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/mirror/int_const.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M>
struct position<meta<R, M>>
 : integral_constant<size_t, size_t(R::position::value)>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
