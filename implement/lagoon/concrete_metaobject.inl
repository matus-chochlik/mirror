/**
 * .file lagoon/concrete_metaobject.inl
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
#include <mirror/get_base_classes.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_enumerators.hpp>

namespace lagoon {

template <typename MO>
inline
concrete_metaobject::concrete_metaobject(MO mo, metaobject_registry& reg)
noexcept
 : _bn(mirror::string_view<mirror::get_base_name<MO>>)
 , _fn(mirror::string_view<mirror::get_full_name<MO>>)
 , _dn(mirror::string_view<mirror::get_display_name<MO>>)
 , _ty(reg.get(mirror::get_fingerprint<mirror::get_type<MO>>))
 , _sc(reg.get(mirror::get_fingerprint<mirror::get_scope<MO>>))
 , _al(reg.get(mirror::get_fingerprint<mirror::get_aliased<MO>>))
 , _bi(reg.get_seq(mirror::get_base_classes<MO>{}))
 , _dm(reg.get_seq(mirror::get_data_members<MO>{}))
 , _mt(reg.get_seq(mirror::get_member_types<MO>{}))
 , _em(reg.get_seq(mirror::get_enumerators<MO>{}))
 , _ts(mo)
{
	static_assert(mirror::is_metaobject<MO>::value, "");
}

inline
bool
concrete_metaobject::is_none(void) const
{
	return false;
}

inline
const metaobject_traits&
concrete_metaobject::traits(void)
{
	return _ts;
}

inline
std::string_view
concrete_metaobject::get_base_name(void)
{
	return _bn;
}

inline
std::string_view
concrete_metaobject::get_full_name(void)
{
	return _fn;
}

inline
std::string_view
concrete_metaobject::get_display_name(void)
{
	return _dn;
}

inline
shared_metaobject
concrete_metaobject::get_type(void)
{
	return _ty;
}

inline
shared_metaobject
concrete_metaobject::get_scope(void)
{
	return _sc;
}

inline
shared_metaobject
concrete_metaobject::get_aliased(void)
{
	return _al;
}

inline
shared_metaobject_sequence
concrete_metaobject::get_base_classes(void)
{
	return _bi;
}

inline
shared_metaobject_sequence
concrete_metaobject::get_data_members(void)
{
	return _dm;
}

inline
shared_metaobject_sequence
concrete_metaobject::get_member_types(void)
{
	return _mt;
}

inline
shared_metaobject_sequence
concrete_metaobject::get_enumerators(void)
{
	return _em;
}

} // namespace lagoon
