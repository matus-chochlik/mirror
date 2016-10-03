/**
 * .file lagoon/none_sequence.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/none_metaobject.hpp>

namespace lagoon {

inline
shared_metaobject_sequence&
none_metaobject_sequence::get_single(void)
{
	static shared_metaobject_sequence s(
		make_shared_sequence<none_metaobject_sequence>()
	);
	return s;
}

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
	return none_metaobject::get_single();
}

} // namespace lagoon
