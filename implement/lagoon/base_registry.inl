/**
 * .file lagoon/base_registry.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/none_metaobject.hpp>
#include <lagoon/none_sequence.hpp>
#include <lagoon/proxy_metaobject.hpp>
#include <lagoon/member_sequence.hpp>
#include <algorithm>

namespace lagoon {
namespace _aux {

template <typename T>
inline
void
flat_set<T>::insert(T v)
{
	auto i = std::lower_bound(_v.begin(), _v.end(), v);
	if((i == _v.end()) || (*i != v))
	{
		_v.insert(i, std::move(v));
	}
}

} // namespace _aux

inline
const shared_metaobject&
base_registry::get_none(void) const
{
	return none_metaobject::get_single();
}

inline
const shared_metaobject_sequence&
base_registry::get_none_seq(void) const
{
	return none_metaobject_sequence::get_single();
}

inline
shared_metaobject
base_registry::get_proxy(fingerprint n)
{
	return make_shared_metaobject<proxy_metaobject>(n, *this);
}

inline
shared_metaobject
base_registry::get(fingerprint n)
{
	auto p = _mos.find(n);
	if (p == _mos.end()) {
		return get_proxy(n);
	}
	return p->second;
}

inline
shared_metaobject
base_registry::find(fingerprint n)
{
	auto p = _mos.find(n);
	if (p == _mos.end()) {
		return get_none();
	}
	return p->second;
}

inline
shared_metaobject_sequence
base_registry::make_mem_seq(fingerprint n)
{
	return make_shared_sequence<member_metaobject_sequence>(_mems[n],*this);
}

} // namespace lagoon
