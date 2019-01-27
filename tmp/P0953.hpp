#ifndef P0953_HPP_
#define P0953_HPP_

namespace meta {
//------------------------------------------------------------------------------
enum class category_bits : unsigned {
	cat_object = 0,
	cat_object_sequence = (1 << 0),
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
	cat_template_type_param =
	  cat_template | cat_type | cat_parameter | cat_alias,
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
//------------------------------------------------------------------------------
#define MIRROR_CAT_BITS(CAT) unsigned(meta::category_bits::cat_##CAT)

#define MIRROR_OBJ_IS(BITS, CAT) \
	((BITS & MIRROR_CAT_BITS(CAT)) == MIRROR_CAT_BITS(CAT))
//------------------------------------------------------------------------------
struct moid_holder {
	constexpr moid_holder(__metaobject_id moid) noexcept
	  : _moid{moid} {
	}

	const __metaobject_id _moid{};
};
//------------------------------------------------------------------------------
#define MIRROR_GET_MOID(THIS) static_cast<const Derived*>(THIS)->_moid
//------------------------------------------------------------------------------
template <class Derived, bool isObject>
struct object_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isObjectSequence>
struct object_sequence_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isNamed>
struct named_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isTyped>
struct typed_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isScope>
struct scope_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isInheritance>
struct inheritance_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isScopeMember>
struct scope_member_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isEnumMember>
struct enum_member_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isAlias>
struct alias_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isType>
struct type_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isTagType>
struct tag_type_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isEnum>
struct enum_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isRecord>
struct record_ops {};
//------------------------------------------------------------------------------
template <class Derived, bool isClass>
struct class_ops {};
//------------------------------------------------------------------------------
#define MIRROR_IMPL_OBJ_OPS(CONCEPT) \
	CONCEPT##_ops<metaobject<CatBits>, MIRROR_OBJ_IS(CatBits, CONCEPT)>
//------------------------------------------------------------------------------
template <unsigned CatBits>
struct metaobject
  : moid_holder
  , MIRROR_IMPL_OBJ_OPS(object)
  , MIRROR_IMPL_OBJ_OPS(object_sequence)
  , MIRROR_IMPL_OBJ_OPS(named)
  , MIRROR_IMPL_OBJ_OPS(typed)
  , MIRROR_IMPL_OBJ_OPS(inheritance)
  , MIRROR_IMPL_OBJ_OPS(scope_member)
  , MIRROR_IMPL_OBJ_OPS(enum_member)
  , MIRROR_IMPL_OBJ_OPS(scope)
  , MIRROR_IMPL_OBJ_OPS(alias)
  , MIRROR_IMPL_OBJ_OPS(type)
  , MIRROR_IMPL_OBJ_OPS(tag_type)
  , MIRROR_IMPL_OBJ_OPS(enum)
  , MIRROR_IMPL_OBJ_OPS(record)
  , MIRROR_IMPL_OBJ_OPS(class) {

	constexpr metaobject(__metaobject_id moid) noexcept
	  : moid_holder{moid} {
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct object_ops<Derived, true> {
	constexpr auto get_concept_bits() const noexcept {
		return __metaobject_get_concept_bits(MIRROR_GET_MOID(this));
	}

	constexpr bool is_object_sequence() const noexcept {
		return __metaobject_is_meta_obj_sequence(MIRROR_GET_MOID(this));
	}

	constexpr bool is_named() const noexcept {
		return __metaobject_is_meta_named(MIRROR_GET_MOID(this));
	}

	constexpr bool is_typed() const noexcept {
		return __metaobject_is_meta_typed(MIRROR_GET_MOID(this));
	}

	constexpr bool is_scope() const noexcept {
		return __metaobject_is_meta_scope(MIRROR_GET_MOID(this));
	}

	constexpr bool is_scope_member() const noexcept {
		return __metaobject_is_meta_scope_member(MIRROR_GET_MOID(this));
	}

	constexpr bool is_inheritance() const noexcept {
		return __metaobject_is_meta_inheritance(MIRROR_GET_MOID(this));
	}

	constexpr bool is_template() const noexcept {
		return __metaobject_is_meta_template(MIRROR_GET_MOID(this));
	}

	constexpr bool is_parameter() const noexcept {
		return __metaobject_is_meta_parameter(MIRROR_GET_MOID(this));
	}

	constexpr bool is_record_member() const noexcept {
		return __metaobject_is_meta_record_member(MIRROR_GET_MOID(this));
	}

	constexpr bool is_alias() const noexcept {
		return __metaobject_is_meta_alias(MIRROR_GET_MOID(this));
	}

	constexpr bool is_constant() const noexcept {
		return __metaobject_is_meta_constant(MIRROR_GET_MOID(this));
	}

	constexpr bool is_variable() const noexcept {
		return __metaobject_is_meta_variable(MIRROR_GET_MOID(this));
	}

	constexpr bool is_namespace() const noexcept {
		return __metaobject_is_meta_namespace(MIRROR_GET_MOID(this));
	}

	constexpr bool is_global_scope() const noexcept {
		return __metaobject_is_meta_global_scope(MIRROR_GET_MOID(this));
	}

	constexpr bool is_type() const noexcept {
		return __metaobject_is_meta_type(MIRROR_GET_MOID(this));
	}

	constexpr bool is_tag_type() const noexcept {
		return __metaobject_is_meta_tag_type(MIRROR_GET_MOID(this));
	}

	constexpr bool is_enum() const noexcept {
		return __metaobject_is_meta_enum(MIRROR_GET_MOID(this));
	}

	constexpr bool is_record() const noexcept {
		return __metaobject_is_meta_record(MIRROR_GET_MOID(this));
	}

	constexpr bool is_class() const noexcept {
		return __metaobject_is_meta_class(MIRROR_GET_MOID(this));
	}

	constexpr bool is_function() const noexcept {
		return __metaobject_is_meta_function(MIRROR_GET_MOID(this));
	}

	constexpr auto get_source_line() const noexcept {
		return __metaobject_get_source_line(MIRROR_GET_MOID(this));
	}

	constexpr auto get_source_column() const noexcept {
		return __metaobject_get_source_column(MIRROR_GET_MOID(this));
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct object_sequence_ops<Derived, true> {
	constexpr auto size() const noexcept {
		return __metaobject_get_size(MIRROR_GET_MOID(this));
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct named_ops<Derived, true> {
	constexpr auto base_name_length() const noexcept {
		return __metaobject_base_name_length(MIRROR_GET_MOID(this));
	}

	constexpr auto display_name_length() const noexcept {
		return __metaobject_display_name_length(MIRROR_GET_MOID(this));
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct typed_ops<Derived, true> {
	constexpr metaobject<MIRROR_CAT_BITS(type)> get_type() const noexcept {
		return {__metaobject_get_type(MIRROR_GET_MOID(this))};
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct scope_member_ops<Derived, true> {
	constexpr metaobject<MIRROR_CAT_BITS(scope)> get_scope() const noexcept {
		return {__metaobject_get_scope(MIRROR_GET_MOID(this))};
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct alias_ops<Derived, true> {
	constexpr metaobject<MIRROR_CAT_BITS(named)> get_aliased() const noexcept {
		return {__metaobject_get_aliased(MIRROR_GET_MOID(this))};
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct tag_type_ops<Derived, true> {
	constexpr bool is_enum() const noexcept {
		return __metaobject_is_enum(MIRROR_GET_MOID(this));
	}

	constexpr bool is_class() const noexcept {
		return __metaobject_is_class(MIRROR_GET_MOID(this));
	}

	constexpr bool is_struct() const noexcept {
		return __metaobject_is_struct(MIRROR_GET_MOID(this));
	}

	constexpr bool is_union() const noexcept {
		return __metaobject_is_union(MIRROR_GET_MOID(this));
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct enum_ops<Derived, true> {
	constexpr bool is_scoped_enum() const noexcept {
		return __metaobject_is_scoped_enum(MIRROR_GET_MOID(this));
	}

	constexpr metaobject<MIRROR_CAT_BITS(object_sequence)> get_enumerators()
	  const noexcept {
		return {__metaobject_get_enumerators(MIRROR_GET_MOID(this))};
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct class_ops<Derived, true> {
	constexpr metaobject<MIRROR_CAT_BITS(object_sequence)> get_base_classes()
	  const noexcept {
		return {__metaobject_get_base_classes(MIRROR_GET_MOID(this))};
	}

	constexpr metaobject<MIRROR_CAT_BITS(object_sequence)> get_member_types()
	  const noexcept {
		return {__metaobject_get_member_types(MIRROR_GET_MOID(this))};
	}
};
//------------------------------------------------------------------------------
template <class Derived>
struct inheritance_ops<Derived, true> {
	constexpr metaobject<MIRROR_CAT_BITS(class)> get_base_class() const
	  noexcept {
		return {__metaobject_get_base_class(MIRROR_GET_MOID(this))};
	}
};
//------------------------------------------------------------------------------
#define reflexpr(...)                                                          \
	meta::metaobject<__metaobject_get_concept_bits(__reflexpr(__VA_ARGS__))> { \
		__reflexpr(__VA_ARGS__)                                                \
	}
//------------------------------------------------------------------------------
#define downcast(METAOBJECT)                          \
	meta::metaobject<METAOBJECT.get_concept_bits()> { \
		METAOBJECT._moid                              \
	}
//------------------------------------------------------------------------------
} // namespace meta

#endif // P0953_HPP_
