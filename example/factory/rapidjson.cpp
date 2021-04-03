/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <iostream>
#include <mirror/factory/builder.hpp>
#include <mirror/factory/rapidjson.hpp>
#include <mirror/testdecl.hpp>

int main() {
    auto json_str = R"({
		"base": {
			"a": {
				"x": 2.0,
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
			"v": 0.0
		}
	})";

    rapidjson::Document json_doc;
    const rapidjson::ParseResult parse_result{json_doc.Parse(json_str)};
    if(parse_result) {
        using namespace mirror;
        using rapidjson_factory_builder =
          factory_builder<rapidjson_factory_traits>;

        auto fac = rapidjson_factory_builder("rjf").build<test::tetrahedron>();
        auto teh = fac.construct({json_doc});

        std::cout << "volume of the tetrahedron is: " << teh.volume()
                  << std::endl;
        std::cout << "area of its base is: " << teh.base().area() << std::endl;
        std::cout << "distance of its apex from origin is: "
                  << teh.apex().direction().length() << std::endl;
    } else {
        std::cerr << rapidjson::GetParseError_En(parse_result.Code())
                  << std::endl;
    }

    return 0;
}
