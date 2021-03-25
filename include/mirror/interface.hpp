/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_INTERFACE_HPP
#define MIRROR_INTERFACE_HPP

namespace mirror {
//------------------------------------------------------------------------------
/// @brief Base template for abstract interfaces, implements common functionality.
/// @see copyable_interface
template <typename Derived>
class interface {
public:
    /// @brief Not copyable.
    constexpr interface(const interface&) = delete;

    /// @brief Not move assignable.
    auto operator=(interface&&) = delete;

    /// @brief Not copy assignable.
    auto operator=(const interface&) = delete;

protected:
    /// @brief Default constructible by derived.
    constexpr interface() noexcept = default;

    /// @brief Move constructible by derived.
    constexpr interface(interface&&) noexcept = default;
    virtual ~interface() noexcept = default;
};
//------------------------------------------------------------------------------
/// @brief Base template for polymorphic classes, implements common functionality.
/// @see interface
template <typename Derived>
class abstract {
protected:
    /// @brief Default constructible by derived.
    constexpr abstract() noexcept = default;

    /// @brief Move constructible by derived.
    constexpr abstract(abstract&&) noexcept = default;

    /// @brief Copy constructible by derived.
    constexpr abstract(const abstract&) noexcept = default;

    /// @brief Move assignable by derived.
    auto operator=(abstract&&) noexcept -> abstract& = default;

    /// @brief Copy assignable by derived.
    auto operator=(const abstract&) noexcept -> abstract& = default;
    virtual ~abstract() noexcept = default;
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_INTERFACE_HPP
