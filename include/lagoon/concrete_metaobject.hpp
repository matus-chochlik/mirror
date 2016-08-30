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
#include "concrete_storage.hpp"

namespace lagoon {

class metaobject_registry;

template <class Traits>
class concrete_metaobject_tpl
 : public metaobject
 , public _aux::mo_source<Traits>
 , public _aux::mo_scoped<Traits>
 , public _aux::mo_scope<Traits>
 , public _aux::mo_typed<Traits>
 , public _aux::mo_named<Traits>
 , public _aux::mo_alias<Traits>
 , public _aux::mo_tag_type<Traits>
 , public _aux::mo_record<Traits>
 , public _aux::mo_enum<Traits>
 , public _aux::mo_constant<Traits>
 , public _aux::mo_inherit<Traits>
 , public _aux::mo_access<Traits>
{
private:
	fingerprint _fpt;
	metaobject_traits _ts;
public:
	template <typename MO>
	concrete_metaobject_tpl(MO, metaobject_registry& reg)
	noexcept;

	bool is_none(void) const
	override;

	fingerprint get_fingerprint(void)
	override;

	const metaobject_traits* traits(void)
	override;

	std::string_view get_source_file(void)
	override;

	unsigned get_source_line(void)
	override;

	unsigned get_source_column(void)
	override;

	std::string_view get_base_name(void)
	override;

	std::string_view get_full_name(void)
	override;

	std::string_view get_display_name(void)
	override;

	any_constant get_constant(void)
	override;

	shared_metaobject get_type(void)
	override;

	shared_metaobject get_scope(void)
	override;

	shared_metaobject get_aliased(void)
	override;

	shared_metaobject get_base_class(void)
	override;

	shared_metaobject get_elaborated_type_specifier(void)
	override;

	shared_metaobject get_access_specifier(void)
	override;

	shared_metaobject_sequence get_base_classes(void)
	override;

	shared_metaobject_sequence get_data_members(void)
	override;

	shared_metaobject_sequence get_member_types(void)
	override;

	shared_metaobject_sequence get_enumerators(void)
	override;

	shared_metaobject_sequence get_members(void)
	override;
};

template <typename MO>
using concrete_metaobject =
	concrete_metaobject_tpl<_aux::make_mo_trait_tuple<MO>>;

} // namespace lagoon

#include <lagoon/concrete_metaobject.inl>

#endif //include guard

