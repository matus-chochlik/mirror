/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_BITFIELD_HPP
#define MIRROR_BITFIELD_HPP

#include <type_traits>

namespace mirror {

/// @brief Class for manipulating and testing a group of enumeration-based bits.
/// @ingroup utilities
template <typename Bit>
class bitfield {
public:
    /// @brief The enumeration type specifying individual bit values.
    using bit_type = Bit;

    /// @brief The Integral type used to store the bits.
    using value_type = std::make_unsigned_t<std::underlying_type_t<bit_type>>;

    /// @brief Default constructor.
    constexpr bitfield() noexcept = default;

    /// @brief Explicit construction from the underlying interger type value.
    constexpr explicit bitfield(const value_type bits) noexcept
      : _bits{bits} {}

    /// @brief Construction from the bit enumeration type value.
    constexpr bitfield(const bit_type _bit) noexcept
      : _bits{value_type(_bit)} {}

    constexpr bitfield(const bit_type _bit_a, const bit_type _bit_b) noexcept
      : _bits(value_type(_bit_a) | value_type(_bit_b)) {}

    /// @brief Indicates that none of the bits are set.
    constexpr auto is_empty() const noexcept {
        return _bits == value_type(0);
    }

    /// @brief Indicates that some of the bits are set.
    /// @see is_empty
    explicit constexpr operator bool() const noexcept {
        return _bits != value_type(0);
    }

    /// @brief Explicit conversion to the underlying integer value type.
    /// @see bits
    explicit constexpr operator value_type() const noexcept {
        return _bits;
    }

    /// @brief Returns the bits in the underlying integer value type.
    constexpr auto bits() const noexcept -> value_type {
        return _bits;
    }

    /// @brief Tests if the specified bit is set.
    /// @see has_not
    /// @see has_only
    /// @see has_all
    /// @see has_any
    /// @see has_none
    /// @see has_at_most
    constexpr auto has(const bit_type bit) const noexcept {
        return (_bits & value_type(bit)) == value_type(bit);
    }

    /// @brief Tests if the specified bit is not set.
    /// @see has
    /// @see has_all
    /// @see has_any
    /// @see has_only
    /// @see has_none
    /// @see has_at_most
    constexpr auto has_not(const bit_type bit) const noexcept {
        return (_bits & value_type(bit)) != value_type(bit);
    }

    /// @brief Tests if all of the specified bits are set.
    /// @see has
    /// @see has_not
    /// @see has_only
    /// @see has_any
    /// @see has_none
    /// @see has_at_most
    template <typename... B>
    constexpr auto has_all(const bit_type bit, B... bits) const noexcept
      -> bool {
        return (has(bit) && ... && has(bits));
    }

    /// @brief Tests if any of the specified bits are set.
    /// @see has
    /// @see has_not
    /// @see has_only
    /// @see has_all
    /// @see has_none
    /// @see has_at_most
    template <typename... B>
    constexpr auto has_any(const bit_type bit, B... bits) const noexcept
      -> bool {
        return (has(bit) || ... || has(bits));
    }

    /// @brief Tests if none of the specified bits are set.
    /// @see has
    /// @see has_not
    /// @see has_only
    /// @see has_all
    /// @see has_any
    /// @see has_at_most
    template <typename... B>
    constexpr auto has_none(const bit_type bit, B... bits) const noexcept
      -> bool {
        return (has_not(bit) && ... && has_not(bits));
    }

    /// @brief Tests if only the specified bit is set.
    /// @see has
    /// @see has_not
    /// @see has_all
    /// @see has_any
    /// @see has_none
    /// @see has_at_most
    constexpr auto has_only(const bit_type bit) const noexcept {
        return _bits == value_type(bit);
    }

    /// @brief Tests if at most the specified bit is set (or is empty).
    /// @see has
    /// @see has_not
    /// @see has_only
    /// @see has_all
    /// @see has_any
    /// @see has_none
    constexpr auto has_at_most(const bit_type bit) const noexcept {
        return is_empty() || has_only(bit);
    }

    /// @brief Equality comparison.
    friend constexpr auto
    operator==(const bitfield a, const bitfield b) noexcept {
        return a._bits == b._bits;
    }

    /// @brief Nonequality comparison.
    friend constexpr auto
    operator!=(const bitfield a, const bitfield b) noexcept {
        return a._bits != b._bits;
    }

    /// @brief Bitwise-or operator.
    friend constexpr auto operator|(const bitfield a, const bitfield b) noexcept
      -> bitfield {
        return bitfield(a._bits | b._bits);
    }

    /// @brief Bitwise-or operator.
    auto operator|=(const bitfield b) noexcept -> bitfield& {
        _bits |= b._bits;
        return *this;
    }

    /// @brief Bitwise-and operator.
    friend constexpr auto operator&(const bitfield a, const bitfield b) noexcept
      -> bitfield {
        return bitfield(a._bits & b._bits);
    }

    /// @brief Bitwise-and operator.
    auto operator&=(const bitfield b) noexcept -> bitfield& {
        _bits &= b._bits;
        return *this;
    }

    /// @brief Bit inversion operator
    friend constexpr auto operator~(const bitfield b) noexcept -> bitfield {
        return bitfield{value_type(~b._bits)};
    }

    /// @brief Clears the specified bit.
    auto clear(const bit_type b) noexcept -> bitfield& {
        _bits &= ~value_type(b); // NOLINT(hicpp-signed-bitwise)
        return *this;
    }

    /// @brief Clears all bits.
    /// @post is_empty()
    auto clear() noexcept -> bitfield& {
        _bits = value_type(0);
        return *this;
    }

private:
    value_type _bits{0U};
};

} // namespace mirror

#endif // MIRROR_BITFIELD_HPP
