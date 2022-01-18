/// @example mirror/test.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/placeholder.hpp>
#include <mirror/primitives.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

class query_generator_impl {
public:
    template <typename T>
    struct dataset : std::string {
        dataset(std::string s) noexcept
          : std::string{std::move(s)} {}
    };

private:
    template <typename T>
    static auto _table_name(std::type_identity<T>) {
        return std::string(get_name(remove_all_aliases(mirror(T))));
    }

    template <typename T>
    static auto _table_name(std::type_identity<dataset<T>>) {
        return _table_name(std::type_identity<T>{});
    }

public:
    auto operator()(mirror::metaobject auto me, const auto& arg)
      -> std::string {
        const auto mf = get_callable(get_subexpression(me));

        std::stringstream query;
        query << "SELECT * FROM ";
        query << _table_name(get_reflected_type(get_type(mf)));
        query << " WHERE ";
        query << get_name(mf).substr(std::string_view{"get_by_"}.size());
        query << " = " << std::quoted(arg);
        query << ";";
        return query.str();
    }
};

namespace schema {

struct person {
    std::string first_name;
    std::string family_name;
    std::string email;
};

} // namespace schema

template <typename Impl>
struct operations {
private:
    Impl _impl;

public:
    template <typename T>
    using dataset = typename Impl::template dataset<T>;

    auto get_by_first_name(std::string_view name) -> dataset<schema::person> {
        return _impl(mirror((get_by_first_name(name))), name);
    }

    auto get_by_email(std::string_view email) -> dataset<schema::person> {
        return _impl(mirror((get_by_email(email))), email);
    }
};

using query_generator = operations<query_generator_impl>;

int main() {
    query_generator gen;

    // SELECT * FROM person WHERE first_name = "Joe";
    std::cout << gen.get_by_first_name("Joe") << std::endl;

    // SELECT * FROM person WHERE email = "joe@example.com";
    std::cout << gen.get_by_email("joe@example.com") << std::endl;

    return 0;
}
