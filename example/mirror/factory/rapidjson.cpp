/// @example mirror/factory/rapidjson.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include "../testdecl/tetrahedron.hpp"
#include <iostream>
#include <mirror/factory/builder.hpp>
#include <mirror/factory/rapidjson.hpp>

static void print_info(const example::tetrahedron& teh) {
    std::cout << "volume of the tetrahedron is: " << teh.volume() << std::endl;
    std::cout << "area of its base is: " << teh.base().area() << std::endl;
    std::cout << "distance of its apex from origin is: "
              << teh.apex().direction().length() << std::endl;
}

template <typename T, size_t N>
static void construct_from(
  mirror::factory_builder<mirror::rapidjson_factory_traits>& builder,
  const char (&json_str)[N]) {

    rapidjson::Document json_doc;
    const rapidjson::ParseResult parse_result{json_doc.Parse(json_str)};
    if(parse_result) {
        using namespace mirror;

        auto fac = builder.build<T>();
        print_info(fac.construct({json_doc}));

    } else {
        std::cerr << rapidjson::GetParseError_En(parse_result.Code())
                  << std::endl;
    }
}

int main() {
    using namespace mirror;
    factory_builder<rapidjson_factory_traits> builder("rjf");

    construct_from<example::tetrahedron>(builder, R"({
		"base": {
			"a": {
				"x": 1.0,
				"y": 0.0,
				"z": 0.0
			},
			"b": {
				"x": 0.0,
				"y": 1.0,
				"z": 0.0
			},
			"c": {
				"x": 0.0,
				"y": 0.0,
				"z": 1.0
			}
		},
		"apex": {
			"v": 1.0
		}
	})");

    return 0;
}
