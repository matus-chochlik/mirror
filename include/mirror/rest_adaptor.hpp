/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_REST_ADAPTOR_HPP
#define MIRROR_REST_ADAPTOR_HPP

#include <mirror/extract.hpp>
#include <mirror/from_string.hpp>
#include <mirror/make_array.hpp>
#include <mirror/make_tuple.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <mirror/url.hpp>
#include <ostream>

namespace mirror {

template <typename Backend>
class rest_adaptor {
private:
    std::string _scheme{"https"};
    std::string _domain{"server"};
    Backend _backend{};

    template <typename Value>
    auto _handle_arg(
      std::string_view name,
      Value& dst,
      const url& request,
      std::ostream& response) -> bool {
        if(const auto arg{request.argument(name)}) {
            if(const auto value{from_string<Value>(extract(arg))};
               has_value(value)) {
                dst = extract(value);
                return true;
            } else {
                response << "invalid value `" << extract(arg)
                         << "` for argument `" << name << "` in request";
            }
        } else if(name == "username") {
            if(const auto username{request.login()}) {
                if(const auto value{from_string<Value>(extract(username))};
                   has_value(value)) {
                    dst = extract(value);
                }
                return true;
            }
        } else if(name == "password") {
            if(const auto password{request.password()}) {
                if(const auto value{from_string<Value>(extract(password))};
                   has_value(value)) {
                    dst = extract(value);
                }
                return true;
            }
        }
        response << "missing argument `" << name << "` in request";
        return false;
    }

    template <std::size_t I, typename Names, typename Values>
    bool _handle_args(
      const Names& names,
      Values& values,
      const url& request,
      std::ostream& response) {
        if constexpr(I < std::tuple_size_v<Values>) {
            if(_handle_arg(names[I], std::get<I>(values), request, response)) {
                return _handle_args<I + 1Z>(names, values, request, response);
            }
            return false;
        }
        return true;
    }

    template <typename Metaobject, typename R, typename Tup, size_t... I>
    auto _apply(
      Metaobject mf,
      std::type_identity<R>,
      Tup& tup,
      std::index_sequence<I...>,
      std::ostream& response) {
        response << (_backend.*get_pointer(mf))(std::get<I>(tup)...);
        return response.good();
    }

    template <typename Metaobject, typename R, typename Tup, size_t... I>
    auto _apply(
      Metaobject mf,
      std::type_identity<void>,
      Tup& tup,
      std::index_sequence<I...>,
      std::ostream&) {
        (_backend.*get_pointer(mf))(std::get<I>(tup)...);
        return true;
    }

    bool _handle_call(
      metaobject auto mf,
      const url& request,
      std::ostream& response) {
        const auto mp{get_parameters(mf)};
        const auto arg_names{make_array_of<std::string_view>(mp, get_name(_1))};
        auto arg_values{make_value_tuple(transform(mp, get_type(_1)))};
        if(_handle_args<0Z>(arg_names, arg_values, request, response)) {
            return _apply(
              mf,
              get_reflected_type(get_type(mf)),
              arg_values,
              std::make_index_sequence<std::tuple_size_v<decltype(arg_values)>>{},
              response);
        }
        return false;
    }

    bool _handle_dispatch(const url& request, std::ostream& response) {
        bool success{false};
        if(const auto opt_path{request.path()}) {
            const auto& path{extract(opt_path)};
            for_each(get_member_functions(mirror(Backend)), [&](auto mf) {
                const auto func_name{get_name(mf)};
                if(
                  path.starts_with("/") && path.ends_with(func_name) &&
                  (path.size() == 1Z + func_name.size())) {
                    success = _handle_call(mf, request, response);
                }
            });
        } else {
            response << "missing path in request";
        }
        return success;
    }

    bool _handle_domain(const url& request, std::ostream& response) {
        if(request.has_host(_domain)) {
            return _handle_dispatch(request, response);
        } else {
            if(const auto domain{request.host()}) {
                response << "invalid domain `" << *domain << "` in request";
            } else {
                response << "missing domain in request";
            }
        }
        return false;
    }

    bool _handle_scheme(const url& request, std::ostream& response) {
        if(request.has_scheme(_scheme)) {
            return _handle_domain(request, response);
        } else {
            if(const auto scheme{request.scheme()}) {
                response << "invalid scheme `" << *scheme << "` in request";
            } else {
                response << "missing scheme in request";
            }
        }
        return false;
    }

public:
    rest_adaptor() = default;
    rest_adaptor(std::string scheme, std::string domain, Backend backend) noexcept
      : _scheme{std::move(scheme)}
      , _domain{std::move(domain)}
      , _backend{std::move(backend)} {}

    auto domain() const noexcept -> std::string_view {
        return _domain;
    }

    auto handle(const url& request, std::ostream& response) -> bool {
        if(request) {
            return _handle_scheme(request, response);
        } else {
            response << "invalid URL: `" << request.str() << "`";
        }
        return false;
    }
};

} // namespace mirror

#endif
