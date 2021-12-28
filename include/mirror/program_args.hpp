/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef MIRROR_PROGRAM_ARGS_HPP
#define MIRROR_PROGRAM_ARGS_HPP

#include "from_string.hpp"
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace mirror {
//------------------------------------------------------------------------------
class program_args;
//------------------------------------------------------------------------------
class program_arg_iterator;

/// @brief Class representing a single main function (command-line) argument.
/// @ingroup utilities
/// @see program_args
/// @note Do not construct directly. Use program_arguments.
class program_arg {
public:
    /// @brief Default constructor.
    constexpr program_arg() noexcept = default;

    program_arg(const int argi, const int argc, const char** argv) noexcept
      : _argi{argi}
      , _argc{argc}
      , _argv{argv} {}

    /// @brief Alias for the argument value type.
    using value_type = std::string_view;

    /// @brief Indicates if the arguments has_value.
    auto has_value() const noexcept -> bool {
        return (0 < _argi) && (_argi < _argc) && (_argv != nullptr) &&
               (_argv[_argi] != nullptr);
    }

    /// @brief Indicates if the arguments has value.
    /// @see is_valid
    operator bool() const noexcept {
        return has_value();
    }

    /// @brief Returns the index of this argument.
    auto position() const noexcept {
        return _argi;
    }

    /// @brief Indicates if this is the first command-line argument.
    auto is_first() const noexcept -> bool {
        return _argi == 1;
    }

    /// @brief Indicates if this is the last command-line argument.
    auto is_last() const noexcept -> bool {
        return _argi == _argc - 1;
    }

    /// @brief Returns the value of this argument if valid, an empty string view otherwise.
    /// @see starts_with
    /// @see ends_with
    auto get() const noexcept -> value_type {
        if(has_value()) {
            return value_type(_argv[_argi]);
        }
        return {};
    }

    /// @brief Implicit cast to value_type.
    /// @see get
    operator value_type() const noexcept {
        return get();
    }

    /// @brief Returns the argument following this one.
    /// @see prev
    auto next() const noexcept -> program_arg {
        return {_argi + 1, _argc, _argv};
    }

    /// @brief Returns the argument preceding this one.
    /// @see next
    auto prev() const noexcept -> program_arg {
        return {_argi - 1, _argc, _argv};
    }

    /// @brief Indicates if the argument starts with str
    /// @see get
    /// @see ends_with
    /// @see is_long_tag
    auto starts_with(value_type str) const noexcept -> bool {
        return get().starts_with(str);
    }

    /// @brief Indicates if the argument ends with str
    /// @see get
    /// @see starts_with
    /// @see is_long_tag
    auto ends_with(value_type str) const noexcept -> bool {
        return get().ends_with(str);
    }

    /// @brief Indicates if the argument is "--<str>"
    /// @see get
    /// @see starts_with
    /// @see ends_with
    auto is_long_tag(value_type str) const noexcept -> bool {
        return get().starts_with("--") && get().ends_with(str) &&
               (get().size() == str.size() + 2);
    }

    /// @brief Indicates if this argument's value is equal to the specified string.
    auto operator==(const value_type& v) const noexcept {
        return get() == v;
    }

    /// @brief Indicates if this argument's value is different than the specified string.
    auto operator!=(const value_type& v) const noexcept {
        return get() != v;
    }

private:
    int _argi{0};
    int _argc{0};
    const char** _argv{nullptr};

    friend class program_arg_iterator;
    friend class program_args;
};
//------------------------------------------------------------------------------
static inline auto to_string(const program_arg& arg) {
    return std::string{arg.get()};
}
//------------------------------------------------------------------------------
static inline auto operator<<(std::ostream& out, const program_arg& arg)
  -> std::ostream& {
    return out << arg.get();
}
//------------------------------------------------------------------------------
/// @brief Iterator type over program_arg instances.
class program_arg_iterator {
    using this_class = program_arg_iterator;

public:
    constexpr program_arg_iterator(const program_arg arg) noexcept
      : _a{arg} {}

    /// @brief Alias for the referenced value type.
    using value_type = program_arg;

    /// @brief Alias for difference type.
    using difference_type = int;

    /// @brief Alias for reference type.
    using reference = program_arg&;

    /// @brief Alias for const reference type.
    using const_reference = const program_arg&;

    /// @brief Alias for pointer type.
    using pointer = program_arg*;

    /// @brief Alias for const pointer type.
    using const_pointer = const program_arg*;

    /// @brief Alias for iterator category.
    using iterator_category = std::random_access_iterator_tag;

    /// @brief Equality comparison.
    friend constexpr auto
    operator==(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) == 0;
    }

    /// @brief Nonequality comparison.
    friend constexpr auto
    operator!=(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) != 0;
    }

    /// @brief Less-than comparison.
    friend constexpr auto
    operator<(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) < 0;
    }

    /// @brief Less-equal comparison.
    friend constexpr auto
    operator<=(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) <= 0;
    }

    /// @brief Greater-than comparison.
    friend constexpr auto
    operator>(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) > 0;
    }

    /// @brief Greater-equal comparison.
    friend constexpr auto
    operator>=(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) >= 0;
    }

    /// @brief Difference.
    friend constexpr auto
    operator-(const this_class& l, const this_class& r) noexcept
      -> difference_type {
        return _cmp(l._a, r._a);
    }

    /// @brief Pre-increment operator.
    constexpr auto operator++() noexcept -> this_class& {
        ++_a._argi;
        return *this;
    }

    /// @brief Pre-decrement operator.
    constexpr auto operator--() noexcept -> this_class& {
        --_a._argi;
        return *this;
    }

    /// @brief Post-increment operator.
    constexpr auto operator++(int) noexcept -> this_class {
        this_class result{*this};
        ++_a._argi;
        return result;
    }

    /// @brief Post-decrement operator.
    constexpr auto operator--(int) noexcept -> this_class {
        this_class result{*this};
        --_a._argi;
        return result;
    }

    /// @brief Increment operator.
    constexpr auto operator+=(const difference_type dist) noexcept
      -> this_class& {
        _a._argi += dist;
        return *this;
    }

    /// @brief Decrement operator.
    constexpr auto operator-=(const difference_type dist) noexcept
      -> this_class& {
        _a._argi -= dist;
        return *this;
    }

    /// @brief Difference addition.
    constexpr auto operator+(const difference_type dist) noexcept
      -> this_class {
        this_class result{*this};
        result._a._argi += dist;
        return result;
    }

    /// @brief Difference subtraction.
    constexpr auto operator-(const difference_type dist) noexcept
      -> this_class {
        this_class result{*this};
        result._a._argi -= dist;
        return result;
    }

    /// @brief Dereference operator.
    constexpr auto operator*() noexcept -> reference {
        return _a;
    }

    /// @brief Const dereference operator.
    constexpr auto operator*() const noexcept -> const_reference {
        return _a;
    }

private:
    static constexpr auto
    _cmp(const program_arg& l, const program_arg& r) noexcept -> int {
        return l._argi - r._argi;
    }

    program_arg _a{};
};
//------------------------------------------------------------------------------
/// @brief Class wrapping the main function arguments, providing a convenient API.
/// @ingroup main_context
class program_args {
public:
    /// @brief Default constructor.
    /// @post empty()
    program_args() noexcept = default;

    /// @brief  Construction from the length and pointer to the argument list.
    program_args(const int argn, char** args) noexcept
      : _argc{argn}
      , _argv{const_cast<const char**>(args)} {}

    /// @brief  Construction from the length and const pointer to the argument list.
    program_args(const int argn, const char** args) noexcept
      : _argc{argn}
      , _argv{args} {}

    /// @brief Alias for the element value type.
    using value_type = std::string_view;

    /// @brief Alias for the element count type.
    using size_type = int;

    /// @brief Alias for iterator type.
    using iterator = program_arg_iterator;

    /// @brief Returns the number of arguments.
    auto argc() const noexcept -> int {
        return _argc;
    }

    /// @brief Returns a pointer to tha list of argument C-strings.
    auto argv() const noexcept -> const char** {
        return _argv;
    }

    /// @brief Indicates if the argument list is completely empty.
    auto empty() const noexcept -> bool {
        return _argc <= 0;
    }

    /// @brief Indicates if the argument list does not contain any arguments.
    auto none() const noexcept -> bool {
        return _argc <= 1;
    }

    /// @brief Returns the count of arguments (counting in the command name)
    auto size() const noexcept -> int {
        return _argc;
    }

    /// @brief Returns the command line argument value at the specified position.
    auto get(const int pos) const noexcept -> program_arg {
        return {pos, _argc, _argv};
    }

    /// @brief Returns the command line argument value at the specified position.
    auto operator[](const int pos) const noexcept -> program_arg {
        return get(pos);
    }

    /// @brief Returns the command name.
    auto command() const noexcept -> program_arg {
        return get(0);
    }

    /// @brief Returns first argument.
    auto first() const noexcept -> program_arg {
        return {1, _argc, _argv};
    }

    /// @brief Returns an iterator to the first argument (not the command name).
    auto begin() const noexcept -> iterator {
        return {program_arg(1, _argc, _argv)};
    }

    /// @brief Returns an iterator past the last argument.
    auto end() const noexcept -> iterator {
        return {program_arg(_argc, _argc, _argv)};
    }

    /// @brief Finds and returns the argument with the specified value.
    auto find(const std::string_view what) const noexcept -> program_arg {
        int i = 1;
        while(i < _argc) {
            if((_argv != nullptr) && (_argv[i] != nullptr)) {
                if(std::string_view(_argv[i]) == what) {
                    break;
                }
            }
            ++i;
        }
        return {i, _argc, _argv};
    }

private:
    const int _argc{0};
    const char** _argv{nullptr};
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_PROGRAM_ARGS_HPP
