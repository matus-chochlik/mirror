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

namespace lagoon {

class metaobject_registry
 : public base_registry
{
public:
	template <typename MO>
	shared_metaobject reg(MO);

	shared_metaobject reg(mirror::none);

	template <typename MOS>
	shared_metaobject_sequence get_seq(MOS);

	shared_metaobject_sequence get_seq(mirror::none);
};

} // namespace lagoon

#include <lagoon/metaobject_registry.inl>

#endif //include guard

