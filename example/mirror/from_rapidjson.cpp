/// @example mirror/from_rapidjson.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/month.hpp"
#include "testdecl/tetrahedron.hpp"
#include <mirror/serialize/read_rapidjson.hpp>
#include <iostream>

template <typename T>
void from_json(std::string_view json_str) {
    rapidjson::Document json_doc;
    const rapidjson::ParseResult parse_result{
      json_doc.Parse(mirror::to_rapidjson(json_str))};
    if(parse_result) {
        T value;
        const auto errors = mirror::serialize::read_rapidjson(value, json_doc);
        if(!errors) {
            std::cout << "OK: '" << json_str << "'" << std::endl;
        } else {
            std::cerr << "failed to deserialize from '" << json_str << "'!"
                      << std::endl;
        }
    } else {
        std::cerr << rapidjson::GetParseError_En(parse_result.Code())
                  << std::endl;
    }
}

int main() {
    from_json<bool>("true");
    from_json<mirror::tribool>("null");
    from_json<int>("1");
    from_json<float>("2");
    from_json<double>("3.4");
    from_json<std::array<mirror::tribool, 3>>("[true, false, null]");
    from_json<std::vector<example::month>>(
      R"(["february", "june", "july", "august", "december"])");
    from_json<example::tetrahedron>(
      R"({"_base":{
	       "_a":{"_x":1.0,"_y":0.0,"_z":0.0},
		   "_b":{"_x":0.0,"_y":1.0,"_z":0.0},
		   "_c":{"_x":0.0,"_y":0.0,"_z":1.0}
		 },"_apex":{"_x":0.0,"_y":0.0,"_z":0.0}})");

    return 0;
}
