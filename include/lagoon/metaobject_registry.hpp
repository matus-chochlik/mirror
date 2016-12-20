/**
 * @file lagoon/metaobject_registry.hpp
 * @brief Declaration of the `metaobject_registry` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_METAOBJECT_REGISTRY_1105240825_HPP
#define LAGOON_METAOBJECT_REGISTRY_1105240825_HPP

#include "base_registry.hpp"
#include <mirror/none.hpp>
#include <mirror/range.hpp>

namespace lagoon {

class metaobject_registry
 : public base_registry
{
private:
	template <typename ... X>
	static void _eat(X ...) { }

	template <typename MO>
	shared_metaobject _add(fingerprint, MO);

	void _add_range(mirror::none) { }

	template <typename ... MO>
	void _add_range(mirror::range<MO...>);

	template <typename PMO>
	void _add_inh_range(PMO, mirror::none) { }

	template <typename PMO, typename ... MO>
	void _add_inh_range(PMO, mirror::range<MO...>);
public:
	shared_metaobject add(mirror::none);

	template <typename MO>
	shared_metaobject add(MO);

	template <typename MO>
	void add_base_classes(MO);

	template <typename MO>
	void add_data_members(MO);

	template <typename MO>
	void add_member_types(MO);

	template <typename MO>
	void add_enumerators(MO);

	shared_metaobject_sequence wrap_sequence(mirror::none);

	template <typename MOS>
	shared_metaobject_sequence wrap_sequence(MOS);

	template <typename PMO, typename MOS>
	shared_metaobject_sequence wrap_inheritance_sequence(PMO, MOS);
};

} // namespace lagoon

#include <lagoon/metaobject_registry.inl>

#endif //include guard

