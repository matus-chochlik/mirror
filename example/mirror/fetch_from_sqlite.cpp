/// @example mirror/fetch_from_sqlite.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/sqlite3.hpp>
#include <cstdint>
#include <filesystem>
#include <iostream>

struct person {
    std::uintmax_t person_id;
    std::string given_name;
    std::string family_name;
    std::string email_address;
};

int main(int, const char** argv) {
    mirror::sqlite3_db db{
      std::filesystem::path{argv[0]}.replace_filename("people.db").string()};

    std::vector<person> ps;

    db.ensure_table<person>();

    for(const auto& p : db.fetch("SELECT * FROM person", ps)) {
        std::cout << p.given_name << " " << p.family_name << std::endl;
    }

    return 0;
}
