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
#include <puddle/traits.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_scoped_ops.hpp>
#include <puddle/meta_enum_ops.hpp>
#include <puddle/meta_record_ops.hpp>
#include <puddle/reflection.hpp>

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
metaobject_registry::reg(fingerprint fp, MO mo)
{
	static_assert(puddle::is_metaobject(mo), "");
	auto p = _mos.find(fp);
	if (p == _mos.end())
	{
		auto smo = make_shared_metaobject<concrete_metaobject<MO>>(
			mo, *this
		);
		p = _mos.emplace(fp, smo).first;

		auto scmo = puddle::get_scope(mo);

		if(puddle::is_none(scmo))
		{
			if(
				!puddle::reflects_specifier(mo) &&
				!puddle::reflects_inheritance(mo) &&
				!puddle::reflects_global_scope(mo)
			)
			{
				auto gsco = PUDDLED(::);
				_mems[get_fingerprint(gsco)].insert(fp);
			}
		}
		else
		{
			_mems[get_fingerprint(scmo)].insert(fp);
		}
	}
	return p->second;
}

template <typename MO>
inline
shared_metaobject
metaobject_registry::reg(MO mo)
{
	return reg(get_fingerprint(mo), mo);
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
	_eat(reg(get_fingerprint(pmo, puddle::get_base_class(MO{})), MO{})...);
}

template <typename MO>
inline
void
metaobject_registry::reg_base_classes(MO pmo)
{
	reg_inh_range(pmo, puddle::unpack(puddle::get_base_classes(pmo)));
}

template <typename MO>
inline
void
metaobject_registry::reg_data_members(MO mo)
{
	reg_range(puddle::unpack(puddle::get_data_members(mo)));
}

template <typename MO>
inline
void
metaobject_registry::reg_member_types(MO mo)
{
	reg_range(puddle::unpack(puddle::get_member_types(mo)));
}

template <typename MO>
inline
void
metaobject_registry::reg_enumerators(MO mo)
{
	reg_range(puddle::unpack(puddle::get_enumerators(mo)));
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
		puddle::is_none(mos) ||
		puddle::is_metaobject_sequence(mos),
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
		puddle::is_none(mos) ||
		puddle::is_metaobject_sequence(mos),
	"");
	return make_shared_sequence<concrete_inh_metaobject_sequence>(
		pmo, mos, *this
	);
}

} // namespace lagoon
