enum Dummy { a, b, c };

class metaobject {
public:
  constexpr metaobject(__metaobject_id mo) noexcept : _mo{mo} {}

  constexpr bool is_named() const noexcept {
    return __metaobject_is_meta_named(_mo);
  }

  constexpr bool is_type() const noexcept {
    return __metaobject_is_meta_type(_mo);
  }

  constexpr bool is_scope() const noexcept {
    return __metaobject_is_meta_scope(_mo);
  }

  constexpr metaobject get_scope() const noexcept {
    return {__metaobject_get_scope(_mo)};
  }

protected:
  const __metaobject_id _mo;
};

#define reflexpr(...)                                                          \
  metaobject { __reflexpr(__VA_ARGS__) }
