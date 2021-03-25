/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FACTORY_HPP
#define MIRROR_FACTORY_HPP

#include "interface.hpp"
#include "meta.hpp"
#include "utils.hpp"
#include <string_view>

namespace mirror {

template <typename T>
struct factory_utils {
    consteval static auto constructors() {
        return std::experimental::meta::members_of(
          ^T, std::experimental::meta::is_constructor);
    }

    consteval static auto constructor_count() {
        return size(constructors());
    }

    using constructor_indices = std::make_index_sequence<constructor_count()>;

    consteval static auto constructor(size_t i)
      -> std::experimental::meta::info {
        return *advance(constructors().begin(), i);
    }

    consteval static auto constructor_parameters(size_t i) {
        return std::experimental::meta::parameters_of(constructor(i));
    }

    consteval static auto constructor_parameter_count(size_t i) {
        return size(constructor_parameters(i));
    }

    template <size_t I>
    using constructor_parameter_indices =
      std::make_index_sequence<constructor_parameter_count(I)>;

    consteval static auto constructor_parameter(size_t i, size_t j)
      -> std::experimental::meta::info {
        return *advance(constructor_parameters(i).begin(), j);
    }

    consteval static auto constructor_parameter_name(size_t i, size_t j) {
        return std::experimental::meta::name_of(constructor_parameter(i, j));
    }
};

struct factory_constructor_parameter
  : interface<factory_constructor_parameter> {

    virtual auto name() const noexcept -> std::string_view = 0;
};

template <typename Traits, typename Product, size_t CtrIdx, size_t ParamIdx>
class factory_constructor_parameter_impl
  : public factory_constructor_parameter {
public:
    auto name() const noexcept -> std::string_view final {
        return factory_utils<Product>().constructor_parameter_name(
          CtrIdx, ParamIdx);
    }
};

struct factory_constructor : interface<factory_constructor> {
    virtual auto parameter_count() const noexcept -> std::size_t = 0;

    virtual auto parameter(size_t index) noexcept
      -> factory_constructor_parameter& = 0;
};

template <typename Traits, typename Product, size_t CtrIdx, typename ParamIdcs>
class factory_constructor_impl;

template <typename Traits, typename Product, size_t CtrIdx, size_t... ParamIdx>
class factory_constructor_impl<
  Traits,
  Product,
  CtrIdx,
  std::index_sequence<ParamIdx...>>
  : public factory_constructor
  , private factory_constructor_parameter_impl<
      Traits,
      Product,
      CtrIdx,
      ParamIdx>... {

    template <size_t Idx>
    using _param =
      factory_constructor_parameter_impl<Traits, Product, CtrIdx, Idx>;

public:
    auto parameter_count() const noexcept -> std::size_t final {
        return sizeof...(ParamIdx);
    }

    auto parameter(size_t index) noexcept
      -> factory_constructor_parameter& final {
        const std::array<factory_constructor_parameter*, sizeof...(ParamIdx)>
          _parameters{{static_cast<_param<ParamIdx>*>(this)...}};
        return *_parameters[index];
    }

private:
};

struct factory : interface<factory> {
    virtual auto constructor_count() const noexcept -> std::size_t = 0;

    virtual auto constructor(size_t index) noexcept -> factory_constructor& = 0;
};

template <typename Traits, typename Product, typename CtrIdcs>
class factory_impl;

template <typename Traits, typename Product, size_t... CtrIdx>
class factory_impl<Traits, Product, std::index_sequence<CtrIdx...>>
  : public factory
  , private factory_constructor_impl<
      Traits,
      Product,
      CtrIdx,
      typename factory_utils<Product>::template constructor_parameter_indices<
        CtrIdx>>... {

    using utils = factory_utils<Product>;

    template <size_t Idx>
    using _ctr = factory_constructor_impl<
      Traits,
      Product,
      Idx,
      typename utils::template constructor_parameter_indices<Idx>>;

public:
    auto constructor_count() const noexcept -> size_t final {
        return sizeof...(CtrIdx);
    }

    auto constructor(size_t index) noexcept -> factory_constructor& final {
        std::array<factory_constructor*, sizeof...(CtrIdx)> ctrs{
          {static_cast<_ctr<CtrIdx>*>(this)...}};
        return *ctrs[index];
    }
};

template <typename Traits, typename Product>
class factory_builder {
    using utils = factory_utils<Product>;

public:
    auto build() noexcept {
        return factory_impl<
          Traits,
          Product,
          typename utils::constructor_indices>{};
    }

private:
};

} // namespace mirror

#endif // MIRROR_FACTORY_HPP
