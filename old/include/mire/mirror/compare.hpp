/**
 *  @file mire/mirror/compare.hpp
 *  @brief Implementation of the comparison metafunction
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_COMPARE_1310291537_HPP
#define MIRE_MIRROR_COMPARE_1310291537_HPP

#include <mire/ct/int_const.hpp>
#include <mire/mirror/fwd.hpp>
#include <mire/mirror/default.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M>
struct equal<meta<R, M>, meta<R, M>>
 : ct::true_type
{ };

template <typename R1, typename M1, typename R2, typename M2>
struct equal<meta<R1, M1>, meta<R2, M2>>
 : ct::false_type
{ };

template <typename R, typename M>
struct nonequal<meta<R, M>, meta<R, M>>
 : ct::false_type
{ };

template <typename R1, typename M1, typename R2, typename M2>
struct nonequal<meta<R1, M1>, meta<R2, M2>>
 : ct::true_type
{ };

template <typename T>
struct equal<spec<T>, spec<T>>
 : ct::true_type
{ };

template <typename T1, typename T2>
struct equal<spec<T1>, spec<T2>>
 : ct::false_type
{ };

template <typename T>
struct nonequal<spec<T>, spec<T>>
 : ct::false_type
{ };

template <typename T1, typename T2>
struct nonequal<spec<T1>, spec<T2>>
 : ct::true_type
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
