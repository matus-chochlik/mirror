/**
 * @file lagoon/concrete_sequence.hpp
 * @brief Declaration of the `concrete_metaobject` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_CONCRETE_SEQUENCE_1105240825_HPP
#define LAGOON_CONCRETE_SEQUENCE_1105240825_HPP

#include "metaobject.hpp"
#include <mirror/range.hpp>
#include <vector>

namespace lagoon {

class base_registry;

class concrete_metaobject_sequence_base
 : public metaobject_sequence
{
private:
	base_registry& _reg;
	std::vector<shared_metaobject> _mos;

protected:
	concrete_metaobject_sequence_base(
		std::vector<shared_metaobject>&& mos,
		base_registry& reg
	);
public:
	bool is_none(void) const
	override;

	size_type get_size(void)
	override;

	shared_metaobject get_element(size_type)
	override;
};

class concrete_metaobject_sequence
 : public concrete_metaobject_sequence_base
{
private:
	template <typename ... MO>
	static
	std::vector<shared_metaobject>
	_make_vec(mirror::range<MO...>, base_registry& reg);
public:
	template <typename MOS>
	concrete_metaobject_sequence(MOS, base_registry& reg)
	noexcept;
};

class concrete_inh_metaobject_sequence
 : public concrete_metaobject_sequence_base
{
private:
	template <typename PMO, typename ... MO>
	static
	std::vector<shared_metaobject>
	_make_vec(PMO, mirror::range<MO...>, base_registry& reg);
public:
	template <typename PMO, typename MOS>
	concrete_inh_metaobject_sequence(PMO, MOS, base_registry& reg)
	noexcept;
};

} // namespace lagoon

#include <lagoon/concrete_sequence.inl>

#endif //include guard

