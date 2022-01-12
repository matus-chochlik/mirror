/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_WRITE_JSON_HPP
#define MIRROR_SERIALIZE_WRITE_JSON_HPP

#include "write_rapidjson.hpp"

namespace mirror::serialize {
//------------------------------------------------------------------------------
template <typename T>
auto write_json_stream(const T& value, std::ostream& out) -> write_errors {
    return write_rapidjson_stream(value, out);
}
//------------------------------------------------------------------------------
template <typename T>
auto write_json_string(const T& value, std::string& str) -> write_errors {
    return write_rapidjson_string(value, str);
}
//------------------------------------------------------------------------------
template <typename T>
auto to_json_string(const T& value) -> std::variant<std::string, write_errors> {
    std::string str;
    if(const auto errors{write_json_string(value, str)}) {
        return {errors};
    }
    return {str};
}
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif

