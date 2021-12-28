/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FACTORY_RAPIDJSON_HPP
#define MIRROR_FACTORY_RAPIDJSON_HPP

#include "../diagnostic.hpp"
#include <cassert>
#include <tuple>
#include <vector>

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(zero-as-null-pointer-constant)
#endif

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/rapidjson.h>

#if defined(__clang__)
MIRROR_DIAG_POP()
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
        rapidjson::Value& value;
    };

    using construction_context_param = construction_context;

    class builder_unit {};

    template <typename Product>
    class factory_unit {
    public:
        factory_unit(const builder_unit&, const factory&) noexcept {}
        factory_unit(const composite_unit<Product>&, const factory&) noexcept {}

        auto
        select_constructor(construction_context_param ctx, const factory& fac)
          -> size_t {
            size_t result = _children.size();
            size_t count = 0;
            std::tuple<int, int> best_match{0, 0};
            for(size_t i = 0; i < _children.size(); ++i) {
                const auto match = _children[i]->match(ctx, fac.constructor(i));
                if(best_match < match) {
                    best_match = match;
                    count = 1;
                    result = i;
                } else if(match == best_match) {
                    ++count;
                    result = i;
                }
            }
            return (count == 1) ? result : _children.size();
        }

    private:
        std::vector<constructor_unit<Product>*> _children;

        friend constructor_unit<Product>;
    };

    template <typename Product>
    class constructor_unit {
    public:
        constructor_unit(
          factory_unit<Product>& parent,
          const factory_constructor&) noexcept {
            parent._children.emplace_back(this);
        }

        template <typename T>
        static constexpr bool is_atomic =
          std::is_floating_point_v<T> || std::is_integral_v<T> ||
          std::is_same_v<T, std::string>;

        template <typename T>
        static auto type_match(const T*, construction_context_param) noexcept
          -> std::enable_if_t<!is_atomic<T>, std::tuple<int, int>> {
            return {true, false};
        }

        static auto
        type_match(const bool*, construction_context_param ctx) noexcept
          -> std::tuple<bool, bool> {
            return {
              ctx.value.IsBool() || ctx.value.IsString(), ctx.value.IsBool()};
        }

        template <typename T>
        static auto type_match(const T*, construction_context_param ctx) noexcept
          -> std::enable_if_t<
            std::is_integral_v<T> && std::is_signed_v<T>,
            std::tuple<bool, bool>> {
            return {
              ctx.value.IsInt64() || ctx.value.IsInt(),
              ctx.value.IsInt64() || ctx.value.IsInt()};
        }

        template <typename T>
        static auto type_match(const T*, construction_context_param ctx) noexcept
          -> std::enable_if_t<
            std::is_integral_v<T> && std::is_unsigned_v<T>,
            std::tuple<bool, bool>> {
            return {
              ctx.value.IsUint64() || ctx.value.IsUint(),
              ctx.value.IsUint64() || ctx.value.IsUint()};
        }

        template <typename T>
        static auto
        type_match(const T*, construction_context_param ctx) noexcept -> std::
          enable_if_t<std::is_floating_point_v<T>, std::tuple<bool, bool>> {
            return {
              ctx.value.IsDouble() || ctx.value.IsInt64() || ctx.value.IsInt(),
              ctx.value.IsDouble()};
        }

        static auto
        type_match(const std::string*, construction_context_param ctx) noexcept
          -> std::tuple<bool, bool> {
            return {true, ctx.value.IsString()};
        }

        auto match(
          construction_context_param ctx,
          const factory_constructor& ctr) const noexcept
          -> std::tuple<int, int> {
            if(ctr.is_move_constructor()) {
                if(ctx.value.IsString()) {
                    return {1, 1};
                }
            }
            const std::tuple<int, int> no_match{-1, 0};
            if(ctx.value.IsObject()) {
                int result = 0;
                int exact = 0;
                const size_t n = ctr.parameter_count();
                for(size_t i = 0; i < n; ++i) {
                    auto& param = ctr.parameter(i);
                    auto pos = ctx.value.FindMember(param.name().data());
                    if(pos == ctx.value.MemberEnd()) {
                        return no_match;
                    }
                    const auto [match, exact_match] =
                      type_match(static_cast<Product*>(nullptr), ctx);
                    if(!match) {
                        return no_match;
                    }
                    if(exact_match) {
                        ++exact;
                    }
                    ++result;
                }
                return {result, exact};
            }
            if(ctx.value.IsArray()) {
                const size_t n = ctr.parameter_count();
                if(n == ctx.value.Size()) {
                    if(ctr.is_copy_constructor() || ctr.is_move_constructor()) {
                        return no_match;
                    }
                    int result = 0;
                    int exact = 0;
                    for(size_t i = 0; i < n; ++i) {
                        const auto [match, exact_match] =
                          type_match(static_cast<Product*>(nullptr), ctx);
                        if(!match) {
                            return no_match;
                        }
                        if(exact_match) {
                            ++exact;
                        }
                        ++result;
                    }
                    return {result, exact};
                }
            }
            return no_match;
        }
    };

    template <typename T>
    static constexpr bool is_atomic =
      std::is_floating_point_v<T> || std::is_integral_v<T> ||
      std::is_same_v<T, std::string>;

    class constructor_info {
    public:
        constructor_info(
          const factory_constructor_parameter& param,
          const factory_constructor& ctr) noexcept
          : _name{param.name()}
          , _index{param.index()}
          , _is_default{ctr.is_default_constructor()}
          , _is_move{ctr.is_move_constructor()}
          , _is_copy{ctr.is_copy_constructor()} {}

        auto nested(construction_context_param ctx) -> construction_context {
            if(!_name.empty()) {
                if(ctx.value.IsObject()) {
                    auto pos = ctx.value.FindMember(_name.c_str());
                    if(pos != ctx.value.MemberEnd()) {
                        return {pos->value};
                    }
                }
            }
            if(ctx.value.IsArray()) {
                if(_index < ctx.value.Size()) {
                    return {ctx.value[rapidjson::SizeType(_index)]};
                }
            }
            return ctx;
        }

    private:
        std::string _name;
        size_t _index;
        bool _is_default;
        bool _is_move;
        bool _is_copy;
    };

    template <typename T>
    class atomic_unit {
    public:
        template <typename P>
        atomic_unit(
          const constructor_unit<P>&,
          const factory_constructor_parameter& parameter) noexcept
          : _info{parameter, parameter.parent_constructor()} {}

        static auto fetch(bool& dest, const rapidjson::Value& v) noexcept
          -> void {
            if(v.IsBool()) {
                dest = v.GetBool();
            } else if(v.IsString()) {
                if(v.GetString() == rapidjson::StringRef("true")) {
                    dest = true;
                } else if(v.GetString() == rapidjson::StringRef("false")) {
                    dest = false;
                }
            }
        }

        template <typename V>
        static auto fetch(V& dest, const rapidjson::Value& v) noexcept
          -> std::enable_if_t<std::is_integral_v<V> && std::is_signed_v<V>> {
            if(v.IsInt64()) {
                dest = static_cast<V>(v.GetInt64());
            } else if(v.IsInt()) {
                dest = static_cast<V>(v.GetInt());
            }
        }

        template <typename V>
        static auto fetch(V& dest, const rapidjson::Value& v) noexcept
          -> std::enable_if_t<std::is_integral_v<V> && std::is_unsigned_v<V>> {
            if(v.IsUint64()) {
                dest = static_cast<V>(v.GetUint64());
            } else if(v.IsUint()) {
                dest = static_cast<V>(v.GetUint());
            }
        }

        template <typename V>
        static auto fetch(V& dest, const rapidjson::Value& v) noexcept
          -> std::enable_if_t<std::is_floating_point_v<V>> {
            if(v.IsDouble()) {
                dest = static_cast<V>(v.GetDouble());
            } else if(v.IsInt64()) {
                dest = static_cast<V>(v.GetInt64());
            } else if(v.IsInt()) {
                dest = static_cast<V>(v.GetInt());
            }
        }

        static auto fetch(std::string& dest, const rapidjson::Value& v) noexcept
          -> void {
            if(v.IsString()) {
                dest = v.GetString();
            } else if(v.IsDouble()) {
                dest = std::to_string(v.GetDouble());
            } else if(v.IsUint64()) {
                dest = std::to_string(v.GetUint64());
            } else if(v.IsInt64()) {
                dest = std::to_string(v.GetInt64());
            } else if(v.IsUint()) {
                dest = std::to_string(v.GetUint());
            } else if(v.IsInt()) {
                dest = std::to_string(v.GetInt());
            } else if(v.IsBool()) {
                dest = v.GetBool() ? std::string("true") : std::string("false");
            } else if(v.IsNull()) {
                dest.clear();
            }
        }

        auto get(
          construction_context_param ctx,
          const factory_constructor_parameter&) noexcept -> T {
            T result{};
            fetch(result, _info.nested(ctx).value);
            return result;
        }

    private:
        constructor_info _info;
    };

    template <typename T>
    class composite_unit {
    public:
        template <typename P>
        composite_unit(
          const constructor_unit<P>&,
          const factory_constructor_parameter& parameter) noexcept
          : _info{parameter, parameter.parent_constructor()}
          , _fac{*this, parameter} {}

        auto get(
          construction_context_param ctx,
          const factory_constructor_parameter&) {
            return _fac.construct(_info.nested(ctx));
        }

    private:
        constructor_info _info;
        built_factory_type<rapidjson_factory_traits, T> _fac;
    };

    template <typename T>
    class copy_unit {
    public:
        template <typename P>
        copy_unit(
          const constructor_unit<P>&,
          const factory_constructor_parameter& parameter)
          : _info{parameter, parameter.parent_constructor()} {}

        template <typename V>
        static auto fetch(V&, const rapidjson::Value&) noexcept {}

        auto get(
          construction_context_param ctx,
          const factory_constructor_parameter&) noexcept -> T {
            T result{};
            fetch(result, _info.nested(ctx).value);
            return result;
        }

    private:
        constructor_info _info;
    };
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif
