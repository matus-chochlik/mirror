/**
 * @file lagoon/concrete_metaobject.hpp
 * @brief Declaration of the `concrete_metaobject` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_CONCRETE_METAOBJECT_1105240825_HPP
#define LAGOON_CONCRETE_METAOBJECT_1105240825_HPP

#include "metaobject.hpp"

namespace lagoon {

class metaobject_registry;

class concrete_metaobject
 : public metaobject
{
private:
	std::string_view _bn;
	std::string_view _fn;
	std::string_view _dn;

	shared_metaobject _ty;
	shared_metaobject _sc;
	shared_metaobject _al;

	shared_metaobject_sequence _bi;
	shared_metaobject_sequence _dm;
	shared_metaobject_sequence _mt;
	shared_metaobject_sequence _em;

	metaobject_traits _ts;
public:
	template <typename MO>
	concrete_metaobject(MO, metaobject_registry& reg)
	noexcept;

	bool is_none(void) const
	override;

	const metaobject_traits& traits(void)
	override;

	std::string_view get_base_name(void)
	override;

	std::string_view get_full_name(void)
	override;

	std::string_view get_display_name(void)
	override;

	shared_metaobject get_type(void)
	override;

	shared_metaobject get_scope(void)
	override;

	shared_metaobject get_aliased(void)
	override;

	shared_metaobject_sequence get_base_classes(void)
	override;

	shared_metaobject_sequence get_data_members(void)
	override;

	shared_metaobject_sequence get_member_types(void)
	override;

	shared_metaobject_sequence get_enumerators(void)
	override;
};


} // namespace lagoon

#include <lagoon/concrete_metaobject.inl>

#endif //include guard

