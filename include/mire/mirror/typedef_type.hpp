/**
 *  @file mire/mirror/typedef_type.hpp
 *  @brief Implementation of the typedef_type metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_TYPEDEF_TYPE_1310291537_HPP
#define MIRE_MIRROR_TYPEDEF_TYPE_1310291537_HPP

#include <mire/mirror/default.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M>
struct typedef_type<meta<R, M>>
 : meta<typename R::typedef_type, M>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
