#ifndef P0953_HPP_
#define P0953_HPP_

namespace meta {
namespace _dtl {

enum class category_bits : unsigned {
	cat_obj_sequence = (1 << 0),
	cat_reversible = (1 << 1),
	cat_named = (1 << 2),
	cat_typed = (1 << 3),
	cat_scope = (1 << 4),
	cat_scope_member = (1 << 5),
	cat_inheritance = (1 << 6),
	cat_template = (1 << 7),
	cat_parameter = (1 << 8),
	cat_enum_member = (1 << 9) | cat_scope_member,
	cat_record_member = (1 << 10) | cat_scope_member,
	cat_alias = (1 << 11) | cat_named,
	cat_constant = (1 << 12) | cat_typed,
	cat_variable = (1 << 13) | cat_named | cat_typed | cat_scope_member,
	cat_namespace = (1 << 14) | cat_named | cat_scope | cat_scope_member,
	cat_global_scope = (1 << 15) | cat_namespace,
	cat_type = (1 << 16) | cat_named | cat_reversible,
	cat_tag_type = (1 << 17) | cat_type | cat_scope | cat_scope_member,
	cat_enum = (1 << 18) | cat_tag_type,
	cat_record = (1 << 19) | cat_tag_type,
	cat_class = (1 << 20) | cat_record,
	cat_function = (1 << 21) | cat_scope | cat_scope_member,
	cat_specifier = (1 << 22) | cat_named,
	cat_template_type_param = cat_template | cat_type | cat_parameter | cat_alias,
	cat_namespace_alias = cat_namespace | cat_alias,
	cat_type_alias = cat_type | cat_alias | cat_scope_member,
	cat_enum_alias = cat_enum | cat_alias,
	cat_record_alias = cat_record | cat_alias,
	cat_class_alias = cat_class | cat_alias,
	cat_named_function = cat_named | cat_function,
	cat_data_member = cat_record_member | cat_variable,
	cat_member_type = cat_record_member | cat_type,
	cat_member_type_alias = cat_record_member | cat_type_alias,
	cat_member_record = cat_record_member | cat_record,
	cat_member_record_alias = cat_record_member | cat_record_alias,
	cat_member_class = cat_record_member | cat_class,
	cat_member_class_alias = cat_record_member | cat_class_alias,
	cat_member_enum = cat_record_member | cat_enum,
	cat_member_enum_alias = cat_record_member | cat_enum_alias,
	cat_member_function = cat_record_member | cat_named_function,
	cat_enumerator = cat_constant | cat_named | cat_enum_member
};

#define MIRROR_CAT_BITS(CAT) unsigned(meta::_dtl::category_bits::cat_##CAT)

#define MIRROR_OBJ_IS(BITS, CAT) ((BITS & MIRROR_CAT_BITS(CAT)) == MIRROR_CAT_BITS(CAT))

struct moid_holder {
	constexpr moid_holder(__metaobject_id moid) noexcept
	  : _moid{moid} {
	}

	const __metaobject_id _moid{};
};

#define MIRROR_GET_MOID(THIS) static_cast<const Derived*>(THIS)->_moid

template <unsigned CatBits>
struct metaobject;

template <class Derived, bool isObject>
struct object_ops {};

template <class Derived>
struct object_ops<Derived, true> {
	constexpr bool is_named() const noexcept {
		return __metaobject_is_meta_named(MIRROR_GET_MOID(this));
	}

	constexpr bool is_scope() const noexcept {
		return __metaobject_is_meta_scope(MIRROR_GET_MOID(this));
	}

	constexpr bool is_scope_member() const noexcept {
		return __metaobject_is_meta_scope_member(MIRROR_GET_MOID(this));
	}
};

template <class Derived, bool isObjectSequence>
struct obj_sequence_ops {};

template <class Derived>
struct obj_sequence_ops<Derived, true> {
	constexpr auto size() const noexcept {
		return __metaobject_get_size(MIRROR_GET_MOID(this));
	}
};

template <class Derived, bool isNamed>
struct named_ops {};

template <class Derived>
struct named_ops<Derived, true> {
	constexpr auto base_name_length() const noexcept {
		return __metaobject_base_name_length(MIRROR_GET_MOID(this));
	}

	constexpr auto display_name_length() const noexcept {
		return __metaobject_display_name_length(MIRROR_GET_MOID(this));
	}
};

template <class Derived, bool isScopeMember>
struct scope_member_ops {};

template <class Derived>
struct scope_member_ops<Derived, true> {
	constexpr metaobject<MIRROR_CAT_BITS(scope)> get_scope() const noexcept;
};

#define MIRROR_IMPL_OBJ_OPS(CONCEPT) \
	CONCEPT##_ops<metaobject<CatBits>, MIRROR_OBJ_IS(CatBits, CONCEPT)>

template <unsigned CatBits>
struct metaobject
  : moid_holder
  , object_ops<metaobject<CatBits>, true>
  , MIRROR_IMPL_OBJ_OPS(obj_sequence)
  , MIRROR_IMPL_OBJ_OPS(named)
  , MIRROR_IMPL_OBJ_OPS(scope_member) {
	constexpr metaobject(__metaobject_id moid) noexcept
	  : moid_holder{moid} {
	}
};

template <class Derived>
constexpr metaobject<MIRROR_CAT_BITS(scope)> scope_member_ops<Derived, true>::get_scope() const
  noexcept {
	return {__metaobject_get_scope(MIRROR_GET_MOID(this))};
}

#define reflexpr(...)                                                                \
	meta::_dtl::metaobject<__metaobject_get_concept_bits(__reflexpr(__VA_ARGS__))> { \
		__reflexpr(__VA_ARGS__)                                                      \
	}

} // namespace _dtl
} // namespace meta

#endif // P0953_HPP_
