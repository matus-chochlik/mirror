/**
 * @file lagoon/metaobject_traits.hpp
 * @brief Declaration of the `metaobject_registry` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_METAOBJECT_TRAITS_1105240825_HPP
#define LAGOON_METAOBJECT_TRAITS_1105240825_HPP

#include <mirror/none.hpp>

namespace lagoon {

struct metaobject_traits
{
	bool has_source_info        : 1;
	bool reflects_specifier     : 1;
	bool reflects_global_scope  : 1;
	bool reflects_namespace     : 1;
	bool reflects_type          : 1;
	bool reflects_tag_type      : 1;
	bool reflects_record        : 1;
	bool reflects_class         : 1;
	bool reflects_enum          : 1;
	bool reflects_alias         : 1;
	bool reflects_variable      : 1;
	bool reflects_constant      : 1;
	bool reflects_enum_member   : 1;
	bool reflects_record_member : 1;
	bool reflects_inheritance   : 1;

	bool is_anonymous   : 1;
	bool is_class       : 1;
	bool is_struct      : 1;
	bool is_union       : 1;
	bool is_enum        : 1;
	bool is_scoped_enum : 1;
	bool is_static      : 1;
	bool is_virtual     : 1;

	constexpr
	metaobject_traits(mirror::none = {})
	noexcept;

	template <typename MO>
	constexpr
	metaobject_traits(MO)
	noexcept;
};

} // namespace lagoon

#include <lagoon/metaobject_traits.inl>

#endif //include guard

