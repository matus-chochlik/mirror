/**
 * @file lagoon/none_sequence.hpp
 * @brief Declaration of the `none_metaobject_sequence` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_NONE_METAOBJECT_SEQUENCE_1105240825_HPP
#define LAGOON_NONE_METAOBJECT_SEQUENCE_1105240825_HPP

#include "metaobject.hpp"

namespace lagoon {

class base_registry;

class none_metaobject_sequence
 : public metaobject_sequence
{
public:
	static shared_metaobject_sequence& get_single(void);

	bool is_none(void) const
	override;

	size_type get_size(void)
	override;

	shared_metaobject get_element(size_type)
	override;
};

} // namespace lagoon

#include <lagoon/none_sequence.inl>

#endif //include guard

