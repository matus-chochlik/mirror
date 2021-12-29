/// @example mirror/repeat_message_json.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/sequence.hpp>
#include <mirror/serialize/read_rapidjson.hpp>
#include <chrono>
#include <iostream>
#include <ranges>
#include <sstream>
#include <thread>

struct options {
    std::string message{"Hello world!"};
    std::optional<std::chrono::milliseconds> interval{500};
    int count{3};
};

static auto parse(options& opts, std::istream& cfg_in) -> bool {
    const auto errors = mirror::serialize::read_rapidjson_stream(opts, cfg_in);
    return !errors;
}

static std::string fake_config_file() {
    return {R"({
		"message": "Hello reflection!",
		"interval": [],
		"count": 4
	})"};
}

int main() {
    options opts;
    std::stringstream cfg_in{fake_config_file()};
    if(parse(opts, cfg_in)) {
        for(int i : std::ranges::views::iota(1, opts.count + 1)) {
            std::cout << i << ": " << opts.message << std::endl;
            if(opts.interval) {
                std::this_thread::sleep_for(*opts.interval);
            }
        }
        return 0;
    } else {
        return 1;
    }
}
