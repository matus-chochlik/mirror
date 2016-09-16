/**
 * @file lagoon/concrete_storage.hpp
 * @brief Declaration of concrete metaobject storage classes
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_CONCRETE_STORAGE_1105240825_HPP
#define LAGOON_CONCRETE_STORAGE_1105240825_HPP

#include "metaobject.hpp"
#include "any_constant.hpp"

namespace lagoon {
namespace _aux {

template <typename X>
struct do_make_mo_trait_tuple;

template <
	bool HasSourceInfo,
	bool IsScopeMember,
	bool IsScope,
	bool IsNamed,
	bool IsTyped,
	bool IsTagType,
	bool IsRecord,
	bool IsEnum,
	bool IsRecordMember,
	bool IsConstant,
	bool IsInheritance,
	bool IsSpecifier
> struct mo_trait_tuple
{
	static constexpr const bool has_source_info = HasSourceInfo;
	static constexpr const bool is_scope_member = IsScopeMember;
	static constexpr const bool is_scope = IsScope;
	static constexpr const bool is_named = IsNamed;
	static constexpr const bool is_typed = IsTyped;
	static constexpr const bool is_tag_type = IsTagType;
	static constexpr const bool is_record = IsRecord;
	static constexpr const bool is_enum = IsEnum;
	static constexpr const bool is_record_member = IsRecordMember;
	static constexpr const bool is_constant = IsConstant;
	static constexpr const bool is_inheritance = IsInheritance;
	static constexpr const bool is_specifier = IsSpecifier;
};

template <typename MO>
struct do_make_mo_trait_tuple<mirror::metaobject<MO>>
{
	using type = mo_trait_tuple<
		reflbase::get_source_line_v<MO> != 0,
		reflbase::ScopeMember<MO>,
		reflbase::Scope<MO>,
		reflbase::Named<MO>,
		reflbase::Typed<MO>,
		reflbase::TagType<MO>,
		reflbase::Record<MO>,
		reflbase::Enum<MO>,
		reflbase::RecordMember<MO>,
		reflbase::Constant<MO>,
		reflbase::Inheritance<MO>,
		reflbase::Specifier<MO>
	>;
};

template <>
struct do_make_mo_trait_tuple<mirror::none>
{
	using type = mo_trait_tuple<
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false
	>;
};

template <typename MO>
using make_mo_trait_tuple = typename do_make_mo_trait_tuple<MO>::type;

// mo_source_data
template <bool HasSrc>
class mo_source_data;

template <>
class mo_source_data<true>
{
private:
	struct {
		std::string_view _fil;
		unsigned _lin;
		unsigned _col;
	} _store;
protected:
	template <typename MO>
	mo_source_data(MO, metaobject_registry&);

	std::string_view _src_fil(void) const { return _store._fil; }
	unsigned  _src_lin(void) const { return _store._lin; }
	unsigned  _src_col(void) const { return _store._col; }
};

template <>
class mo_source_data<false>
{
protected:
	template <typename MO>
	mo_source_data(MO, metaobject_registry&)
	{ }

	std::string_view _src_fil(void) const { return {}; }
	unsigned _src_lin(void) const { return 0; }
	unsigned _src_col(void) const { return 0; }
};

template <typename Traits>
using mo_source = mo_source_data<Traits::has_source_info>;

// mo_named_data
template <bool Named, bool SingleName>
class mo_named_data;

template <>
class mo_named_data<true, false>
{
private:
	struct {
		std::string_view _bn;
		std::string_view _fn;
		std::string_view _dn;
	} _store;
protected:
	template <typename MO>
	mo_named_data(MO, metaobject_registry&);

	std::string_view _base_name(void) const { return _store._bn; }
	std::string_view _full_name(void) const { return _store._fn; }
	std::string_view _disp_name(void) const { return _store._dn; }
};

template <>
class mo_named_data<true, true>
{
private:
	struct {
		std::string_view _n;
	} _store;
protected:
	template <typename MO>
	mo_named_data(MO, metaobject_registry&);

	std::string_view _base_name(void) const { return _store._n; }
	std::string_view _full_name(void) const { return _store._n; }
	std::string_view _disp_name(void) const { return _store._n; }
};

template <bool B>
class mo_named_data<false, B>
{
protected:
	template <typename MO>
	mo_named_data(MO, metaobject_registry&) { }

	std::string_view _base_name(void) const { return {}; }
	std::string_view _full_name(void) const { return {}; }
	std::string_view _disp_name(void) const { return {}; }
};

template <typename Traits>
using mo_named = mo_named_data<
	Traits::is_named,
	Traits::is_specifier ||
	!Traits::is_scope_member
>;

// mo_typed_data
template <bool Typed>
class mo_typed_data;

template <>
class mo_typed_data<true>
{
private:
	struct {
		shared_metaobject _ty;
	} _store;
protected:
	template <typename MO>
	mo_typed_data(MO, metaobject_registry& reg);

	const shared_metaobject& _type(void) const { return _store._ty; }
};

template <>
class mo_typed_data<false>
{
protected:
	template <typename MO>
	mo_typed_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject& _type(void) const;
};

template <typename Traits>
using mo_typed = mo_typed_data<Traits::is_typed>;

// mo_scope_data
template <bool Scope>
class mo_scope_data;

template <>
class mo_scope_data<true>
{
private:
	struct {
		shared_metaobject_sequence _mems;
	} _store;
protected:
	template <typename MO>
	mo_scope_data(MO, metaobject_registry& reg);

	const shared_metaobject_sequence& _members(void) const {
		return _store._mems;
	}
};

template <>
class mo_scope_data<false>
{
protected:
	template <typename MO>
	mo_scope_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject_sequence& _members(void) const;
};

template <typename Traits>
using mo_scope = mo_scope_data<Traits::is_scope>;

// mo_scoped_data
template <bool Typed>
class mo_scoped_data;

template <>
class mo_scoped_data<true>
{
private:
	struct {
		shared_metaobject _sc;
	} _store;
protected:
	template <typename MO>
	mo_scoped_data(MO, metaobject_registry& reg);

	const shared_metaobject& _scope(void) const { return _store._sc; }
};

template <>
class mo_scoped_data<false>
{
protected:
	template <typename MO>
	mo_scoped_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject& _scope(void) const;
};

template <typename Traits>
using mo_scoped = mo_scoped_data<Traits::is_scope_member>;

// mo_alias_data
template <bool Typed>
class mo_alias_data;

template <>
class mo_alias_data<true>
{
private:
	struct {
		shared_metaobject _al;
	} _store;
protected:
	template <typename MO>
	mo_alias_data(MO, metaobject_registry& reg);

	const shared_metaobject& _aliased(void) const { return _store._al; }
};

template <>
class mo_alias_data<false>
{
protected:
	template <typename MO>
	mo_alias_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject& _aliased(void) const;
};

template <typename Traits>
using mo_alias = mo_alias_data<Traits::is_named>; // yes, named.

// mo_inherit_data
template <bool Typed>
class mo_inherit_data;

template <>
class mo_inherit_data<true>
{
private:
	struct {
		shared_metaobject _bc;
	} _store;
protected:
	template <typename MO>
	mo_inherit_data(MO, metaobject_registry& reg);

	const shared_metaobject& _base_cls(void) const { return _store._bc; }
};

template <>
class mo_inherit_data<false>
{
protected:
	template <typename MO>
	mo_inherit_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject& _base_cls(void) const;
};

template <typename Traits>
using mo_inherit = mo_inherit_data<Traits::is_inheritance>;

// mo_access_data
template <bool Accessible>
class mo_access_data;

template <>
class mo_access_data<true>
{
private:
	struct {
		shared_metaobject _as;
	} _store;
protected:
	template <typename MO>
	mo_access_data(MO, metaobject_registry& reg);

	const shared_metaobject& _accs_spec(void) const { return _store._as; }
};

template <>
class mo_access_data<false>
{
protected:
	template <typename MO>
	mo_access_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject& _accs_spec(void) const;
};

template <typename Traits>
using mo_access = mo_access_data<
	Traits::is_inheritance ||
	Traits::is_record_member
>;

// mo_tag_type_data
template <bool Record>
class mo_tag_type_data;

template <>
class mo_tag_type_data<true>
{
private:
	struct {
		shared_metaobject _ets;
	} _store;
protected:
	template <typename MO>
	mo_tag_type_data(MO, metaobject_registry& reg);

	const shared_metaobject& _tag_typ_spec(void) const {
		return _store._ets;
	}
};

template <>
class mo_tag_type_data<false>
{
protected:
	template <typename MO>
	mo_tag_type_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject& _tag_typ_spec(void) const;
};

template <typename Traits>
using mo_tag_type = mo_tag_type_data<Traits::is_tag_type>;

// mo_record_data
template <bool Record>
class mo_record_data;

template <>
class mo_record_data<true>
{
private:
	struct {
		shared_metaobject_sequence _bs;
		shared_metaobject_sequence _dm;
		shared_metaobject_sequence _mt;
	} _store;
protected:
	template <typename MO>
	mo_record_data(MO, metaobject_registry& reg);

	const shared_metaobject_sequence& _base_clss(void) const {
		return _store._bs;
	}
	const shared_metaobject_sequence& _data_mems(void) const {
		return _store._dm;
	}
	const shared_metaobject_sequence& _memb_typs(void) const {
		return _store._mt;
	}
};

template <>
class mo_record_data<false>
{
protected:
	template <typename MO>
	mo_record_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject_sequence& _base_clss(void) const;
	const shared_metaobject_sequence& _data_mems(void) const;
	const shared_metaobject_sequence& _memb_typs(void) const;
};

template <typename Traits>
using mo_record = mo_record_data<Traits::is_record>;

// mo_enum_data
template <bool Record>
class mo_enum_data;

template <>
class mo_enum_data<true>
{
private:
	struct {
		shared_metaobject_sequence _em;
	} _store;
protected:
	template <typename MO>
	mo_enum_data(MO, metaobject_registry& reg);

	const shared_metaobject_sequence& _enmrtrs(void) const {
		return _store._em;
	}
};

template <>
class mo_enum_data<false>
{
protected:
	template <typename MO>
	mo_enum_data(MO, metaobject_registry&)
	{ }

	const shared_metaobject_sequence& _enmrtrs(void) const;
};

template <typename Traits>
using mo_enum = mo_enum_data<Traits::is_enum>;

// mo_constant_data
template <bool Record>
class mo_constant_data;

template <>
class mo_constant_data<true>
{
private:
	struct {
		any_constant _cv;
	} _store;
protected:
	template <typename MO>
	mo_constant_data(MO, metaobject_registry& reg);

	const any_constant& _cnst_val(void) const {
		return _store._cv;
	}
};

template <>
class mo_constant_data<false>
{
protected:
	template <typename MO>
	mo_constant_data(MO, metaobject_registry&)
	{ }

	any_constant _cnst_val(void) const { return {}; }
};

template <typename Traits>
using mo_constant = mo_constant_data<Traits::is_constant>;

} // namespace _aux
} // namespace lagoon

#include <lagoon/concrete_storage.inl>

#endif //include guard

