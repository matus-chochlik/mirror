/**
 * .file lagoon/metaobject.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/none_metaobject.hpp>

namespace lagoon {

inline
bool
shared_metaobject::is_none(void) const
{
	return _mo->is_none();
}

inline
const metaobject_traits*
shared_metaobject::traits(void) const
{
	return _mo->traits();
}

inline
std::string_view
shared_metaobject::get_source_file(void) const
{
	return _mo->get_source_file();
}

inline
unsigned
shared_metaobject::get_source_line(void) const
{
	return _mo->get_source_line();
}

inline
unsigned
shared_metaobject::get_source_column(void) const
{
	return _mo->get_source_column();
}

inline
std::string_view
shared_metaobject::get_base_name(void) const
{
	return _mo->get_base_name();
}

inline
std::string_view
shared_metaobject::get_full_name(void) const
{
	return _mo->get_full_name();
}

inline
std::string_view
shared_metaobject::get_display_name(void) const
{
	return _mo->get_display_name();
}

inline
shared_metaobject
shared_metaobject::get_type(void) const
{
	return _mo->get_type();
}

inline
shared_metaobject
shared_metaobject::get_scope(void) const
{
	return _mo->get_scope();
}

inline
shared_metaobject
shared_metaobject::get_aliased(void) const
{
	return _mo->get_aliased();
}

inline
shared_metaobject
shared_metaobject::get_base_class(void) const
{
	return _mo->get_base_class();
}

inline
shared_metaobject
shared_metaobject::get_access_specifier(void) const
{
	return _mo->get_access_specifier();
}

inline
shared_metaobject_sequence
shared_metaobject::get_base_classes(void) const
{
	return _mo->get_base_classes();
}

inline
shared_metaobject_sequence
shared_metaobject::get_data_members(void) const
{
	return _mo->get_data_members();
}

inline
shared_metaobject_sequence
shared_metaobject::get_member_types(void) const
{
	return _mo->get_member_types();
}

inline
shared_metaobject_sequence
shared_metaobject::get_enumerators(void) const
{
	return _mo->get_enumerators();
}

inline
shared_metaobject_sequence
shared_metaobject::get_members(void) const
{
	return _mo->get_members();
}

inline
bool
shared_metaobject_sequence::is_none(void) const
{
	return _mos->is_none();
}

inline
shared_metaobject_sequence::size_type
shared_metaobject_sequence::get_size(void) const
{
	return _mos->get_size();
}

inline
shared_metaobject
shared_metaobject_sequence::get_element(size_type i) const
{
	return _mos->get_element(i);
}

inline
shared_metaobject
shared_metaobject_sequence_iterator::_load(unsigned pos)
{
	return _seq().get_element(pos);
}

inline
shared_metaobject_sequence_iterator::
shared_metaobject_sequence_iterator(void)
noexcept
 : _psq(nullptr)
 , _pos(0)
 , _cur(none_metaobject::get_single())
{ }

inline
shared_metaobject_sequence_iterator::
shared_metaobject_sequence_iterator(
	const shared_metaobject_sequence& seq,
	unsigned pos
) noexcept
 : _psq(&seq)
 , _pos(pos)
 , _cur(_load(_pos))
{ }

inline
int shared_metaobject_sequence_iterator::difference(
	const shared_metaobject_sequence_iterator& a,
	const shared_metaobject_sequence_iterator& b
) noexcept
{
	return int(a._pos) - int(b._pos);
}
inline
void shared_metaobject_sequence_iterator::increment(void)
noexcept
{
	assert(_pos < _seq().get_size());
	_cur = _load(++_pos);
}

} // namespace lagoon
