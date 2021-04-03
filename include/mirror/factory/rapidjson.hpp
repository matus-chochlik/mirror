/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FACTORY_RAPIDJSON_HPP
#define MIRROR_FACTORY_RAPIDJSON_HPP

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/rapidjson.h>

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

namespace mirror {
//------------------------------------------------------------------------------
struct rapidjson_factory_traits {
    struct builder_unit;

    template <typename Product>
    struct factory_unit;

    template <typename Product>
    struct constructor_unit;

    template <typename T>
    struct atomic_unit;

    template <typename T>
    struct composite_unit;

    template <typename T>
    struct copy_unit;

    struct construction_context {
        rapidjson::Value& root;
    };

    struct builder_unit {};

    template <typename Product>
    struct factory_unit {
        factory_unit(const builder_unit&) {}
        factory_unit(const composite_unit<Product>&) {}

        auto select_constructor(construction_context& ctx, const factory& fac)
          -> size_t {
            (void)ctx;
            (void)fac;
            return 0;
        }
    };

    template <typename Product>
    struct constructor_unit {
        constructor_unit(const factory_unit<Product>&) {}
    };

    template <typename T>
    static constexpr bool is_atomic =
      std::is_floating_point_v<T> || std::is_integral_v<T> ||
      std::is_same_v<T, std::string>;

    template <typename T>
    struct atomic_unit {
        template <typename P>
        atomic_unit(const constructor_unit<P>&, const object_builder&) {}

        auto
        get(construction_context& ctx, const factory_constructor_parameter& p) {
            (void)ctx;
            (void)p;
            return T{};
        }
    };

    template <typename T>
    struct composite_unit {
        template <typename P>
        composite_unit(const constructor_unit<P>&, const object_builder& builder)
          : fac{*this, builder} {}

        auto
        get(construction_context& ctx, const factory_constructor_parameter&) {
            return fac.construct(ctx);
        }

        built_factory_type<rapidjson_factory_traits, T> fac;
    };

    template <typename T>
    struct copy_unit {
        template <typename P>
        copy_unit(const constructor_unit<P>&, const object_builder&) {}

        auto get(construction_context&, const factory_constructor_parameter&)
          -> T {
            return T{};
        }
    };
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif
