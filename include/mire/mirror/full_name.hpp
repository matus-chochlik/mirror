/**
 *  @file mire/mirror/full_name.hpp
 *  @brief Implementation of the full_name metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_FULL_NAME_1310291537_HPP
#define MIRE_MIRROR_FULL_NAME_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/mirror/make_name.hpp>
#include <mire/ct/to_string.hpp>

namespace mire {
namespace mirror {
namespace _aux {

template <typename Reg>
struct get_full_name
 : ct::to_string<typename Reg::full_name>
{ };

} // namespace _aux

template <typename R, typename M>
struct full_name<meta<R, M>>
 : _aux::make_name<_aux::get_full_name, meta<R, M>>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
