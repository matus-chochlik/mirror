/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_WRITE_RAPIDJSON_HPP
#define MIRROR_SERIALIZE_WRITE_RAPIDJSON_HPP

#include "../diagnostic.hpp"
#include "../sequence.hpp"
#include "../tribool.hpp"
#include "write.hpp"

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(zero-as-null-pointer-constant)
#endif

#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#if defined(__clang__)
MIRROR_DIAG_POP()
#endif

namespace mirror::serialize {
//------------------------------------------------------------------------------
template <typename Encoding, typename Allocator>
struct basic_rapidjson_write_backend {
    using node_type = rapidjson::GenericValue<Encoding, Allocator>;

    struct context {
        Allocator& allocator;
        node_type& parent;
        node_type& node;
        node_type temp;

        context(rapidjson::GenericDocument<Encoding, Allocator>& d) noexcept
          : allocator{d.GetAllocator()}
          , parent{d}
          , node{d} {}

        context(context& c, node_type& n) noexcept
          : allocator{c.allocator}
          , parent{c.node}
          , node{n} {}

        context(context&& c) noexcept
          : allocator{c.allocator}
          , parent{c.parent}
          , node{c.node}
          , temp{std::move(c.temp)} {}

        context(context& c) noexcept
          : allocator{c.allocator}
          , parent{c.parent}
          , node{c.node}
          , temp{std::move(c.temp)} {}
    };
    using context_param = context&;

    static auto to_rapidjson(std::string_view v) noexcept {
        return rapidjson::GenericStringRef<char>(
          v.data(), rapidjson::SizeType(v.size()));
    }

    auto enum_as_string(context_param) noexcept -> bool {
        return true;
    }

    auto begin(context_param ctx) -> std::variant<context, write_errors> {
        return {ctx};
    }

    template <typename T>
    auto write(const write_driver& drv, context_param ctx, const T& value)
      -> write_errors {
        if constexpr(std::is_same_v<T, bool>) {
            ctx.node.SetBool(value);
        } else if constexpr(std::is_same_v<T, tribool>) {
            if(value) {
                ctx.node.SetBool(true);
            } else if(!value) {
                ctx.node.SetBool(false);
            } else {
                ctx.node.SetNull();
            }
        } else if constexpr(std::is_integral_v<T>) {
            if constexpr(std::is_signed_v<T>) {
                if constexpr(sizeof(T) > 4Z) {
                    ctx.node.SetInt64(value);
                } else {
                    ctx.node.SetInt(value);
                }
            } else {
                if constexpr(sizeof(T) > 4Z) {
                    ctx.node.SetUInt64(value);
                } else {
                    ctx.node.SetUInt(value);
                }
            }
        } else if constexpr(std::is_floating_point_v<T>) {
            if constexpr(std::is_same_v<T, float>) {
                ctx.node.SetFloat(value);
            } else {
                ctx.node.SetDouble(value);
            }
        } else if constexpr(std::is_convertible_v<T, std::string_view>) {
            const std::string_view view{value};
            ctx.node.SetString(to_rapidjson(view));
        } else {
            return drv.write(*this, ctx, value);
        }
        return {};
    }

    auto begin_list(context_param ctx, size_t count)
      -> std::variant<context, write_errors> {
        ctx.node.SetArray();
        ctx.node.Reserve(rapidjson::SizeType(count), ctx.allocator);
        return {ctx};
    }

    auto begin_element(context_param ctx, size_t)
      -> std::variant<context, write_errors> {
        return {context{ctx, ctx.temp}};
    }

    auto separate_element(context_param) -> write_errors {
        return {};
    }

    auto finish_element(context_param ctx, size_t) -> write_errors {
        ctx.parent.PushBack(ctx.node, ctx.allocator);
        return {};
    }

    auto finish_list(context_param) -> write_errors {
        return {};
    }

    auto begin_record(context_param ctx, size_t)
      -> std::variant<context, write_errors> {
        ctx.node.SetObject();
        return {ctx};
    }

    auto begin_attribute(context_param ctx, std::string_view)
      -> std::variant<context, write_errors> {
        return {context{ctx, ctx.temp}};
    }

    auto separate_attribute(context_param) -> write_errors {
        return {};
    }

    auto finish_attribute(context_param ctx, std::string_view name)
      -> write_errors {
        ctx.parent.AddMember(to_rapidjson(name), ctx.node, ctx.allocator);
        return {};
    }

    auto finish_record(context_param) -> write_errors {
        return {};
    }

    auto finish(context_param) -> write_errors {
        return {};
    }
};
//------------------------------------------------------------------------------
template <typename T, typename E, typename A>
auto write_rapidjson(
  const T& value,
  rapidjson::GenericDocument<E, A>& node) noexcept -> write_errors {
    basic_rapidjson_write_backend<E, A> backend;
    typename basic_rapidjson_write_backend<E, A>::context ctx{node};
    return write(value, backend, ctx);
}
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif

