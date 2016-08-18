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
public:
	shared_metaobject reg(mirror::none);

	template <typename MO>
	shared_metaobject reg(MO);

	void reg_range(mirror::none) { }

	template <typename ... MO>
	void reg_range(mirror::range<MO...>);

	template <typename MO>
	void reg_base_classes(MO);

	template <typename MO>
	void reg_data_members(MO);

	template <typename MO>
	void reg_member_types(MO);

	template <typename MO>
	void reg_enumerators(MO);

	shared_metaobject_sequence get_seq(mirror::none);

	template <typename MOS>
	shared_metaobject_sequence get_seq(MOS);
};

} // namespace lagoon

#include <lagoon/metaobject_registry.inl>

#endif //include guard

