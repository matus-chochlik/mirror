/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_QT5_TRAITS_HPP
#define MIRROR_FACTORY_QT5_TRAITS_HPP

#include "BuilderViewModel.hpp"
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
    qt5_factory_builder_unit(QObject*) {}
};
//------------------------------------------------------------------------------
template <typename Product>
class qt5_factory_unit {
public:
    qt5_factory_unit(const qt5_factory_builder_unit&) {}
    qt5_factory_unit(const qt5_factory_composite_unit<Product>&) {}

    auto select_constructor(qt5_factory_construction_context&, const factory&)
      -> size_t {
        return 0;
    }

private:
};
//------------------------------------------------------------------------------
template <typename Product>
class qt5_factory_constructor_unit {
public:
    qt5_factory_constructor_unit(const qt5_factory_unit<Product>&) {}

private:
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_atomic_unit {
public:
    template <typename P>
    qt5_factory_atomic_unit(
      const qt5_factory_constructor_unit<P>&,
      const object_builder&,
      const factory_constructor&) {}

    auto get(
      qt5_factory_construction_context&,
      const factory_constructor_parameter&) {
        std::remove_reference_t<T> result{};
        return result;
    }
};
//------------------------------------------------------------------------------
template <typename T>
class qt5_factory_composite_unit {
public:
    template <typename P>
    qt5_factory_composite_unit(
      const qt5_factory_constructor_unit<P>&,
      const object_builder& builder,
      const factory_constructor&)
      : fac{*this, builder} {}

    auto get(
      qt5_factory_construction_context& ctx,
      const factory_constructor_parameter&) {
        return fac.construct(ctx);
    }

private:
    built_factory_type<qt5_factory_traits, T> fac;
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

