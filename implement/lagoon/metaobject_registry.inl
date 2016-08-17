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

namespace lagoon {

template <typename MO>
inline
shared_metaobject
metaobject_registry::reg(MO pmo)
{
	static_assert(mirror::is_metaobject<MO>::value, "");
		auto i = mirror::get_fingerprint<MO>;
		auto p = _mos.find(i);
		if (p == _mos.end())
		{
			auto mo = std::make_shared<concrete_metaobject>(
				pmo, *this
			);
			p = _mos.emplace(i, mo).first;
		}
		return p->second;
}

inline
shared_metaobject
metaobject_registry::reg(mirror::none)
{
	return get_none();
}

template <typename MOS>
inline
shared_metaobject_sequence
metaobject_registry::get_seq(MOS pmos)
{
	static_assert(mirror::is_metaobject_sequence<MOS>::value, "");
	return std::shared_ptr<metaobject_sequence>(
		std::make_shared<concrete_metaobject_sequence>(
			pmos, *this
		)
	);
}

inline
shared_metaobject_sequence
metaobject_registry::get_seq(mirror::none)
{
	return get_none_seq();
}

} // namespace lagoon
