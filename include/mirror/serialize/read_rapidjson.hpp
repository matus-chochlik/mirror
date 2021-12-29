/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_READ_RAPIDJSON_HPP
#define MIRROR_SERIALIZE_READ_RAPIDJSON_HPP

#include "../diagnostic.hpp"
#include "../tribool.hpp"
#include "../utils/rapidjson.hpp"
#include "read.hpp"

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(zero-as-null-pointer-constant)
#endif

#include <rapidjson/error/en.h>
#include <rapidjson/rapidjson.h>

#if defined(__clang__)
MIRROR_DIAG_POP()
#endif

namespace mirror::serialize {
//------------------------------------------------------------------------------
template <typename Encoding, typename Allocator>
struct basic_rapidjson_read_backend {
    using node_type = rapidjson::GenericValue<Encoding, Allocator>;

    struct context {
        const node_type& parent;
        const node_type& node;

        context(
          const rapidjson::GenericDocument<Encoding, Allocator>& d) noexcept
          : parent{d}
          , node{d} {}

        context(const context& c, const node_type& n) noexcept
          : parent{c.node}
          , node{n} {}
    };
    using context_param = const context&;

    auto enum_as_string(context_param) noexcept -> bool {
        return true;
    }

    auto begin(context_param ctx) -> std::variant<context, read_errors> {
        return {ctx};
    }

    template <typename T>
    auto read(const read_driver& drv, context_param ctx, T& value)
      -> read_errors {
        read_errors errors{};
        if constexpr(std::is_same_v<T, bool>) {
            if(ctx.node.IsBool()) {
                value = ctx.node.GetBool();
            } else {
                errors |= read_error_code::invalid_format;
            }
        } else if constexpr(std::is_same_v<T, tribool>) {
            if(ctx.node.IsBool()) {
                value = ctx.node.GetBool();
            } else if(ctx.node.IsNull()) {
                value = indeterminate;
            } else {
                errors |= read_error_code::invalid_format;
            }
        } else if constexpr(std::is_integral_v<T>) {
            if constexpr(std::is_signed_v<T>) {
                if(sizeof(T) > 4Z) {
                    if(ctx.node.IsInt64()) {
                        value = T(ctx.node.GetInt64());
                    } else if(ctx.node.IsInt()) {
                        value = T(ctx.node.GetInt());
                    } else {
                        errors |= read_error_code::invalid_format;
                    }
                } else {
                    if(ctx.node.IsInt()) {
                        value = T(ctx.node.GetInt());
                    } else {
                        errors |= read_error_code::invalid_format;
                    }
                }
            } else {
                if(sizeof(T) > 4Z) {
                    if(ctx.node.IsUInt64()) {
                        value = T(ctx.node.GetUInt64());
                    } else if(ctx.node.IsUInt()) {
                        value = T(ctx.node.GetUInt());
                    } else {
                        errors |= read_error_code::invalid_format;
                    }
                } else {
                    if(ctx.node.IsUInt()) {
                        value = T(ctx.node.GetUInt());
                    } else {
                        errors |= read_error_code::invalid_format;
                    }
                }
            }
        } else if constexpr(std::is_floating_point_v<T>) {
            if constexpr(std::is_same_v<T, float>) {
                if(ctx.node.IsFloat()) {
                    value = T(ctx.node.GetFloat());
                }
            } else {
                if(ctx.node.IsDouble()) {
                    value = ctx.node.GetDouble();
                } else if(ctx.node.IsFloat()) {
                    value = T(ctx.node.GetFloat());
                } else {
                    errors |= read_error_code::invalid_format;
                }
            }
        } else if constexpr(std::is_same_v<T, std::string>) {
            if(ctx.node.IsString()) {
                value = ctx.node.GetString();
            } else {
                errors |= read_error_code::invalid_format;
            }
        } else {
            return drv.read(*this, ctx, value);
        }
        return errors;
    }

    auto begin_list(context_param ctx, size_t& count)
      -> std::variant<context, read_errors> {
        if(ctx.node.IsArray()) {
            count = ctx.node.Size();
            return {ctx};
        }
        return read_errors{read_error_code::invalid_format};
    }

    auto begin_element(context_param ctx, size_t idx)
      -> std::variant<context, read_errors> {
        return {context{ctx, ctx.node[rapidjson::SizeType(idx)]}};
    }

    auto separate_element(context_param) -> read_errors {
        return {};
    }

    auto finish_element(context_param, size_t) -> read_errors {
        return {};
    }

    auto finish_list(context_param) -> read_errors {
        return {};
    }

    auto begin_record(context_param ctx, size_t&)
      -> std::variant<context, read_errors> {
        if(ctx.node.IsObject()) {
            return {ctx};
        }
        return read_errors{read_error_code::invalid_format};
    }

    auto begin_attribute(context_param ctx, std::string_view name)
      -> std::variant<context, read_errors> {
        const auto pos = ctx.node.FindMember(to_rapidjson(name));
        if(pos != ctx.node.MemberEnd()) {
            return {context{ctx, pos->value}};
        }
        return read_errors{read_error_code::missing_member};
    }

    auto separate_attribute(context_param) -> read_errors {
        return {};
    }

    auto finish_attribute(context_param, std::string_view) -> read_errors {
        return {};
    }

    auto finish_record(context_param) -> read_errors {
        return {};
    }

    auto finish(context_param) -> read_errors {
        return {};
    }
};
//------------------------------------------------------------------------------
template <typename T, typename E, typename A>
auto read_rapidjson(
  T& value,
  const rapidjson::GenericDocument<E, A>& node) noexcept -> read_errors {
    basic_rapidjson_read_backend<E, A> backend;
    typename basic_rapidjson_read_backend<E, A>::context ctx{node};
    return read(value, backend, ctx);
}
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif

