/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_REST_API_HPP
#define MIRROR_REST_API_HPP

#include "extract.hpp"
#include "from_string.hpp"
#include "make_array.hpp"
#include "make_tuple.hpp"
#include "placeholder.hpp"
#include "sequence.hpp"
#include "serialize/write_rapidjson.hpp"
#include "url.hpp"
#include <ostream>
#include <sstream>

namespace mirror {

class rest_api_response {
private:
    rapidjson::Document _result{};

public:
    template <typename T>
    void set_result(const T& result) {
        serialize::write_rapidjson(result, _result);
    }

    template <typename E>
    void set_error_code(E code) {
        rapidjson::Value code_value;
        if(!serialize::write_rapidjson(
             code, code_value, _result.GetAllocator())) {
            if(!_result.IsObject()) {
                _result.SetObject();
            }
            _result.AddMember(
              to_rapidjson("error_code"), code_value, _result.GetAllocator());
        }
    }

    template <typename... T>
    void set_error_message(std::string_view format, const T&... args) {
        rapidjson::Value message_value;
        message_value.SetObject();
        rapidjson::Value format_value;
        if(!serialize::write_rapidjson(
             format, format_value, _result.GetAllocator())) {
            message_value.AddMember(
              to_rapidjson("format"), format_value, _result.GetAllocator());
        }
        rapidjson::Value args_value;
        if(!serialize::write_rapidjson(
             std::tie(args...), args_value, _result.GetAllocator())) {
            message_value.AddMember(
              to_rapidjson("args"), args_value, _result.GetAllocator());
        }
        if(!_result.IsObject()) {
            _result.SetObject();
        }
        _result.AddMember(
          to_rapidjson("message"), message_value, _result.GetAllocator());
    }

    auto str() const -> std::string {
        std::string str;
        serialize::rapidjson_to_string(_result, str);
        return str;
    }
};

template <typename Backend>
class rest_api_adaptor {
public:
    enum class error_code {
        invalid_argument,
        missing_argument,
        invalid_path,
        missing_path,
        invalid_domain,
        missing_domain,
        invalid_scheme,
        missing_scheme,
        invalid_url
    };

private:
    std::string _scheme{"https"};
    std::string _domain{"server"};
    Backend _backend{};

    template <typename T>
    using result = typename Backend::template result<T>;

    template <typename Value>
    auto _handle_arg(
      std::string_view name,
      Value& dst,
      const url& request,
      rest_api_response& response) -> bool {
        if(const auto arg{request.argument(name)}) {
            if(const auto value{from_string<Value>(extract(arg))};
               has_value(value)) {
                dst = extract(value);
                return true;
            } else {
                response.set_error_code(error_code::invalid_argument);
                response.set_error_message(
                  "invalid value `{1}` for argument `{2}` in request",
                  extract(arg),
                  name);
                return false;
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
        response.set_error_code(error_code::missing_argument);
        response.set_error_message("missing argument `{1}` in request", name);
        return false;
    }

    template <std::size_t I, typename Names, typename Values>
    bool _handle_args(
      const Names& names,
      Values& values,
      const url& request,
      rest_api_response& response) {
        if constexpr(I < std::tuple_size_v<Values>) {
            if(_handle_arg(names[I], std::get<I>(values), request, response)) {
                return _handle_args<I + 1Z>(names, values, request, response);
            }
            return false;
        }
        return true;
    }

    template <typename Metaobject, typename R, typename E, typename Tup, size_t... I>
    auto _apply(
      Metaobject mf,
      std::type_identity<std::variant<R, E>>,
      Tup& tup,
      std::index_sequence<I...>,
      rest_api_response& response) {
        if(const auto result{(_backend.*get_pointer(mf))(std::get<I>(tup)...)};
           has_value(result)) {
            response.set_result(extract(result));
            return true;
        } else {
            response.set_error_code(get_error(result));
        }
        return false;
    }

    template <typename Metaobject, typename R, typename Tup, size_t... I>
    auto _apply(
      Metaobject mf,
      std::type_identity<R>,
      Tup& tup,
      std::index_sequence<I...>,
      rest_api_response& response) {
        response.set_result((_backend.*get_pointer(mf))(std::get<I>(tup)...));
        return true;
    }

    template <typename Metaobject, typename R, typename Tup, size_t... I>
    auto _apply(
      Metaobject mf,
      std::type_identity<void>,
      Tup& tup,
      std::index_sequence<I...>,
      rest_api_response&) {
        (_backend.*get_pointer(mf))(std::get<I>(tup)...);
        return true;
    }

    bool _handle_call(
      metaobject auto mf,
      const url& request,
      rest_api_response& response) {
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

    bool _handle_dispatch(const url& request, rest_api_response& response) {
        bool success{false};
        if(const auto opt_path{request.path()}) {
            bool found{false};
            const auto& path{extract(opt_path)};
            for_each(
              filter(get_member_functions(mirror(Backend)), is_public(_1)),
              [&](auto mf) {
                  const auto func_name{get_name(mf)};
                  if(
                    path.starts_with("/") && path.ends_with(func_name) &&
                    (path.size() == 1Z + func_name.size())) {
                      found = true;
                      success = _handle_call(mf, request, response);
                  }
              });
            if(!found) {
                response.set_error_code(error_code::invalid_path);
                response.set_error_message(
                  "invalid path `{1}` in request", path);
            }
        } else {
            response.set_error_code(error_code::missing_path);
            response.set_error_message("missing path in request");
        }
        return success;
    }

    bool _handle_domain(const url& request, rest_api_response& response) {
        if(request.has_host(_domain)) {
            return _handle_dispatch(request, response);
        } else {
            if(const auto domain{request.host()}) {
                response.set_error_code(error_code::invalid_domain);
                response.set_error_message(
                  "invalid domain `{1}` in request", *domain);
            } else {
                response.set_error_code(error_code::missing_domain);
                response.set_error_message("missing domain in request");
            }
        }
        return false;
    }

    bool _handle_scheme(const url& request, rest_api_response& response) {
        if(request.has_scheme(_scheme)) {
            return _handle_domain(request, response);
        } else {
            if(const auto scheme{request.scheme()}) {
                response.set_error_code(error_code::invalid_scheme);
                response.set_error_message(
                  "invalid scheme `{1}` in request", *scheme);
            } else {
                response.set_error_code(error_code::missing_scheme);
                response.set_error_message("missing scheme in request");
            }
        }
        return false;
    }

public:
    rest_api_adaptor() = default;
    rest_api_adaptor(
      std::string scheme,
      std::string domain,
      Backend backend) noexcept
      : _scheme{std::move(scheme)}
      , _domain{std::move(domain)}
      , _backend{std::move(backend)} {}

    auto domain() const noexcept -> std::string_view {
        return _domain;
    }

    auto handle(const url& request, rest_api_response& response) -> bool {
        if(request) {
            return _handle_scheme(request, response);
        } else {
            response.set_error_message("invalid URL `{1}`", request.str());
        }
        return false;
    }
};

} // namespace mirror

#endif
