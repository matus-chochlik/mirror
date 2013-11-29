/**
 *  @file mire/mirror/named_typedef.hpp
 *  @brief Implementation of the named_typedef metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_NAMED_TYPEDEF_1310291537_HPP
#define MIRE_MIRROR_NAMED_TYPEDEF_1310291537_HPP

#include <mire/mirror/default.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M, typename X>
struct named_typedef<meta<R, M>, X>
{
	typedef typename R::template _named_typedef<X> type;
};

} // namespace mirror
} // namespace mire

#endif // include guard
