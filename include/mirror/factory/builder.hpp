/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FACTORY_BUILDER_HPP
#define MIRROR_FACTORY_BUILDER_HPP

#include "../interface.hpp"
#include "utils.hpp"
#include <array>
#include <string_view>

namespace mirror {
//------------------------------------------------------------------------------
struct object_builder;
struct factory_constructor_parameter;
struct factory_constructor;
struct factory;
//------------------------------------------------------------------------------
template <typename Traits, typename Product, bool isAtomic, bool isCopy>
struct get_parameter_unit;

template <typename Traits, typename Product>
struct get_parameter_unit<Traits, Product, true, false> {
    using type = typename Traits::template atomic_unit<Product>;
};

template <typename Traits, typename Product>
struct get_parameter_unit<Traits, Product, false, false> {
    using type = typename Traits::template composite_unit<Product>;
};

template <typename Traits, typename Product, bool isAtomic>
struct get_parameter_unit<Traits, Product, isAtomic, true> {
    using type = typename Traits::template copy_unit<Product>;
};

template <typename Traits, typename Product, bool isCopy = false>
using factory_product_unit_t = typename get_parameter_unit<
  Traits,
  std::remove_reference_t<Product>,
  Traits::template is_atomic<std::remove_cv_t<std::remove_reference_t<Product>>>,
  isCopy>::type;
//------------------------------------------------------------------------------
template <typename Traits, typename Product, size_t CtrIdx, size_t ParamIdx>
using factory_parameter_unit_t = factory_product_unit_t<
  Traits,
  typename factory_utils<
    Product>::template constructor_parameter_type<CtrIdx, ParamIdx>,
  factory_utils<Product>::is_copy_constructor(CtrIdx) ||
    factory_utils<Product>::is_move_constructor(CtrIdx)>;

template <typename Traits, typename Product>
using factory_constructor_unit_t =
  typename Traits::template constructor_unit<Product>;

template <typename Traits, typename Product>
using factory_unit_t = typename Traits::template factory_unit<Product>;

template <typename Traits>
using factory_builder_unit_t = typename Traits::builder_unit;
//------------------------------------------------------------------------------
struct object_builder : interface<object_builder> {
    virtual auto as_parameter() const noexcept
      -> const factory_constructor_parameter* = 0;

    auto index() const noexcept -> size_t;

    virtual auto name() const noexcept -> std::string_view = 0;
};
//------------------------------------------------------------------------------
struct factory_constructor_parameter : object_builder {
    virtual auto parent_constructor() const noexcept
      -> const factory_constructor& = 0;
    virtual auto parameter_index() const noexcept -> size_t = 0;

    virtual auto type_name() const noexcept -> std::string_view = 0;

    auto parent_parameter() const noexcept
      -> const factory_constructor_parameter*;
};
//------------------------------------------------------------------------------
inline auto object_builder::index() const noexcept -> size_t {
    if(auto param = dynamic_cast<const factory_constructor_parameter*>(this)) {
        return param->parameter_index();
    }
    return 0;
}
//------------------------------------------------------------------------------
template <typename Traits, typename Product, size_t CtrIdx, size_t ParamIdx>
class factory_constructor_parameter_impl
  : public factory_constructor_parameter
  , private factory_parameter_unit_t<Traits, Product, CtrIdx, ParamIdx> {

    using utils = factory_utils<Product>;

    auto base_unit()
      -> factory_parameter_unit_t<Traits, Product, CtrIdx, ParamIdx>& {
        return *this;
    }

    auto base_parameter() const -> const factory_constructor_parameter& {
        return *this;
    }

    auto base_builder() -> object_builder& {
        return *this;
    }

public:
    using construction_context = typename Traits::construction_context;

    factory_constructor_parameter_impl(
      factory_constructor_unit_t<Traits, Product>& parent,
      const factory_constructor& parent_constructor)
      : factory_parameter_unit_t<
          Traits,
          Product,
          CtrIdx,
          ParamIdx>{parent, base_builder(), parent_constructor}
      , _parent_constructor{parent_constructor} {}

    auto parent_constructor() const noexcept
      -> const factory_constructor& final {
        return _parent_constructor;
    }

    auto parameter_index() const noexcept -> size_t final {
        return ParamIdx;
    }

    auto as_parameter() const noexcept
      -> const factory_constructor_parameter* final {
        return this;
    }

    auto type_name() const noexcept -> std::string_view final {
        return utils::constructor_parameter_type_name(CtrIdx, ParamIdx);
    }

    auto name() const noexcept -> std::string_view final {
        return utils::constructor_parameter_name(CtrIdx, ParamIdx);
    }

    auto get(construction_context context)
      -> decltype(base_unit().get(context, base_parameter())) {
        return base_unit().get(context, base_parameter());
    }

private:
    const factory_constructor& _parent_constructor;
};
//------------------------------------------------------------------------------
struct factory_constructor : interface<factory_constructor> {
    virtual auto parent_factory() const noexcept -> const factory& = 0;
    virtual auto constructor_index() const noexcept -> size_t = 0;

    virtual auto is_default_constructor() const noexcept -> bool = 0;
    virtual auto is_move_constructor() const noexcept -> bool = 0;
    virtual auto is_copy_constructor() const noexcept -> bool = 0;

    virtual auto parameter_count() const noexcept -> size_t = 0;

    virtual auto parameter(size_t index) const noexcept
      -> const factory_constructor_parameter& = 0;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product, size_t CtrIdx, typename ParamIdcs>
class factory_constructor_impl;

template <typename Traits, typename Product, size_t CtrIdx, size_t... ParamIdx>
class factory_constructor_impl<
  Traits,
  Product,
  CtrIdx,
  std::index_sequence<ParamIdx...>>
  : public factory_constructor
  , private factory_constructor_unit_t<Traits, Product>
  , private factory_constructor_parameter_impl<
      Traits,
      Product,
      CtrIdx,
      ParamIdx>... {

    using utils = factory_utils<Product>;

    template <size_t Idx>
    using _param =
      factory_constructor_parameter_impl<Traits, Product, CtrIdx, Idx>;

    auto base_unit() noexcept -> factory_constructor_unit_t<Traits, Product>& {
        return *this;
    }

    template <size_t Idx>
    auto base_param() noexcept -> _param<Idx>* {
        return this;
    }

    template <size_t Idx>
    auto base_param() const noexcept -> const _param<Idx>* {
        return this;
    }

public:
    using construction_context = typename Traits::construction_context;

    factory_constructor_impl(
      factory_unit_t<Traits, Product>& parent,
      const factory& parent_factory)
      : factory_constructor_unit_t<Traits, Product>{parent}
      , _param<ParamIdx>{base_unit(), *this}...
      , _parent_factory{parent_factory} {}

    auto parent_factory() const noexcept -> const factory& final {
        return _parent_factory;
    }

    auto constructor_index() const noexcept -> size_t final {
        return CtrIdx;
    }

    auto is_default_constructor() const noexcept -> bool final {
        return utils::is_default_constructor(CtrIdx);
    }

    auto is_move_constructor() const noexcept -> bool final {
        return utils::is_move_constructor(CtrIdx);
    }

    auto is_copy_constructor() const noexcept -> bool final {
        return utils::is_copy_constructor(CtrIdx);
    }

    auto parameter_count() const noexcept -> size_t final {
        return sizeof...(ParamIdx);
    }

    auto parameter(size_t index) const noexcept
      -> const factory_constructor_parameter& final {
        const std::
          array<const factory_constructor_parameter*, sizeof...(ParamIdx)>
            _parameters{{base_param<ParamIdx>()...}};
        return *_parameters[index];
    }

    auto construct(construction_context context) -> Product {
        return Product(base_param<ParamIdx>()->get(context)...);
    }

private:
    const factory& _parent_factory;
};
//------------------------------------------------------------------------------
struct factory : interface<factory> {
    virtual auto parent_builder() const noexcept -> const object_builder& = 0;

    virtual auto product_type_name() const noexcept -> std::string_view = 0;

    virtual auto constructor_count() const noexcept -> size_t = 0;

    virtual auto constructor(size_t index) const noexcept
      -> const factory_constructor& = 0;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product, typename CtrIdcs>
class factory_impl;

template <typename Traits, typename Product, size_t... CtrIdx>
class factory_impl<Traits, Product, std::index_sequence<CtrIdx...>>
  : public factory
  , private factory_unit_t<Traits, Product>
  , private factory_constructor_impl<
      Traits,
      Product,
      CtrIdx,
      typename factory_utils<Product>::template constructor_parameter_indices<
        CtrIdx>>... {

    static_assert(sizeof...(CtrIdx) > 0, "Product must have constructors");

    using utils = factory_utils<Product>;

    template <size_t Idx>
    using _ctr = factory_constructor_impl<
      Traits,
      Product,
      Idx,
      typename utils::template constructor_parameter_indices<Idx>>;

    auto base_unit() noexcept -> factory_unit_t<Traits, Product>& {
        return *this;
    }

    template <size_t Idx>
    auto base_ctr() noexcept -> _ctr<Idx>* {
        return this;
    }

    template <size_t Idx>
    auto base_ctr() const noexcept -> const _ctr<Idx>* {
        return this;
    }

public:
    using construction_context = typename Traits::construction_context;

    factory_impl(
      factory_builder_unit_t<Traits>& parent,
      const object_builder& parent_builder)
      : factory_unit_t<Traits, Product>{parent}
      , _ctr<CtrIdx>{base_unit(), *this}...
      , _parent_builder{parent_builder} {}

    factory_impl(
      factory_product_unit_t<Traits, Product>& parent,
      const object_builder& parent_builder)
      : factory_unit_t<Traits, Product>{parent}
      , _ctr<CtrIdx>{base_unit(), *this}...
      , _parent_builder{parent_builder} {}

    auto parent_builder() const noexcept -> const object_builder& final {
        return _parent_builder;
    }

    auto product_type_name() const noexcept -> std::string_view final {
        return {utils::product_type_name()};
    }

    auto constructor_count() const noexcept -> size_t final {
        return sizeof...(CtrIdx);
    }

    auto constructor(size_t index) const noexcept
      -> const factory_constructor& final {
        std::array<const factory_constructor*, sizeof...(CtrIdx)> ctrs{
          {base_ctr<CtrIdx>()...}};
        return *ctrs[index];
    }

    auto construct(construction_context context) -> Product {
        return _dispatch_constructor(
          context,
          base_unit().select_constructor(context, *static_cast<factory*>(this)),
          std::integer_sequence<size_t, sizeof...(CtrIdx)>{});
    }

private:
    template <size_t Idx>
    auto _do_construct(
      construction_context context,
      std::integer_sequence<size_t, Idx>) -> Product {
        if constexpr(Idx < sizeof...(CtrIdx)) {
            return base_ctr<Idx>()->construct(context);
        }
        throw std::runtime_error("failed to pick constructor");
    }

    auto _dispatch_constructor(
      construction_context context,
      size_t,
      std::integer_sequence<size_t, 0U> tag) -> Product {
        return _do_construct(context, tag);
    }

    template <size_t Idx>
    auto _dispatch_constructor(
      construction_context context,
      size_t index,
      std::integer_sequence<size_t, Idx> tag) -> Product {
        if(index == Idx) {
            return _do_construct(context, tag);
        }
        return _dispatch_constructor(
          context, index, std::integer_sequence<size_t, Idx - 1>{});
    }

    const object_builder& _parent_builder;
};
//------------------------------------------------------------------------------
template <typename Traits>
class factory_builder
  : public object_builder
  , private factory_builder_unit_t<Traits> {

    auto base_unit() noexcept -> factory_builder_unit_t<Traits>& {
        return *this;
    }

public:
    template <typename... Args>
    factory_builder(std::string name, Args&&... args)
      : factory_builder_unit_t<Traits>{args...}
      , _name{std::move(name)} {}

    template <typename Product>
    using factory_type = factory_impl<
      Traits,
      Product,
      typename factory_utils<Product>::constructor_indices>;

    template <typename Product>
    auto build() noexcept {
        return factory_type<Product>{base_unit(), *this};
    }

    auto as_parameter() const noexcept
      -> const factory_constructor_parameter* final {
        return nullptr;
    }

    auto name() const noexcept -> std::string_view final {
        return {_name};
    }

private:
    std::string _name;
};
//------------------------------------------------------------------------------
inline auto factory_constructor_parameter::parent_parameter() const noexcept
  -> const factory_constructor_parameter* {
    return parent_constructor().parent_factory().parent_builder().as_parameter();
}
//------------------------------------------------------------------------------
template <typename Traits, typename Product>
using built_factory_type =
  typename factory_builder<Traits>::template factory_type<Product>;
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_BUILDER_HPP
