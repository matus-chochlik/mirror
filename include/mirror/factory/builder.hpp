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
#include <string_view>

namespace mirror {
//------------------------------------------------------------------------------
struct factory_constructor_parameter
  : interface<factory_constructor_parameter> {

    virtual auto name() const noexcept -> std::string_view = 0;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product, size_t CtrIdx, size_t ParamIdx>
class factory_constructor_parameter_impl
  : public factory_constructor_parameter
  , private Traits::template parameter_unit<Product> {

    using parent_unit = typename Traits::template constructor_unit<Product>;
    using base_unit = typename Traits::template parameter_unit<Product>;

public:
    factory_constructor_parameter_impl(parent_unit& parent)
      : base_unit{parent} {}

    auto name() const noexcept -> std::string_view final {
        return factory_utils<Product>().constructor_parameter_name(
          CtrIdx, ParamIdx);
    }
};
//------------------------------------------------------------------------------
struct factory_constructor : interface<factory_constructor> {
    virtual auto parameter_count() const noexcept -> std::size_t = 0;

    virtual auto parameter(size_t index) noexcept
      -> factory_constructor_parameter& = 0;
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
  , private Traits::template constructor_unit<Product>
  , private factory_constructor_parameter_impl<
      Traits,
      Product,
      CtrIdx,
      ParamIdx>... {

    using parent_unit = typename Traits::template factory_unit<Product>;
    using base_unit = typename Traits::template constructor_unit<Product>;

    template <size_t Idx>
    using _param =
      factory_constructor_parameter_impl<Traits, Product, CtrIdx, Idx>;

public:
    factory_constructor_impl(parent_unit& parent)
      : base_unit{parent}
      , _param<ParamIdx>{static_cast<base_unit&>(*this)}... {}

    auto parameter_count() const noexcept -> std::size_t final {
        return sizeof...(ParamIdx);
    }

    auto parameter(size_t index) noexcept
      -> factory_constructor_parameter& final {
        const std::array<factory_constructor_parameter*, sizeof...(ParamIdx)>
          _parameters{{static_cast<_param<ParamIdx>*>(this)...}};
        return *_parameters[index];
    }
};
//------------------------------------------------------------------------------
struct factory : interface<factory> {
    virtual auto constructor_count() const noexcept -> std::size_t = 0;

    virtual auto constructor(size_t index) noexcept -> factory_constructor& = 0;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product, typename CtrIdcs>
class factory_impl;

template <typename Traits, typename Product, size_t... CtrIdx>
class factory_impl<Traits, Product, std::index_sequence<CtrIdx...>>
  : public factory
  , private Traits::template factory_unit<Product>
  , private factory_constructor_impl<
      Traits,
      Product,
      CtrIdx,
      typename factory_utils<Product>::template constructor_parameter_indices<
        CtrIdx>>... {

    using parent_unit = typename Traits::template builder_unit<Product>;
    using base_unit = typename Traits::template factory_unit<Product>;
    using utils = factory_utils<Product>;

    template <size_t Idx>
    using _ctr = factory_constructor_impl<
      Traits,
      Product,
      Idx,
      typename utils::template constructor_parameter_indices<Idx>>;

public:
    factory_impl(parent_unit& parent)
      : base_unit{parent}
      , _ctr<CtrIdx>{static_cast<base_unit&>(*this)}... {}

    auto constructor_count() const noexcept -> size_t final {
        return sizeof...(CtrIdx);
    }

    auto constructor(size_t index) noexcept -> factory_constructor& final {
        std::array<factory_constructor*, sizeof...(CtrIdx)> ctrs{
          {static_cast<_ctr<CtrIdx>*>(this)...}};
        return *ctrs[index];
    }
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product>
class factory_builder : private Traits::template builder_unit<Product> {
    using base_unit = typename Traits::template builder_unit<Product>;
    using utils = factory_utils<Product>;

public:
    template <typename... Args>
    factory_builder(Args&&... args)
      : base_unit{args...} {}

    auto build() noexcept {
        using impl =
          factory_impl<Traits, Product, typename utils::constructor_indices>;
        return impl{static_cast<base_unit&>(*this)};
    }
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_BUILDER_HPP
