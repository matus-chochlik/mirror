/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_QT5_TRAITS_HPP
#define MIRROR_FACTORY_QT5_TRAITS_HPP

#include "AtomicViewModel.hpp"
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
    using construction_context_param = const construction_context&;

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
    qt5_factory_unit(
      const qt5_factory_builder_unit& parent_unit,
      const factory&) {
        parent_unit.view_model().addFactory(view_model());
    }

    qt5_factory_unit(
      const qt5_factory_composite_unit<Product>&,
      const factory&) {}

    auto
    select_constructor(const qt5_factory_construction_context&, const factory&)
      -> size_t {
        return view_model().getSelectedIndex();
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    static auto toQString(std::string_view s) {
        return QString::fromStdString(std::string(s));
    }

    std::unique_ptr<FactoryViewModel> _view_model{
      std::make_unique<FactoryViewModel>(
        toQString(get_name(remove_all_aliases(mirror(Product)))))};
};
//------------------------------------------------------------------------------
template <typename Product>
class qt5_factory_constructor_unit {
public:
    qt5_factory_constructor_unit(
      const qt5_factory_unit<Product>& parent_unit,
      const factory_constructor& ctr)
      : _view_model{std::make_unique<ConstructorViewModel>(
          ctr.is_default_constructor(),
          ctr.is_move_constructor(),
          ctr.is_copy_constructor())} {
        parent_unit.view_model().addConstructor(view_model());
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    std::unique_ptr<ConstructorViewModel> _view_model;
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_atomic_unit {
public:
    template <typename P>
    qt5_factory_atomic_unit(
      const qt5_factory_constructor_unit<P>& parent_unit,
      const factory_constructor_parameter& parameter)
      : _atomic_model{_make_atomic(static_cast<T*>(nullptr))}
      , _view_model{std::make_unique<ParameterViewModel>(
          QString(parameter.type_name().data()),
          QString(parameter.name().data()),
          static_cast<QObject*>(_atomic_model.get()))} {
        parent_unit.view_model().addParameter(view_model());
    }

    auto get(
      const qt5_factory_construction_context&,
      const factory_constructor_parameter&) {
        return _get_atomic(static_cast<T*>(nullptr))
          .get(static_cast<T*>(nullptr));
    }

    auto view_model() const noexcept -> auto& {
        return *_view_model;
    }

private:
    template <typename X>
    struct _get_atomic_model {
        using type = std::conditional_t<
          std::is_floating_point_v<X>,
          FloatViewModel,
          StringViewModel>;
    };

    template <typename X>
    using _atomic_model_t = typename _get_atomic_model<X>::type;

    template <typename X>
    static auto _make_atomic(X*) -> std::unique_ptr<AtomicViewModel> {
        return std::make_unique<_atomic_model_t<X>>();
    }

    template <typename X>
    auto _get_atomic(X*) -> typename _get_atomic_model<X>::type& {
        return *static_cast<_atomic_model_t<X>*>(_atomic_model.get());
    }

    std::unique_ptr<AtomicViewModel> _atomic_model;
    std::unique_ptr<ParameterViewModel> _view_model;
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_composite_unit {
public:
    template <typename P>
    qt5_factory_composite_unit(
      const qt5_factory_constructor_unit<P>& parent_unit,
      const factory_constructor_parameter& parameter)
      : _factory{*this, parameter}
      , _view_model{std::make_unique<ParameterViewModel>(
          QString(parameter.type_name().data()),
          QString(parameter.name().data()))} {
        parent_unit.view_model().addParameter(view_model());
        view_model().addFactory(_factory.base_unit().view_model());
    }

    auto get(
      const qt5_factory_construction_context& ctx,
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
      const factory_constructor_parameter&) {}

    auto get(
      const qt5_factory_construction_context,
      const factory_constructor_parameter&) {
        return T{};
    }
};
//------------------------------------------------------------------------------
template <typename Product>
using qt5_product_factory = product_factory<qt5_factory_traits, Product>;
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_IOSTREAM_HPP

