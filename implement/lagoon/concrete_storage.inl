/**
 * .file lagoon/concrete_storage.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/metaobject_registry.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_full_name.hpp>
#include <mirror/get_display_name.hpp>
#include <mirror/get_type.hpp>
#include <mirror/get_scope.hpp>
#include <mirror/get_aliased.hpp>
#include <mirror/get_base_class.hpp>
#include <mirror/get_access_specifier.hpp>
#include <mirror/get_base_classes.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/string_view.hpp>
#include <lagoon/none_metaobject.hpp>
#include <lagoon/none_sequence.hpp>
#include <lagoon/fingerprint.hpp>

namespace lagoon {
namespace _aux {

// mo_named
template <typename MO>
inline
mo_named_data<true, false>::mo_named_data(MO)
 : _store{
	mirror::string_view<mirror::get_base_name<MO>>,
	mirror::string_view<mirror::get_full_name<MO>>,
	mirror::string_view<mirror::get_display_name<MO>>
} { }

template <typename MO>
inline
mo_named_data<true, true>::mo_named_data(MO)
 : _store{mirror::string_view<mirror::get_base_name<MO>>}
{ }

// mo_typed
template <typename MO>
inline
mo_typed_data<true>::mo_typed_data(MO, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(mirror::get_type<MO>{}))}
{ }

inline
const shared_metaobject&
mo_typed_data<false>::_type(void) const
{
	return none_metaobject::get_single();
}

// mo_scoped
template <typename MO>
inline
mo_scoped_data<true>::mo_scoped_data(MO, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(mirror::get_scope<MO>{}))}
{ }

inline
const shared_metaobject&
mo_scoped_data<false>::_scope(void) const
{
	return none_metaobject::get_single();
}

// mo_alias
template <typename MO>
inline
mo_alias_data<true>::mo_alias_data(MO, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(mirror::get_aliased<MO>{}))}
{ }

inline
const shared_metaobject&
mo_alias_data<false>::_aliased(void) const
{
	return none_metaobject::get_single();
}

// mo_inherit
template <typename MO>
inline
mo_inherit_data<true>::mo_inherit_data(MO, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(mirror::get_base_class<MO>{}))}
{ }

inline
const shared_metaobject&
mo_inherit_data<false>::_base_cls(void) const
{
	return none_metaobject::get_single();
}

// mo_access
template <typename MO>
inline
mo_access_data<true>::mo_access_data(MO, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(mirror::get_access_specifier<MO>{}))}
{ }

inline
const shared_metaobject&
mo_access_data<false>::_accs_spec(void) const
{
	return none_metaobject::get_single();
}

// mo_record
template <typename MO>
inline
mo_record_data<true>::mo_record_data(MO mo, metaobject_registry& reg)
 : _store{
	reg.make_inh_seq(mo, mirror::get_base_classes<MO>{}),
	reg.make_seq(mirror::get_data_members<MO>{}),
	reg.make_seq(mirror::get_member_types<MO>{})
 } { }

inline
const shared_metaobject_sequence&
mo_record_data<false>::_base_clss(void) const
{
	return none_metaobject_sequence::get_single();
}

inline
const shared_metaobject_sequence&
mo_record_data<false>::_data_mems(void) const
{
	return none_metaobject_sequence::get_single();
}

inline
const shared_metaobject_sequence&
mo_record_data<false>::_memb_typs(void) const
{
	return none_metaobject_sequence::get_single();
}

// mo_enum
template <typename MO>
inline
mo_enum_data<true>::mo_enum_data(MO, metaobject_registry& reg)
 : _store{reg.make_seq(mirror::get_enumerators<MO>{})}
{ }

inline
const shared_metaobject_sequence&
mo_enum_data<false>::_enmrtrs(void) const
{
	return none_metaobject_sequence::get_single();
}

} // namespace _aux
} // namespace lagoon
