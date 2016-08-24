/**
 * .file lagoon/concrete_metaobject.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <lagoon/metaobject_registry.hpp>
#include <lagoon/fingerprint.hpp>

namespace lagoon {

template <class Traits>
template <typename MO>
inline
concrete_metaobject_tpl<Traits>::
concrete_metaobject_tpl(MO mo, metaobject_registry& reg)
noexcept
 : _aux::mo_source<Traits>(mo)
 , _aux::mo_scoped<Traits>(mo, reg)
 , _aux::mo_scope<Traits>(mo, reg)
 , _aux::mo_typed<Traits>(mo, reg)
 , _aux::mo_named<Traits>(mo)
 , _aux::mo_alias<Traits>(mo, reg)
 , _aux::mo_record<Traits>(mo, reg)
 , _aux::mo_enum<Traits>(mo, reg)
 , _aux::mo_inherit<Traits>(mo, reg)
 , _aux::mo_access<Traits>(mo, reg)
 , _fpt(lagoon::get_fingerprint(mo))
 , _ts(mo)
{
	static_assert(puddle::is_metaobject(mo), "");
}

template <class Traits>
inline
bool
concrete_metaobject_tpl<Traits>::is_none(void) const
{
	return false;
}

template <class Traits>
inline
fingerprint
concrete_metaobject_tpl<Traits>::get_fingerprint(void)
{
	return _fpt;
}

template <class Traits>
inline
const metaobject_traits*
concrete_metaobject_tpl<Traits>::traits(void)
{
	return &_ts;
}

template <class Traits>
inline
std::string_view
concrete_metaobject_tpl<Traits>::get_source_file(void)
{
	return this->_src_fil();
}

template <class Traits>
inline
unsigned
concrete_metaobject_tpl<Traits>::get_source_line(void)
{
	return this->_src_lin();
}

template <class Traits>
inline
unsigned
concrete_metaobject_tpl<Traits>::get_source_column(void)
{
	return this->_src_col();
}

template <class Traits>
inline
std::string_view
concrete_metaobject_tpl<Traits>::get_base_name(void)
{
	return this->_base_name();
}

template <class Traits>
inline
std::string_view
concrete_metaobject_tpl<Traits>::get_full_name(void)
{
	return this->_full_name();
}

template <class Traits>
inline
std::string_view
concrete_metaobject_tpl<Traits>::get_display_name(void)
{
	return this->_disp_name();
}

template <class Traits>
inline
shared_metaobject
concrete_metaobject_tpl<Traits>::get_type(void)
{
	return this->_type();
}

template <class Traits>
inline
shared_metaobject
concrete_metaobject_tpl<Traits>::get_scope(void)
{
	return this->_scope();
}

template <class Traits>
inline
shared_metaobject
concrete_metaobject_tpl<Traits>::get_aliased(void)
{
	return this->_aliased();
}

template <class Traits>
inline
shared_metaobject
concrete_metaobject_tpl<Traits>::get_base_class(void)
{
	return this->_base_cls();
}

template <class Traits>
inline
shared_metaobject
concrete_metaobject_tpl<Traits>::get_access_specifier(void)
{
	return this->_accs_spec();
}

template <class Traits>
inline
shared_metaobject_sequence
concrete_metaobject_tpl<Traits>::get_base_classes(void)
{
	return this->_base_clss();
}

template <class Traits>
inline
shared_metaobject_sequence
concrete_metaobject_tpl<Traits>::get_data_members(void)
{
	return this->_data_mems();
}

template <class Traits>
inline
shared_metaobject_sequence
concrete_metaobject_tpl<Traits>::get_member_types(void)
{
	return this->_memb_typs();
}

template <class Traits>
inline
shared_metaobject_sequence
concrete_metaobject_tpl<Traits>::get_enumerators(void)
{
	return this->_enmrtrs();
}

template <class Traits>
inline
shared_metaobject_sequence
concrete_metaobject_tpl<Traits>::get_members(void)
{
	return this->_members();
}

} // namespace lagoon
