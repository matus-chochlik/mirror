/**
 * @file mirror/metaobject_ops.hpp
 * @brief Metaobject operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_METAOBJECT_OPS_1105240825_HPP
#define MIRROR_METAOBJECT_OPS_1105240825_HPP

#include "metaobject.hpp"
#include "identity.hpp"
#include "int_const.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename B, typename X, typename F, template <class> class Tpl>
struct op_make_metaobject_if;

template <typename Op, typename F, template <class> class Tpl>
struct op_make_metaobject_if<true_, Op, F, Tpl>
 : Tpl<eval<Op>>
{ };

template <typename X, typename F, template <class> class Tpl>
struct op_make_metaobject_if<false_, X, F, Tpl>
 : Tpl<F>
{ };

template <typename X, template <class> class Tpl>
struct op_make_metaobject_if<false_, X, none, Tpl>
 : none
{ };

} // namespace _aux

template <typename Bool, typename Op, typename F = none>
using make_metaobject_if =
	eval<_aux::op_make_metaobject_if<Bool, Op, F, metaobject>>;

template <typename Bool, typename Op, typename F = none>
using make_metaobject_sequence_if =
	eval<_aux::op_make_metaobject_if<Bool, Op, F, metaobject_sequence>>;

template <bool B, typename Op, typename F = none>
using make_metaobject_if_c =
	make_metaobject_if<bool_<B>, Op, F>;

template <bool B, typename Op, typename F = none>
using make_metaobject_sequence_if_c =
	make_metaobject_sequence_if<bool_<B>, Op, F>;

} // namespace mirror

#endif //include guard

