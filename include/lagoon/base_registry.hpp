/**
 * @file lagoon/base_registry.hpp
 * @brief Declaration of the `base_registry` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_BASE_REGISTRY_1105240825_HPP
#define LAGOON_BASE_REGISTRY_1105240825_HPP

#include "metaobject.hpp"
#include "fingerprint.hpp"
#include <cstdint>
#include <map>

namespace lagoon {

class base_registry
{
protected:
	std::map<fingerprint, shared_metaobject> _mos;

	base_registry(void) = default;
public:
	const shared_metaobject& get_none(void) const;
	const shared_metaobject_sequence& get_none_seq(void) const;

	shared_metaobject get_proxy(fingerprint n);
	shared_metaobject get(fingerprint n);
	shared_metaobject find(fingerprint n);
};

} // namespace lagoon

#include <lagoon/base_registry.inl>

#endif //include guard

