/// @example mirror/repeat_message.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/program_args.hpp>
#include <mirror/sequence.hpp>
#include <chrono>
#include <iostream>
#include <ranges>
#include <thread>

struct options {
    std::string message{"Hello world!"};
    std::chrono::milliseconds interval{500};
    int count{3};
};

static auto parse(options& opts, const mirror::program_args& args) -> bool {
    bool parsed = true;
    const auto mo = mirror(options);
    for(const auto& arg : args) {
        for_each(get_data_members(mo), [&](auto mdm) {
            if(arg.is_long_tag(get_name(mdm))) {
                if(const auto opt{mirror::from_string(
                     arg.next(), get_reflected_type(get_type(mdm)))};
                   mirror::has_value(opt)) {
                    get_reference(mdm, opts) = mirror::extract(opt);
                } else {
                    std::cerr << "invalid value '" << arg.next()
                              << "' for option " << arg << "!" << std::endl;
                    parsed = false;
                }
            }
        });
    }
    return parsed;
}

int main(int argc, const char** argv) {
    const mirror::program_args args{argc, argv};
    options opts;
    if(parse(opts, args)) {
        for(int i : std::ranges::views::iota(1, opts.count + 1)) {
            std::cout << i << ": " << opts.message << std::endl;
            std::this_thread::sleep_for(opts.interval);
        }
        return 0;
    } else {
        return 1;
    }
}
