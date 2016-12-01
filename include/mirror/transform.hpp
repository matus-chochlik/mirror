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

template <template <class> class Transf, typename X>
struct op_transform;

template <template <class> class Transf>
struct op_transform<Transf, none>
 : none
{ };

template <template <class> class Transf, typename ... P>
struct op_transform<Transf, range<P...>>
 : range<Transf<P>...>
{ };

template <template <class> class Transf, typename Char, Char ... C>
struct op_transform<Transf, basic_string<Char, C...>>
 : basic_string<Char, Transf<int_const<Char, C>>::value...>
{ };

template <template <class> class Transf, typename MoS>
struct op_transform<Transf, metaobject_sequence<MoS>>
 : op_transform<Transf, unpack<metaobject_sequence<MoS>>>
{ };

} // namespace _aux

template <template <class> class Transf, typename X>
using transform = eval<_aux::op_transform<Transf, X>>;

} // namespace mirror

#endif //include guard

