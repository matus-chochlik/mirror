/**
 * .file lagoon/metaobject.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

namespace lagoon {

inline
bool
shared_metaobject::is_none(void) const
{
	return _mo->is_none();
}

inline
const metaobject_traits&
shared_metaobject::traits(void)
{
	return _mo->traits();
}

inline
std::string_view
shared_metaobject::get_base_name(void)
{
	return _mo->get_base_name();
}

inline
std::string_view
shared_metaobject::get_full_name(void)
{
	return _mo->get_full_name();
}

inline
std::string_view
shared_metaobject::get_display_name(void)
{
	return _mo->get_display_name();
}

inline
shared_metaobject
shared_metaobject::get_type(void)
{
	return _mo->get_type();
}

inline
shared_metaobject
shared_metaobject::get_scope(void)
{
	return _mo->get_scope();
}

inline
shared_metaobject
shared_metaobject::get_aliased(void)
{
	return _mo->get_aliased();
}

inline
shared_metaobject_sequence
shared_metaobject::get_base_classes(void)
{
	return _mo->get_base_classes();
}

inline
shared_metaobject_sequence
shared_metaobject::get_data_members(void)
{
	return _mo->get_data_members();
}

inline
shared_metaobject_sequence
shared_metaobject::get_member_types(void)
{
	return _mo->get_member_types();
}

inline
shared_metaobject_sequence
shared_metaobject::get_enumerators(void)
{
	return _mo->get_enumerators();
}

inline
bool
shared_metaobject_sequence::is_none(void) const
{
	return _mos->is_none();
}

inline
shared_metaobject_sequence::size_type
shared_metaobject_sequence::get_size(void)
{
	return _mos->get_size();
}

inline
shared_metaobject
shared_metaobject_sequence::get_element(size_type i)
{
	return _mos->get_element(i);
}

} // namespace lagoon
