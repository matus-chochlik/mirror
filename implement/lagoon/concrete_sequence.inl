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
#include <mirror/get_base_class.hpp>

namespace lagoon {

inline
concrete_metaobject_sequence_base::
concrete_metaobject_sequence_base(
	std::vector<shared_metaobject>&& mos,
	base_registry& reg
): _reg(reg)
 , _mos(std::move(mos))
{ }

inline
bool
concrete_metaobject_sequence_base::is_none(void) const
{
	return false;
}

inline
metaobject_sequence::size_type
concrete_metaobject_sequence_base::get_size(void)
{
	return size_type(_mos.size());
}

inline
shared_metaobject
concrete_metaobject_sequence_base::get_element(size_type i)
{
	if(i < size_type(_mos.size())) {
		return _mos[i];
	}
	return _reg.get_none();
}


template <typename ... MO>
inline
std::vector<shared_metaobject>
concrete_metaobject_sequence::
_make_vec(mirror::range<MO...>, base_registry& reg)
{
	return {reg.get(get_fingerprint(MO{}))...};
}

template <typename MOS>
inline
concrete_metaobject_sequence::
concrete_metaobject_sequence(MOS, base_registry& reg)
noexcept
 : concrete_metaobject_sequence_base(
	_make_vec(mirror::unpack<MOS>{}, reg),
	reg
) {
	static_assert(
		mirror::is_none<MOS>::value ||
		mirror::is_metaobject_sequence<MOS>::value,
	"");
}

template <typename PMO, typename ... MO>
inline
std::vector<shared_metaobject>
concrete_inh_metaobject_sequence::
_make_vec(PMO pmo, mirror::range<MO...>, base_registry& reg)
{
	return {reg.get(get_fingerprint(pmo, mirror::get_base_class<MO>{}))...};
}

template <typename PMO, typename MOS>
inline
concrete_inh_metaobject_sequence::
concrete_inh_metaobject_sequence(PMO pmo, MOS, base_registry& reg)
noexcept
 : concrete_metaobject_sequence_base(
	_make_vec(pmo, mirror::unpack<MOS>{}, reg),
	reg
) {
	static_assert(
		mirror::is_none<MOS>::value ||
		mirror::is_metaobject_sequence<MOS>::value,
	"");
}

} // namespace lagoon
