/**
 * .file lagoon/metaobject_registry.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/concrete_metaobject.hpp>
#include <lagoon/concrete_sequence.hpp>
#include <mirror/traits.hpp>
#include <mirror/unpack.hpp>
#include <mirror/get_base_classes.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_enumerators.hpp>

namespace lagoon {

inline
shared_metaobject
metaobject_registry::reg(mirror::none)
{
	return get_none();
}

template <typename MO>
inline
shared_metaobject
metaobject_registry::reg(fingerprint fp, MO pmo)
{
	static_assert(mirror::is_metaobject<MO>::value, "");
	auto p = _mos.find(fp);
	if (p == _mos.end())
	{
		auto mo = make_shared_metaobject<concrete_metaobject<MO>>(
			pmo, *this
		);
		p = _mos.emplace(fp, mo).first;
	}
	return p->second;
}

template <typename MO>
inline
shared_metaobject
metaobject_registry::reg(MO pmo)
{
	return reg(get_fingerprint(pmo), pmo);
}

template <typename ... MO>
inline
void
metaobject_registry::reg_range(mirror::range<MO...>)
{
	_eat(reg(MO{})...);
}

template <typename PMO, typename ... MO>
inline
void
metaobject_registry::reg_inh_range(PMO pmo, mirror::range<MO...>)
{
	_eat(reg(get_fingerprint(pmo, mirror::get_base_class<MO>{}), MO{})...);
}

template <typename MO>
inline
void
metaobject_registry::reg_base_classes(MO pmo)
{
	reg_inh_range(pmo, mirror::unpack<mirror::get_base_classes<MO>>{});
}

template <typename MO>
inline
void
metaobject_registry::reg_data_members(MO)
{
	reg_range(mirror::unpack<mirror::get_data_members<MO>>{});
}

template <typename MO>
inline
void
metaobject_registry::reg_member_types(MO)
{
	reg_range(mirror::unpack<mirror::get_member_types<MO>>{});
}

template <typename MO>
inline
void
metaobject_registry::reg_enumerators(MO)
{
	reg_range(mirror::unpack<mirror::get_enumerators<MO>>{});
}

inline
shared_metaobject_sequence
metaobject_registry::get_seq(mirror::none)
{
	return get_none_seq();
}

template <typename MOS>
inline
shared_metaobject_sequence
metaobject_registry::make_seq(MOS mos)
{
	static_assert(
		mirror::is_none<MOS>::value ||
		mirror::is_metaobject_sequence<MOS>::value,
	"");
	return make_shared_sequence<concrete_metaobject_sequence>(
		mos, *this
	);
}

template <typename PMO, typename MOS>
inline
shared_metaobject_sequence
metaobject_registry::make_inh_seq(PMO pmo, MOS mos)
{
	static_assert(
		mirror::is_none<MOS>::value ||
		mirror::is_metaobject_sequence<MOS>::value,
	"");
	return make_shared_sequence<concrete_inh_metaobject_sequence>(
		pmo, mos, *this
	);
}

} // namespace lagoon
