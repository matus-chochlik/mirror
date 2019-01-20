enum Dummy { a, b, c };

static constexpr inline bool is_named(__metaobject_id mo) noexcept {
  return __metaobject_is_meta_named(mo);
}

static constexpr inline bool is_type(__metaobject_id mo) noexcept {
  return __metaobject_is_meta_type(mo);
}

static constexpr inline bool is_scope(__metaobject_id mo) noexcept {
  return __metaobject_is_meta_scope(mo);
}

static constexpr inline __metaobject_id get_scope(__metaobject_id mo) noexcept {
  return __metaobject_get_scope(mo);
}

#define reflexpr(...) __reflexpr(__VA_ARGS__)
