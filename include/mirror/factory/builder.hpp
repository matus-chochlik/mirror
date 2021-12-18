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
#include "../unit_composition.hpp"
#include <functional>
#include <stdexcept>
#include <string>

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
template <typename Traits, typename Product>
using factory_unit_t = typename Traits::template factory_unit<Product>;

template <typename Traits>
using factory_builder_unit_t = typename Traits::builder_unit;

template <typename Traits, typename Product, typename MetaCtr, typename MetaParam>
using factory_parameter_unit_t = factory_product_unit_t<
  Traits,
  typename decltype(get_reflected_type(get_type(MetaParam{})))::type,
  is_copy_constructor(MetaCtr{}) || is_move_constructor(MetaCtr{})>;

template <typename Traits, typename Product>
using factory_constructor_unit_t =
  typename Traits::template constructor_unit<Product>;
//------------------------------------------------------------------------------
struct object_builder : interface<object_builder> {
    virtual auto as_parameter() const noexcept
      -> const factory_constructor_parameter* = 0;

    auto index() const noexcept -> size_t;

    auto type_name() const noexcept -> std::string_view;

    virtual auto name() const noexcept -> std::string_view = 0;
};
//------------------------------------------------------------------------------
struct factory_constructor_parameter : object_builder {
    virtual auto parent_constructor() const noexcept
      -> const factory_constructor& = 0;

    virtual auto parameter_index() const noexcept -> size_t = 0;

    virtual auto parameter_type_name() const noexcept -> std::string_view = 0;

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
inline auto object_builder::type_name() const noexcept -> std::string_view {
    if(auto param = dynamic_cast<const factory_constructor_parameter*>(this)) {
        return param->parameter_type_name();
    }
    return {};
}
//------------------------------------------------------------------------------
template <typename Traits, typename Product, typename MetaCtr, typename MetaParam>
class factory_constructor_parameter_impl
  : public factory_constructor_parameter {
    static constexpr const MetaParam _meta_param{};

    const size_t _index{0};
    const factory_constructor& _parent_constructor;
    factory_parameter_unit_t<Traits, Product, MetaCtr, MetaParam> _base_unit;

    auto base_parameter() const -> const factory_constructor_parameter& {
        return *this;
    }

    auto base_builder() -> object_builder& {
        return *this;
    }

public:
    using construction_context_param =
      typename Traits::construction_context_param;

    auto base_unit() noexcept -> auto& {
        return _base_unit;
    }

    factory_constructor_parameter_impl(
      factory_constructor_unit_t<Traits, Product>& parent,
      const factory_constructor& parent_constructor,
      size_t& index_init_counter)
      : _index{index_init_counter++}
      , _parent_constructor{parent_constructor}
      , _base_unit{parent, static_cast<factory_constructor_parameter&>(*this)} {
    }

    auto parent_constructor() const noexcept
      -> const factory_constructor& final {
        return _parent_constructor;
    }

    auto parameter_index() const noexcept -> size_t final {
        return _index;
    }

    auto as_parameter() const noexcept
      -> const factory_constructor_parameter* final {
        return this;
    }

    auto parameter_type_name() const noexcept -> std::string_view final {
        return get_name(get_type(_meta_param));
    }

    auto name() const noexcept -> std::string_view final {
        return get_name(_meta_param);
    }

    auto get(construction_context_param context)
      -> decltype(base_unit().get(context, base_parameter())) {
        return base_unit().get(context, base_parameter());
    }
};
//------------------------------------------------------------------------------
struct factory_constructor : interface<factory_constructor> {
    virtual auto parent_factory() const noexcept -> const factory& = 0;

    virtual auto is_default_constructor() const noexcept -> bool = 0;
    virtual auto is_move_constructor() const noexcept -> bool = 0;
    virtual auto is_copy_constructor() const noexcept -> bool = 0;

    virtual auto parameter_count() const noexcept -> size_t = 0;

    virtual auto parameter(size_t index) const noexcept
      -> const factory_constructor_parameter& = 0;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product>
struct factory_product_constructor : factory_constructor {
    virtual auto construct(typename Traits::construction_context_param context)
      -> Product = 0;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product, typename MetaCtr>
class factory_constructor_impl
  : public factory_product_constructor<Traits, Product> {

    static constexpr const MetaCtr _meta_ctr{};

    factory_constructor_unit_t<Traits, Product> _base_unit;

    auto base_constructor() const noexcept -> const factory_constructor& {
        return *this;
    }

    template <typename MetaParam>
    using _parameter_impl =
      factory_constructor_parameter_impl<Traits, Product, MetaCtr, MetaParam>;

    unit_composition<_parameter_impl, decltype(get_parameters(_meta_ctr))>
      _parameters;

    const factory& _parent_factory;

public:
    using construction_context_param =
      typename Traits::construction_context_param;

    auto base_unit() noexcept -> auto& {
        return _base_unit;
    }

    factory_constructor_impl(
      factory_unit_t<Traits, Product>& parent,
      const factory& parent_factory,
      size_t index_init_counter = 0)
      : _base_unit{parent, static_cast<factory_constructor&>(*this)}
      , _parameters{base_unit(), *this, index_init_counter}
      , _parent_factory{parent_factory} {}

    auto parent_factory() const noexcept -> const factory& final {
        return _parent_factory;
    }

    auto is_default_constructor() const noexcept -> bool final {
        return is_empty(get_parameters(_meta_ctr));
    }

    auto is_move_constructor() const noexcept -> bool final {
        return mirror::is_move_constructor(_meta_ctr);
    }

    auto is_copy_constructor() const noexcept -> bool final {
        return mirror::is_copy_constructor(_meta_ctr);
    }

    auto parameter_count() const noexcept -> size_t final {
        return get_size(get_parameters(_meta_ctr));
    }

    auto parameter(size_t index) const noexcept
      -> const factory_constructor_parameter& final {
        return get_element<factory_constructor_parameter>(_parameters, index);
    }

    auto construct(construction_context_param context) -> Product final {
        return apply(_parameters, [&](auto&... mp) {
            return Product(mp.get(context)...);
        });
    }
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
struct factory_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};
//------------------------------------------------------------------------------
template <typename Traits, typename Product, typename MetaType>
class factory_impl : public factory {

private:
    static constexpr const MetaType _meta_type{};

    factory_unit_t<Traits, Product> _base_unit;

    template <typename MetaCtr>
    using _constructor_impl =
      factory_constructor_impl<Traits, Product, MetaCtr>;

    unit_composition<_constructor_impl, decltype(get_constructors(_meta_type))>
      _constructors;

    const object_builder& _parent_builder;

public:
    using construction_context_param =
      typename Traits::construction_context_param;

    auto base_unit() noexcept -> auto& {
        return _base_unit;
    }

    factory_impl(
      factory_builder_unit_t<Traits>& parent,
      const object_builder& parent_builder)
      : _base_unit{parent, static_cast<factory&>(*this)}
      , _constructors{_base_unit, *this}
      , _parent_builder{parent_builder} {}

    factory_impl(
      factory_product_unit_t<Traits, Product>& parent,
      const object_builder& parent_builder)
      : _base_unit{parent, static_cast<factory&>(*this)}
      , _constructors{_base_unit, *this}
      , _parent_builder{parent_builder} {}

    auto parent_builder() const noexcept -> const object_builder& final {
        return _parent_builder;
    }

    auto product_type_name() const noexcept -> std::string_view final {
        return get_name(_meta_type);
    }

    auto constructor_count() const noexcept -> size_t final {
        return get_size(get_constructors(_meta_type));
    }

    auto constructor(size_t index) const noexcept
      -> const factory_constructor& final {
        return get_element<factory_constructor>(_constructors, index);
    }

    auto construct(construction_context_param context) -> Product {
        using ctr_t = factory_product_constructor<Traits, Product>;
        const size_t index =
          base_unit().select_constructor(context, static_cast<factory&>(*this));
        if(index >= constructor_count()) {
            throw factory_error("failed to find appropriate constructors");
        }
        return get_element<ctr_t>(_constructors, index).construct(context);
    }
};
//------------------------------------------------------------------------------
template <typename Traits>
class factory_builder : public object_builder {

private:
    factory_builder_unit_t<Traits> _base_unit;
    std::string _name;

public:
    auto base_unit() noexcept -> auto& {
        return _base_unit;
    }

    template <typename... Args>
    factory_builder(std::string name, Args&&... args)
      : _base_unit{args...}
      , _name{std::move(name)} {}

    template <typename Product>
    using factory_type = factory_impl<
      Traits,
      // this is here to force the compiler to create copy/move constructors
      decltype(Product(std::declval<const Product&>())),
      decltype(get_aliased(mirror(Product)))>;

    template <typename Product>
    auto build() noexcept -> factory_type<Product> {
        return {base_unit(), *this};
    }

    auto as_parameter() const noexcept
      -> const factory_constructor_parameter* final {
        return nullptr;
    }

    auto name() const noexcept -> std::string_view final {
        return {_name};
    }
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
