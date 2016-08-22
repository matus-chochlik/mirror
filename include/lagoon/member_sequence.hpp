/**
 * @file lagoon/member_sequence.hpp
 * @brief Declaration of the `seq_ref_metaobject_sequence` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_MEMBER_SEQUENCE_1105240825_HPP
#define LAGOON_MEMBER_SEQUENCE_1105240825_HPP

#include "metaobject.hpp"
#include "base_registry.hpp"

namespace lagoon {

class base_registry;

class member_metaobject_sequence
 : public metaobject_sequence
{
private:
	base_registry& _reg;
	_aux::flat_set<fingerprint>& _mems;
public:
	member_metaobject_sequence(
		_aux::flat_set<fingerprint>& mems,
		base_registry& reg
	) noexcept;

	bool is_none(void) const
	override;

	size_type get_size(void)
	override;

	shared_metaobject get_element(size_type)
	override;
};

} // namespace lagoon

#include <lagoon/member_sequence.inl>

#endif //include guard

