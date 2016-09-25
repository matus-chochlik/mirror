/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[lagoon_shared_metaobject_1
class shared_metaobject
{
public:
	bool is_none(void) const;

	explicit operator bool (void) const; /*< Same as [^!is_none();] >*/
	bool operator ! (void) const /*< Same as [^is_none();] >*/

	__tribool has_source_info (void) const;
	tribool reflects_specifier (void) const;
	tribool reflects_global_scope (void) const;
	tribool reflects_namespace (void) const;
	tribool reflects_type (void) const;
	tribool reflects_alias (void) const;
	tribool reflects_variable (void) const;
	tribool reflects_constant (void) const;
	tribool reflects_enum_member (void) const;
	tribool reflects_record_member (void) const;
	tribool reflects_inheritance (void) const;

	__tribool is_anonymous (void) const;
	tribool is_class (void) const;
	tribool is_struct (void) const;
	tribool is_union (void) const;
	tribool is_enum (void) const;
	tribool is_scoped_enum (void) const;
	tribool is_static (void) const;
	tribool is_virtual (void) const;

	std::string_view get_source_file(void) const;
	unsigned get_source_line(void) const;
	unsigned get_source_column(void) const;

	std::string_view get_base_name(void) const;
	std::string_view get_full_name(void) const;
	std::string_view get_display_name(void) const;

	any_constant get_constant(void) const;

	shared_metaobject get_type(void) const;
	shared_metaobject get_scope(void) const;
	shared_metaobject get_aliased(void) const;
	shared_metaobject get_base_class(void) const;

	shared_metaobject get_elaborated_type_specifier(void) const;
	shared_metaobject get_access_specifier(void) const;

	__shared_metaobject_sequence get_base_classes(void) const;
	shared_metaobject_sequence get_data_members(void) const;
	shared_metaobject_sequence get_member_types(void) const;
	shared_metaobject_sequence get_enumerators(void) const;

	shared_metaobject_sequence get_members(void) const;
};
//]
//[lagoon_shared_metaobject_sequence_1
class shared_metaobject_sequence
{
public:
	using size_type = __unspecified;
	using iterator = __unspecified;

	bool is_none(void) const;

	explicit operator bool (void) const;

	bool operator ! (void) const;

	size_type get_size(void) const;
	size_type size(void) const; /*< Same as [^get_size] >*/

	bool is_empty(void) const;
	bool empty(void) const; /*< Same as [^is_empty] >*/

	__shared_metaobject get_element(size_type i) const;
	shared_metaobject at(size_type i) const;

	iterator begin(void) const;
	iterator end(void) const;
};
//]

