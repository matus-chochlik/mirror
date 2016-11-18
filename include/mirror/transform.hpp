/**
 * @file mirror/transform.hpp
 * @brief Implementation of the `transform` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TRANSFORM_1105240825_HPP
#define MIRROR_TRANSFORM_1105240825_HPP

#include "identity.hpp"
#include "metaobject.hpp"
#include "int_const.hpp"
#include "string.hpp"
#include "range.hpp"
#include "none.hpp"
#include "unpack.hpp"

namespace mirror {
namespace _aux {

template <typename X, template <class> class Transf>
struct op_transform;

template <template <class> class Transf>
struct op_transform<none, Transf>
 : none
{ };

template <typename ... P, template <class> class Transf>
struct op_transform<range<P...>, Transf>
 : range<Transf<P>...>
{ };

template <typename Char, Char ... C, template <class> class Transf>
struct op_transform<basic_string<Char, C...>, Transf>
 : basic_string<Char, Transf<int_const<Char, C>>::value...>
{ };

template <typename MoS, template <class> class Transf>
struct op_transform<metaobject_sequence<MoS>, Transf>
 : op_transform<unpack<metaobject_sequence<MoS>>, Transf>
{ };

} // namespace _aux

template <typename X, template <class> class Transf>
using transform = eval<_aux::op_transform<X, Transf>>;

} // namespace mirror

#endif //include guard

