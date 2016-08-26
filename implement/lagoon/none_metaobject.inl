/**
 * .file lagoon/none_metaobject.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/none_sequence.hpp>

namespace lagoon {

inline
shared_metaobject& none_metaobject::get_single(void)
{
	static shared_metaobject s(
		make_shared_metaobject<none_metaobject>()
	);
	return s;
}

inline
bool
none_metaobject::is_none(void) const
{
	return true;
}

inline
fingerprint
none_metaobject::get_fingerprint(void)
{
	return {};
}

inline
const metaobject_traits*
none_metaobject::traits(void)
{
	return nullptr;
}

inline
std::string_view
none_metaobject::get_source_file(void)
{
	return {};
}

inline
unsigned
none_metaobject::get_source_line(void)
{
	return 0;
}

inline
unsigned
none_metaobject::get_source_column(void)
{
	return 0;
}

inline
std::string_view
none_metaobject::get_base_name(void)
{
	return {};
}

inline
std::string_view
none_metaobject::get_full_name(void)
{
	return {};
}

inline
std::string_view
none_metaobject::get_display_name(void)
{
	return {};
}

inline
shared_metaobject
none_metaobject::get_type(void)
{
	return get_single();
}

inline
shared_metaobject
none_metaobject::get_scope(void)
{
	return get_single();
}

inline
shared_metaobject
none_metaobject::get_aliased(void)
{
	return get_single();
}

inline
shared_metaobject
none_metaobject::get_base_class(void)
{
	return get_single();
}

inline
shared_metaobject
none_metaobject::get_elaborated_type_specifier(void)
{
	return get_single();
}

inline
shared_metaobject
none_metaobject::get_access_specifier(void)
{
	return get_single();
}

inline
shared_metaobject_sequence
none_metaobject::get_base_classes(void)
{
	return none_metaobject_sequence::get_single();
}

inline
shared_metaobject_sequence
none_metaobject::get_data_members(void)
{
	return none_metaobject_sequence::get_single();
}

inline
shared_metaobject_sequence
none_metaobject::get_member_types(void)
{
	return none_metaobject_sequence::get_single();
}

inline
shared_metaobject_sequence
none_metaobject::get_enumerators(void)
{
	return none_metaobject_sequence::get_single();
}

inline
shared_metaobject_sequence
none_metaobject::get_members(void)
{
	return none_metaobject_sequence::get_single();
}

} // namespace lagoon
