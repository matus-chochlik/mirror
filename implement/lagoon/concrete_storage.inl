/**
 * .file lagoon/concrete_storage.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/metaobject_registry.hpp>
#include <puddle/metaobject_ops.hpp>
#include <lagoon/none_metaobject.hpp>
#include <lagoon/none_sequence.hpp>
#include <lagoon/fingerprint.hpp>

namespace lagoon {
namespace _aux {

// mo_source
template <typename MO>
inline
mo_source_data<true>::mo_source_data(MO mo)
 : _store{
	puddle::string_view(puddle::get_source_file(mo)),
	puddle::get_source_line(mo),
	puddle::get_source_column(mo)
} { }

// mo_named
template <typename MO>
inline
mo_named_data<true, false>::mo_named_data(MO mo)
 : _store{
	puddle::string_view(puddle::get_base_name(mo)),
	puddle::string_view(puddle::get_full_name(mo)),
	puddle::string_view(puddle::get_display_name(mo))
} { }

template <typename MO>
inline
mo_named_data<true, true>::mo_named_data(MO mo)
 : _store{puddle::string_view(puddle::get_base_name(mo))}
{ }

// mo_typed
template <typename MO>
inline
mo_typed_data<true>::mo_typed_data(MO mo, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(puddle::get_type(mo)))}
{ }

inline
const shared_metaobject&
mo_typed_data<false>::_type(void) const
{
	return none_metaobject::get_single();
}

// mo_scope
template <typename MO>
inline
mo_scope_data<true>::mo_scope_data(MO mo, metaobject_registry& reg)
 : _store{reg.make_mem_seq(get_fingerprint(mo))}
{ }

inline
const shared_metaobject_sequence&
mo_scope_data<false>::_members(void) const
{
	return none_metaobject_sequence::get_single();
}

// mo_scoped
template <typename MO>
inline
mo_scoped_data<true>::mo_scoped_data(MO mo, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(puddle::get_scope(mo)))}
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
mo_alias_data<true>::mo_alias_data(MO mo, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(puddle::get_aliased(mo)))}
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
mo_inherit_data<true>::mo_inherit_data(MO mo, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(puddle::get_base_class(mo)))}
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
mo_access_data<true>::mo_access_data(MO mo, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(puddle::get_access_specifier(mo)))}
{ }

inline
const shared_metaobject&
mo_access_data<false>::_accs_spec(void) const
{
	return none_metaobject::get_single();
}

// mo_tag_type
template <typename MO>
inline
mo_tag_type_data<true>::mo_tag_type_data(MO mo, metaobject_registry& reg)
 : _store{reg.get(get_fingerprint(puddle::get_elaborated_type_specifier(mo)))}
{ }

inline
const shared_metaobject&
mo_tag_type_data<false>::_tag_typ_spec(void) const
{
	return none_metaobject::get_single();
}

// mo_record
template <typename MO>
inline
mo_record_data<true>::mo_record_data(MO mo, metaobject_registry& reg)
 : _store{
	reg.make_inh_seq(mo, puddle::get_base_classes(mo)),
	reg.make_seq(puddle::get_data_members(mo)),
	reg.make_seq(puddle::get_member_types(mo))
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
mo_enum_data<true>::mo_enum_data(MO mo, metaobject_registry& reg)
 : _store{reg.make_seq(puddle::get_enumerators(mo))}
{ }

inline
const shared_metaobject_sequence&
mo_enum_data<false>::_enmrtrs(void) const
{
	return none_metaobject_sequence::get_single();
}

} // namespace _aux
} // namespace lagoon
