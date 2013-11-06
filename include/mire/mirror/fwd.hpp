/**
 *  @file mire/mirror/fwd.hpp
 *  @brief Forward declarations.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRROR_FWD_1310291537_HPP
#define MIRROR_FWD_1310291537_HPP

namespace mirror {

template <typename X, typename M>
struct meta { };

template <typename X>
struct spec { };

template <typename T>
struct mirrored_t;

template <typename X>
struct category;

template <typename X>
struct keyword;

template <typename X>
struct base_name;

template <typename X>
struct full_name;

template <typename X, typename P>
struct named_typedef;

template <typename X, typename P>
struct named_mem_var;

template <typename X>
struct scope;

namespace _reg {

template <typename T>
struct _type_reg;

} // namespace _reg

namespace _aux {

template <typename X>
struct _get_meta;

} // namespace _aux

} // namespace mirror

#endif // include guard
