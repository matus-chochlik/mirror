/**
 * .file lagoon/member_sequence.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
namespace lagoon {

#include <lagoon/none_metaobject.hpp>

inline
member_metaobject_sequence::
member_metaobject_sequence(
	_aux::flat_set<fingerprint>& mems,
	base_registry& reg
) noexcept
 : _reg(reg)
 , _mems(mems)
{ }

inline
bool
member_metaobject_sequence::is_none(void) const
{
	return false;
}

inline
metaobject_sequence::size_type
member_metaobject_sequence::get_size(void)
{
	return size_type(_mems.size());
}

inline
shared_metaobject
member_metaobject_sequence::get_element(size_type i)
{
	if(i < _mems.size()) {
		return _reg.get(_mems[i]);
	}
	return none_metaobject::get_single();
}

} // namespace lagoon
