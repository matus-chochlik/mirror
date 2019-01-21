#ifndef P0953_HPP_
#define P0953_HPP_

namespace meta {
namespace detail {

template <class Derived, bool>
struct object_ops {
	constexpr bool is_named() const noexcept {
		return __metaobject_is_meta_named(static_cast<const Derived*>(this)->_moid);
	}
};

template <class Derived>
struct object_ops<Derived, false> {};

struct moid_holder {
	constexpr moid_holder(__metaobject_id moid) noexcept
	  : _moid{moid} {
	}

	__metaobject_id _moid{};
};

struct metaobject
  : moid_holder
  , object_ops<metaobject, true> {
	constexpr metaobject(__metaobject_id moid) noexcept
	  : moid_holder{moid} {
	}
};

#define reflexpr(...)           \
	meta::detail::metaobject {  \
		__reflexpr(__VA_ARGS__) \
	}

} // namespace detail
} // namespace meta

#endif // P0953_HPP_
