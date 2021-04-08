/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_QT5_TRAITS_HPP
#define MIRROR_FACTORY_QT5_TRAITS_HPP

#include "BuilderViewModel.hpp"
#include "ConstructorViewModel.hpp"
#include "FactoryViewModel.hpp"
#include "ParameterViewModel.hpp"
#include <memory>
#include <mirror/factory/builder.hpp>

namespace mirror {
//------------------------------------------------------------------------------
struct qt5_factory_traits;
class qt5_factory_builder_unit;
template <typename Product>
class qt5_factory_unit;
template <typename Product>
class qt5_factory_constructor_unit;
template <typename Product>
class qt5_factory_constructor_unit;
template <typename T>
class qt5_factory_atomic_unit;
template <typename T>
class qt5_factory_composite_unit;
template <typename T>
class qt5_factory_copy_unit;
//------------------------------------------------------------------------------
struct qt5_factory_construction_context {};
//------------------------------------------------------------------------------
struct qt5_factory_traits {
    using builder_unit = qt5_factory_builder_unit;

    template <typename Product>
    using factory_unit = qt5_factory_unit<Product>;

    template <typename Product>
    using constructor_unit = qt5_factory_constructor_unit<Product>;

    template <typename T>
    using atomic_unit = qt5_factory_atomic_unit<T>;

    template <typename T>
    using composite_unit = qt5_factory_composite_unit<T>;

    template <typename T>
    using copy_unit = qt5_factory_copy_unit<T>;

    using construction_context = qt5_factory_construction_context;

    template <typename T>
    static constexpr bool is_atomic =
      std::is_floating_point_v<T> || std::is_integral_v<T> ||
      std::is_same_v<T, std::string>;
};
//------------------------------------------------------------------------------
class qt5_factory_builder_unit {
public:
    qt5_factory_builder_unit(qt5_factory_builder_unit&&) noexcept = default;
    qt5_factory_builder_unit(const qt5_factory_builder_unit&) = delete;
    auto operator=(qt5_factory_builder_unit&&) = delete;
    auto operator=(const qt5_factory_builder_unit&) = delete;
    qt5_factory_builder_unit() = default;

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    std::unique_ptr<BuilderViewModel> _view_model{
      std::make_unique<BuilderViewModel>()};
};
//------------------------------------------------------------------------------
template <typename Product>
class qt5_factory_unit {
public:
    qt5_factory_unit(const qt5_factory_builder_unit& parent_unit) {
        parent_unit.view_model().addFactory(view_model());
    }
    qt5_factory_unit(const qt5_factory_composite_unit<Product>&) {}

    auto select_constructor(qt5_factory_construction_context&, const factory&)
      -> size_t {
        return 0;
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    std::unique_ptr<FactoryViewModel> _view_model{
      std::make_unique<FactoryViewModel>(
        QString(factory_utils<Product>::product_type_name()))};
};
//------------------------------------------------------------------------------
template <typename Product>
class qt5_factory_constructor_unit {
public:
    qt5_factory_constructor_unit(const qt5_factory_unit<Product>& parent_unit) {
        parent_unit.view_model().addConstructor(view_model());
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    std::unique_ptr<ConstructorViewModel> _view_model{
      std::make_unique<ConstructorViewModel>()};
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_atomic_unit {
public:
    template <typename P>
    qt5_factory_atomic_unit(
      const qt5_factory_constructor_unit<P>& parent_unit,
      const object_builder& builder,
      const factory_constructor&)
      : _view_model{std::make_unique<ParameterViewModel>(
          QString(builder.type_name().data()),
          QString(builder.name().data()),
          _unit(static_cast<T*>(nullptr)))} {
        parent_unit.view_model().addParameter(view_model());
    }

    auto get(
      qt5_factory_construction_context&,
      const factory_constructor_parameter&) {
        std::remove_reference_t<T> result{};
        return result;
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    template <typename X>
    static auto _unit(X*) -> QString {
        return "String";
    }

    static auto _unit(float*) -> QString {
        return "Float";
    }

    static auto _unit(double*) -> QString {
        return "Float";
    }

    static auto _unit(bool*) -> QString {
        return "Bool";
    }

    std::unique_ptr<ParameterViewModel> _view_model{
      std::make_unique<ParameterViewModel>()};
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_composite_unit {
public:
    template <typename P>
    qt5_factory_composite_unit(
      const qt5_factory_constructor_unit<P>& parent_unit,
      const object_builder& builder,
      const factory_constructor&)
      : _factory{*this, builder}
      , _view_model{std::make_unique<ParameterViewModel>(
          QString(builder.type_name().data()),
          QString(builder.name().data()),
          QString("Composite"))} {
        parent_unit.view_model().addParameter(view_model());
        view_model().addFactory(_factory.base_unit().view_model());
    }

    auto get(
      qt5_factory_construction_context& ctx,
      const factory_constructor_parameter&) {
        return _factory.construct(ctx);
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    built_factory_type<qt5_factory_traits, T> _factory;
    std::unique_ptr<ParameterViewModel> _view_model;
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_copy_unit {
public:
    template <typename P>
    qt5_factory_copy_unit(
      const qt5_factory_constructor_unit<P>&,
      const object_builder&,
      const factory_constructor&) {}

    auto get(
      qt5_factory_construction_context,
      const factory_constructor_parameter&) {
        return T{};
    }
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_IOSTREAM_HPP

