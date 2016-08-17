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

#include <mirror/traits.hpp>

namespace lagoon {

struct metaobject_traits
{
	bool reflects_specifier    : 1;
	bool reflects_global_scope : 1;
	bool reflects_namespace    : 1;
	bool reflects_type         : 1;
	bool reflects_variable     : 1;
	bool reflects_enum_member  : 1;
	bool reflects_record_member: 1;
	bool reflects_inheritance  : 1;

	constexpr
	metaobject_traits(mirror::none = {})
	noexcept
	 : reflects_specifier{false}
	 , reflects_global_scope{false}
	 , reflects_namespace{false}
	 , reflects_type{false}
	 , reflects_variable{false}
	 , reflects_enum_member{false}
	 , reflects_record_member{false}
	 , reflects_inheritance{false}
	{ }

	template <typename MO>
	constexpr
	metaobject_traits(MO)
	noexcept
	 : reflects_specifier{mirror::reflects_specifier<MO>{}}
	 , reflects_global_scope{mirror::reflects_global_scope<MO>{}}
	 , reflects_namespace{mirror::reflects_namespace<MO>{}}
	 , reflects_type{mirror::reflects_type<MO>{}}
	 , reflects_variable{mirror::reflects_variable<MO>{}}
	 , reflects_enum_member{mirror::reflects_enum_member<MO>{}}
	 , reflects_record_member{mirror::reflects_record_member<MO>{}}
	 , reflects_inheritance{mirror::reflects_inheritance<MO>{}}
	{ }
};

} // namespace lagoon

#endif //include guard

