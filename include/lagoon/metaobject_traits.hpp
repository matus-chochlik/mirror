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
#include <mirror/has_source_info.hpp>
#include <mirror/is_anonymous.hpp>
#include <mirror/is_class.hpp>
#include <mirror/is_struct.hpp>
#include <mirror/is_union.hpp>
#include <mirror/is_enum.hpp>
#include <mirror/is_scoped_enum.hpp>
#include <mirror/is_static.hpp>
#include <mirror/is_virtual.hpp>

namespace lagoon {

struct metaobject_traits
{
	bool has_source_info    : 1;
	bool reflects_specifier     : 1;
	bool reflects_global_scope  : 1;
	bool reflects_namespace     : 1;
	bool reflects_type          : 1;
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
	noexcept
	 : has_source_info{false}
	 , reflects_specifier{false}
	 , reflects_global_scope{false}
	 , reflects_namespace{false}
	 , reflects_type{false}
	 , reflects_alias{false}
	 , reflects_variable{false}
	 , reflects_constant{false}
	 , reflects_enum_member{false}
	 , reflects_record_member{false}
	 , reflects_inheritance{false}
	 , is_anonymous{false}
	 , is_class{false}
	 , is_struct{false}
	 , is_union{false}
	 , is_enum{false}
	 , is_scoped_enum{false}
	 , is_static{false}
	 , is_virtual{false}
	{ }

	template <typename MO>
	constexpr
	metaobject_traits(MO)
	noexcept
	 : has_source_info{mirror::has_source_info<MO>{}}
	 , reflects_specifier{mirror::reflects_specifier<MO>{}}
	 , reflects_global_scope{mirror::reflects_global_scope<MO>{}}
	 , reflects_namespace{mirror::reflects_namespace<MO>{}}
	 , reflects_type{mirror::reflects_type<MO>{}}
	 , reflects_alias{mirror::reflects_type<MO>{}}
	 , reflects_variable{mirror::reflects_variable<MO>{}}
	 , reflects_constant{mirror::reflects_constant<MO>{}}
	 , reflects_enum_member{mirror::reflects_enum_member<MO>{}}
	 , reflects_record_member{mirror::reflects_record_member<MO>{}}
	 , reflects_inheritance{mirror::reflects_inheritance<MO>{}}
	 , is_anonymous{mirror::is_anonymous<MO>{}}
	 , is_class{mirror::is_class<MO>{}}
	 , is_struct{mirror::is_struct<MO>{}}
	 , is_union{mirror::is_union<MO>{}}
	 , is_enum{mirror::is_enum<MO>{}}
	 , is_scoped_enum{mirror::is_scoped_enum<MO>{}}
	 , is_static{mirror::is_static<MO>{}}
	 , is_virtual{mirror::is_virtual<MO>{}}
	{ }
};

} // namespace lagoon

#endif //include guard

