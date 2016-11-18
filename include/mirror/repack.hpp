/**
 * @file mirror/repack.hpp
 * @brief Implementation of the `repack` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_REPACK_1105240825_HPP
#define MIRROR_REPACK_1105240825_HPP

#include "metaobject.hpp"
#include "identity.hpp"
#include "range.hpp"
#include "none.hpp"
#include "unpack.hpp"

namespace mirror {
namespace _aux {

template <typename X, template <class...> class Package>
struct op_repack;

template <template <class...> class Package>
struct op_repack<none, Package>
 : identity<Package<>>
{ };

template <typename ... P, template <class...> class Package>
struct op_repack<range<P...>, Package>
 : identity<Package<P...>>
{ };

} // namespace _aux

template <typename X, template <class...> class Package>
using repack = eval<_aux::op_repack<unpack<X>, Package>>;

} // namespace mirror

#endif //include guard

