/**
 * .file lagoon/none_sequence.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/base_registry.hpp>

namespace lagoon {

inline
none_metaobject_sequence::
none_metaobject_sequence(base_registry& reg)
noexcept
 : _reg(reg)
{ }

inline
bool
none_metaobject_sequence::is_none(void) const
{
	return true;
}

inline
metaobject_sequence::size_type
none_metaobject_sequence::get_size(void)
{
	return 0;
}

inline
shared_metaobject
none_metaobject_sequence::get_element(size_type)
{
	return _reg.get_none();
}

} // namespace lagoon
