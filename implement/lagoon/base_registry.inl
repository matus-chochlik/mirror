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

namespace lagoon {

inline
base_registry::base_registry(void)
 : _nmo(make_shared_metaobject<none_metaobject>(*this))
 , _nmos(make_shared_metaobject_sequence<none_metaobject_sequence>(*this))
{ }

inline
const shared_metaobject&
base_registry::get_none(void) const
{
	return _nmo;
}

inline
const shared_metaobject_sequence&
base_registry::get_none_seq(void) const
{
	return _nmos;
}

inline
shared_metaobject
base_registry::get_proxy(const mirror::fingerprint& n)
{
	return std::shared_ptr<metaobject>(
		std::make_shared<proxy_metaobject>(n, *this)
	);
}

inline
shared_metaobject
base_registry::get(const mirror::fingerprint& n)
{
	auto p = _mos.find(n);
	if (p == _mos.end()) {
		return get_proxy(n);
	}
	return p->second;
}

inline
shared_metaobject
base_registry::find(const mirror::fingerprint& n)
{
	auto p = _mos.find(n);
	if (p == _mos.end()) {
		return get_none();
	}
	return p->second;
}

} // namespace lagoon
