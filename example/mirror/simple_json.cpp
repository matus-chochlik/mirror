/// @example mirror/simple_json.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/tetrahedron.hpp"
#include "testdecl/weekday.hpp"
#include <mirror/sequence.hpp>
#include <mirror/serialize/write.hpp>
#include <iomanip>
#include <iostream>

namespace mirror::serialize {
//------------------------------------------------------------------------------
struct simple_json_write_backend {
    struct context {
        std::ostream& out;
    };
    using context_param = context;

    auto enum_as_string(const context&) noexcept -> bool {
        return true;
    }

    auto begin(context_param ctx)
      -> std::variant<context, serialization_errors> {
        return {ctx};
    }

    auto write(const write_driver&, context_param ctx, bool v)
      -> serialization_errors {
        ctx.out << std::boolalpha << v;
        return {};
    }

    auto write(const write_driver&, context_param ctx, std::string_view v)
      -> serialization_errors {
        ctx.out << std::quoted(v);
        return {};
    }

    auto write(const write_driver&, context_param ctx, const std::string& v)
      -> serialization_errors {
        ctx.out << std::quoted(v);
        return {};
    }

    template <typename T>
    auto write(const write_driver&, context_param ctx, const T& v)
      -> serialization_errors {
        ctx.out << v;
        return {};
    }

    auto begin_list(context_param ctx, size_t)
      -> std::variant<context, serialization_errors> {
        ctx.out << '[';
        return {ctx};
    }

    auto begin_element(context_param ctx, size_t)
      -> std::variant<context, serialization_errors> {
        return {ctx};
    }

    auto separate_element(context_param ctx) -> serialization_errors {
        ctx.out << ',';
        return {};
    }

    auto finish_element(context_param, size_t) -> serialization_errors {
        return {};
    }

    auto finish_list(context_param ctx) -> serialization_errors {
        ctx.out << ']';
        return {};
    }

    auto begin_record(context_param ctx, size_t)
      -> std::variant<context, serialization_errors> {
        ctx.out << '{';
        return {ctx};
    }

    auto begin_attribute(context_param ctx, std::string_view name)
      -> std::variant<context, serialization_errors> {
        ctx.out << std::quoted(name) << ':';
        return {ctx};
    }

    auto separate_attribute(context_param ctx) -> serialization_errors {
        ctx.out << ',';
        return {};
    }

    auto finish_attribute(context_param, std::string_view)
      -> serialization_errors {
        return {};
    }

    auto finish_record(context_param ctx) -> serialization_errors {
        ctx.out << '}';
        return {};
    }

    auto finish(context_param) -> serialization_errors {
        return {};
    }
};
//------------------------------------------------------------------------------
} // namespace mirror::serialize

template <typename T>
auto print_simple_json(std::ostream& out, const T& value) -> std::ostream& {
    mirror::serialize::simple_json_write_backend be;
    mirror::serialize::write(value, be, {out});
    return out << std::endl;
}

int main() {
    using example::weekday;
    print_simple_json(
      std::cout, std::array<int, 10>{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}});
    print_simple_json(
      std::cout, std::array<std::string_view, 4>{{"foo", "bar", "baz", "qux"}});
    print_simple_json(
      std::cout,
      std::vector<weekday>{
        weekday::monday,
        weekday::tuesday,
        weekday::wednesday,
        weekday::thursday,
        weekday::friday,
        weekday::saturday,
        weekday::sunday});
    print_simple_json(
      std::cout,
      example::tetrahedron{
        {{1.F, 0.F, 0.F}, {0.F, 1.F, 0.F}, {0.F, 0.F, 1.F}}, {0.F}});

    return 0;
}
