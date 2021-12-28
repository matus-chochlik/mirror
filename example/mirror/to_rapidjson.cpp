/// @example mirror/to_rapidjson.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/tetrahedron.hpp"
#include "testdecl/weekday.hpp"
#include <mirror/sequence.hpp>
#include <mirror/serialize/rapidjson.hpp>
#include <iostream>

template <typename T>
void print_json(const T& value) {
    rapidjson::Document doc;
    mirror::serialize_rapidjson(value, doc);

    rapidjson::OStreamWrapper stream(std::cout);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(stream);
    doc.Accept(writer);
    std::cout << std::endl;
}

int main() {
    print_json(true);
    print_json(mirror::tribool{mirror::indeterminate});
    print_json(1234567890L);
    print_json(123.456F);
    print_json(456.789);
    print_json("mirror");
    print_json(std::string("foo"));
    print_json(std::array<int, 10>{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}});
    print_json(std::array<std::string_view, 4>{{"foo", "bar", "baz", "qux"}});
    print_json(std::vector<example::weekday>{
      example::weekday::monday,
      example::weekday::tuesday,
      example::weekday::wednesday,
      example::weekday::thursday,
      example::weekday::friday,
      example::weekday::saturday,
      example::weekday::sunday});
    print_json(example::tetrahedron{
      {{1.F, 0.F, 0.F}, {0.F, 1.F, 0.F}, {0.F, 0.F, 1.F}}, {0.F}});

    return 0;
}
