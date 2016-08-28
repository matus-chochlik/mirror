/**
 * .file lagoon/proxy_metaobject.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/base_registry.hpp>

namespace lagoon {

inline
bool
proxy_metaobject::is_none(void) const
{
	return _reg.find(_fpt).is_none();
}

inline
fingerprint
proxy_metaobject::get_fingerprint(void)
{
	return _fpt;
}

inline
const metaobject_traits*
proxy_metaobject::traits(void)
{
	return _reg.find(_fpt).traits();
}

inline
std::string_view
proxy_metaobject::get_source_file(void)
{
	return {};
}

inline
unsigned
proxy_metaobject::get_source_line(void)
{
	return 0;
}

inline
unsigned
proxy_metaobject::get_source_column(void)
{
	return 0;
}

inline
std::string_view
proxy_metaobject::get_base_name(void)
{
	return _reg.find(_fpt).get_base_name();
}

inline
std::string_view
proxy_metaobject::get_full_name(void)
{
	return _reg.find(_fpt).get_full_name();
}

inline
std::string_view
proxy_metaobject::get_display_name(void)
{
	return _reg.find(_fpt).get_display_name();
}

inline
raw_const_t
proxy_metaobject::get_raw_constant(void)
{
	return _reg.find(_fpt).get_raw_constant();
}

inline
shared_metaobject
proxy_metaobject::get_type(void)
{
	return _reg.find(_fpt).get_type();
}

inline
shared_metaobject
proxy_metaobject::get_scope(void)
{
	return _reg.find(_fpt).get_scope();
}

inline
shared_metaobject
proxy_metaobject::get_aliased(void)
{
	return _reg.find(_fpt).get_aliased();
}

inline
shared_metaobject
proxy_metaobject::get_base_class(void)
{
	return _reg.find(_fpt).get_aliased();
}

inline
shared_metaobject
proxy_metaobject::get_elaborated_type_specifier(void)
{
	return _reg.find(_fpt).get_elaborated_type_specifier();
}

inline
shared_metaobject
proxy_metaobject::get_access_specifier(void)
{
	return _reg.find(_fpt).get_access_specifier();
}

inline
shared_metaobject_sequence
proxy_metaobject::get_base_classes(void)
{
	return _reg.find(_fpt).get_base_classes();
}

inline
shared_metaobject_sequence
proxy_metaobject::get_data_members(void)
{
	return _reg.find(_fpt).get_data_members();
}

inline
shared_metaobject_sequence
proxy_metaobject::get_member_types(void)
{
	return _reg.find(_fpt).get_member_types();
}

inline
shared_metaobject_sequence
proxy_metaobject::get_enumerators(void)
{
	return _reg.find(_fpt).get_enumerators();
}

inline
shared_metaobject_sequence
proxy_metaobject::get_members(void)
{
	return _reg.find(_fpt).get_members();
}

} // namespace lagoon
