/// @example mirror/interface_revision.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/hash.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iomanip>
#include <iostream>

template <typename Intf>
struct versioned_interface {
public:
    constexpr versioned_interface(const versioned_interface&) = delete;
    auto operator=(versioned_interface&&) = delete;
    auto operator=(const versioned_interface&) = delete;

    static auto revision_id() noexcept -> mirror::hash_t {
        using mirror::_1;
        return fold(
          filter(get_member_functions(mirror(Intf)), is_virtual(_1)),
          get_hash(_1) ^ get_hash(get_type(_1)),
          [](auto... h) { return (... ^ h); });
    }

protected:
    constexpr versioned_interface() noexcept = default;

    constexpr versioned_interface(versioned_interface&&) noexcept = default;
    virtual ~versioned_interface() noexcept = default;
};

#define EXAMPLE_REVISION 2

namespace example {
#if EXAMPLE_REVISION == 1
inline
#endif
  namespace v1 {

struct operations : versioned_interface<operations> {
    virtual void foo() = 0;
    virtual void bar(int) = 0;
    virtual auto baz(bool, bool) -> bool = 0;
};

} // namespace v1

#if EXAMPLE_REVISION == 2
inline
#endif
  namespace v2 {

struct operations : versioned_interface<operations> {
    virtual void foo() = 0;
    virtual void bar(long) = 0;
    virtual auto baz(bool, bool) -> int = 0;
};

} // namespace v2
} // namespace example

int main() {
    std::cout << "version 1: " << std::hex
              << example::v1::operations::revision_id() << std::endl;
    std::cout << "version 2: " << std::hex
              << example::v2::operations::revision_id() << std::endl;
    std::cout << "current:   " << std::hex << example::operations::revision_id()
              << std::endl;

    return 0;
}
