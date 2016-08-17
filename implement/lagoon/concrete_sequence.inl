/**
 * .file lagoon/concrete_sequence.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/base_registry.hpp>
#include <mirror/unpack.hpp>

namespace lagoon {

template <typename ... MO>
inline
std::vector<shared_metaobject>
concrete_metaobject_sequence::
_make_vec(mirror::range<MO...>, base_registry& reg)
{
	return {reg.get(mirror::get_fingerprint<MO>)...};
}

template <typename MOS>
inline
concrete_metaobject_sequence::
concrete_metaobject_sequence(MOS, base_registry& reg)
noexcept
 : _reg(reg)
 , _mos(_make_vec(mirror::unpack<MOS>{}, reg))
{
	static_assert(mirror::is_metaobject_sequence<MOS>::value, "");
}

inline
bool
concrete_metaobject_sequence::is_none(void) const
{
	return false;
}

inline
metaobject_sequence::size_type
concrete_metaobject_sequence::get_size(void)
{
	return size_type(_mos.size());
}

inline
shared_metaobject
concrete_metaobject_sequence::get_element(size_type i)
{
	if(i < size_type(_mos.size())) {
		return _mos[i];
	}
	return _reg.get_none();
}

} // namespace lagoon
