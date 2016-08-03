/**
 *  @file mire/mirror/base_name.hpp
 *  @brief Implementation of the base_name metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_BASE_NAME_1310291537_HPP
#define MIRE_MIRROR_BASE_NAME_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/ct/to_string.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M>
struct base_name<meta<R, M>>
 : ct::to_string<typename R::base_name>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
