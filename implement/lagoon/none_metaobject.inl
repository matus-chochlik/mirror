/**
 * .file lagoon/none_metaobject.inl
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
none_metaobject::is_none(void) const
{
	return true;
}

inline
const metaobject_traits&
none_metaobject::traits(void)
{
	return _ts;
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
	return _reg.get_none();
}

inline
shared_metaobject
none_metaobject::get_scope(void)
{
	return _reg.get_none();
}

inline
shared_metaobject
none_metaobject::get_aliased(void)
{
	return _reg.get_none();
}

inline
shared_metaobject_sequence
none_metaobject::get_base_classes(void)
{
	return _reg.get_none_seq();
}

inline
shared_metaobject_sequence
none_metaobject::get_data_members(void)
{
	return _reg.get_none_seq();
}

inline
shared_metaobject_sequence
none_metaobject::get_member_types(void)
{
	return _reg.get_none_seq();
}

inline
shared_metaobject_sequence
none_metaobject::get_enumerators(void)
{
	return _reg.get_none_seq();
}

} // namespace lagoon
