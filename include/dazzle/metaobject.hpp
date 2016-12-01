/**
 * @file dazzle/metaobject.hpp
 * @brief Declaration of metaobject and metaobject sequences
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_METAOBJECT_1105240825_HPP
#define DAZZLE_METAOBJECT_1105240825_HPP

#include <mirror/metaobject.hpp>
#include <mirror/traits.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_full_name.hpp>
#include <mirror/get_display_name.hpp>
#include <mirror/get_aliased.hpp>
#include <mirror/get_type.hpp>
#include <mirror/get_scope.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_public_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_public_member_types.hpp>
#include <mirror/get_base_classes.hpp>
#include <mirror/get_public_base_classes.hpp>
#include <mirror/get_base_class.hpp>
#include <mirror/get_constant.hpp>
#include <mirror/get_pointer.hpp>
#include <mirror/dereference.hpp>

#include <mirror/get_elaborated_type_specifier.hpp>
#include <mirror/get_access_specifier.hpp>

#include <mirror/is_private.hpp>
#include <mirror/is_protected.hpp>
#include <mirror/is_public.hpp>
#include <mirror/is_static.hpp>
#include <mirror/is_virtual.hpp>
#include <mirror/is_class.hpp>
#include <mirror/is_struct.hpp>
#include <mirror/is_union.hpp>
#include <mirror/is_enum.hpp>
#include <mirror/is_scoped_enum.hpp>

#include <mirror/get_reflected_type.hpp>

#include "sequence_ops.hpp"
#include "type.hpp"

namespace dazzle {

template <typename MO>
struct wrapped<mirror::metaobject<MO>>
{
	using impl = mirror::metaobject<MO>;

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_base_name)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_full_name)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_display_name)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_aliased)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_type)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_scope)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_enumerators)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_data_members)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_public_data_members)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_member_types)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_public_member_types)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_base_classes)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_public_base_classes)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_base_class)

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_constant)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_pointer)

	template <typename T>
	static constexpr auto& dereference(T& inst) {
		return mirror::dereference<impl>::apply(inst);
	}

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_elaborated_type_specifier)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_access_specifier)

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_private)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_protected)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_public)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_static)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_virtual)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_class)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_struct)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_union)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_enum)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_scoped_enum)

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_reflected_type)
};

template <typename MoS>
struct wrapped<mirror::metaobject_sequence<MoS>>
 : sequence_ops<mirror::metaobject_sequence<MoS>>
{ };

} // namespace dazzle

#endif //include guard

