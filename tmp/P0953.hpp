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
	cat_template = (1 << 7)
};

#define MIRROR_OBJ_IS(BITS, CAT)                             \
	((BITS & unsigned(meta::_dtl::category_bits::cat_##CAT)) \
	  == unsigned(meta::_dtl::category_bits::cat_##CAT))

struct moid_holder {
	constexpr moid_holder(__metaobject_id moid) noexcept
	  : _moid{moid} {
	}

	__metaobject_id _moid{};
};

#define MIRROR_GET_MOID(THIS) static_cast<const Derived*>(THIS)->_moid

template <class Derived, bool isObject>
struct object_ops {};

template <class Derived>
struct object_ops<Derived, true> {
	constexpr bool is_named() const noexcept {
		return __metaobject_is_meta_named(MIRROR_GET_MOID(this));
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

template <class Derived, bool isScoped>
struct scope_member_ops {};

template <class Derived>
struct scope_member_ops<Derived, true> {};

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

#define reflexpr(...)                                                                \
	meta::_dtl::metaobject<__metaobject_get_concept_bits(__reflexpr(__VA_ARGS__))> { \
		__reflexpr(__VA_ARGS__)                                                      \
	}

} // namespace _dtl
} // namespace meta

#endif // P0953_HPP_
