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
    class builder_unit;

    template <typename Product>
    class factory_unit;

    template <typename Product>
    class constructor_unit;

    template <typename T>
    class atomic_unit;

    template <typename T>
    class composite_unit;

    template <typename T>
    class copy_unit;

    struct construction_context {
        rapidjson::Value& root;
    };

    class builder_unit {};

    template <typename Product>
    class factory_unit {
    public:
        factory_unit(const builder_unit&) noexcept {}
        factory_unit(const composite_unit<Product>& parent) noexcept
          : _parent{&parent} {}

        auto select_constructor(construction_context& ctx, const factory& fac)
          -> size_t {
            (void)ctx;
            (void)fac;
            return 1;
        }

        auto path() const noexcept -> std::string {
            return _parent ? _parent->path() : std::string{};
        }

    private:
        const composite_unit<Product>* _parent{nullptr};
    };

    template <typename Product>
    class constructor_unit {
    public:
        constructor_unit(const factory_unit<Product>& parent) noexcept
          : _parent{parent} {}

        auto path() const noexcept -> std::string {
            return _parent.path();
        }

    private:
        const factory_unit<Product>& _parent;
    };

    template <typename T>
    static constexpr bool is_atomic =
      std::is_floating_point_v<T> || std::is_integral_v<T> ||
      std::is_same_v<T, std::string>;

    static auto
    do_make_path(std::string path, std::string name, bool copy) noexcept
      -> std::string {
        std::string result;
        if(!path.empty()) {
            result.append(path);
            result.append(".");
        }
        if(name.empty()) {
            if(copy) {
                result.append("that");
            } else {
                result.append("x");
            }
        } else {
            result.append(name);
        }
        return result;
    }

    template <typename P>
    static auto make_path(
      const constructor_unit<P>& parent,
      const object_builder& builder,
      const factory_constructor& constructor) noexcept -> std::string {
        return do_make_path(
          parent.path(),
          std::string(builder.name()),
          constructor.is_copy_constructor());
    }

    template <typename T>
    class atomic_unit {
    public:
        template <typename P>
        atomic_unit(
          const constructor_unit<P>& parent,
          const object_builder& builder,
          const factory_constructor& constructor) noexcept
          : _path{make_path(parent, builder, constructor)} {}

        auto
        get(construction_context& ctx, const factory_constructor_parameter& p) {
            (void)ctx;
            (void)p;
            return T{};
        }

        auto path() const noexcept -> const std::string& {
            return _path;
        }

    private:
        std::string _path;
    };

    template <typename T>
    class composite_unit {
    public:
        template <typename P>
        composite_unit(
          const constructor_unit<P>& parent,
          const object_builder& builder,
          const factory_constructor& constructor) noexcept
          : _path{make_path(parent, builder, constructor)}
          , _fac{*this, builder} {}

        auto
        get(construction_context& ctx, const factory_constructor_parameter&) {
            return _fac.construct(ctx);
        }

        auto path() const noexcept -> const std::string& {
            return _path;
        }

    private:
        std::string _path;
        built_factory_type<rapidjson_factory_traits, T> _fac;
    };

    template <typename T>
    class copy_unit {
    public:
        template <typename P>
        copy_unit(
          const constructor_unit<P>& parent,
          const object_builder& builder,
          const factory_constructor& constructor)
          : _path{make_path(parent, builder, constructor)} {}

        auto get(construction_context&, const factory_constructor_parameter&)
          -> T {
            return T{};
        }

        auto path() const noexcept -> const std::string& {
            return _path;
        }

    private:
        std::string _path;
    };
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif
