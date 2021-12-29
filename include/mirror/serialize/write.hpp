/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_WRITE_HPP
#define MIRROR_SERIALIZE_WRITE_HPP

#include "../branch_predict.hpp"
#include "../primitives.hpp"
#include "../tribool.hpp"
#include "write_backend.hpp"
#include <array>
#include <span>
#include <type_traits>
#include <variant>
#include <vector>

namespace mirror::serialize {
//------------------------------------------------------------------------------
template <typename T>
struct serializer;

struct write_driver {
    template <typename T, write_backend Backend>
    auto write(
      Backend& backend,
      typename Backend::context_param ctx,
      const T& value) const -> serialization_errors {
        serializer<std::remove_cv_t<T>> writer;
        return writer.write(*this, backend, ctx, value);
    }
};
//------------------------------------------------------------------------------
template <typename T>
struct serializer<T&> : serializer<T> {};
//------------------------------------------------------------------------------
template <typename T>
struct serializer<const T&> : serializer<T> {};
//------------------------------------------------------------------------------
template <typename T>
struct plain_serializer {
    template <write_backend Backend>
    static auto write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      const T value) noexcept {
        return backend.write(driver, ctx, value);
    }
};
//------------------------------------------------------------------------------
template <>
struct serializer<bool> : plain_serializer<bool> {};
template <>
struct serializer<tribool> : plain_serializer<tribool> {};
template <>
struct serializer<char> : plain_serializer<char> {};
template <>
struct serializer<std::int8_t> : plain_serializer<std::int8_t> {};
template <>
struct serializer<short> : plain_serializer<short> {};
template <>
struct serializer<int> : plain_serializer<int> {};
template <>
struct serializer<long> : plain_serializer<long> {};
template <>
struct serializer<long long> : plain_serializer<long long> {};
template <>
struct serializer<std::uint8_t> : plain_serializer<std::uint8_t> {};
template <>
struct serializer<unsigned short> : plain_serializer<unsigned short> {};
template <>
struct serializer<unsigned> : plain_serializer<unsigned> {};
template <>
struct serializer<unsigned long> : plain_serializer<unsigned long> {};
template <>
struct serializer<unsigned long long> : plain_serializer<unsigned long long> {};
template <>
struct serializer<float> : plain_serializer<float> {};
template <>
struct serializer<double> : plain_serializer<double> {};
template <>
struct serializer<std::string_view> : plain_serializer<std::string_view> {};
template <>
struct serializer<std::string> : plain_serializer<std::string_view> {};
template <size_t N>
struct serializer<const char[N]> : plain_serializer<std::string_view> {};
template <size_t N>
struct serializer<char[N]> : plain_serializer<std::string_view> {};
//------------------------------------------------------------------------------
template <typename T, size_t N>
struct serializer<std::span<const T, N>> {
    template <write_backend Backend>
    auto write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::span<const T, N> value) const noexcept {

        serialization_errors errors{};
        auto subctx{backend.begin_list(ctx, value.size())};
        if(MIRROR_LIKELY(has_value(subctx))) {
            size_t idx = 0;
            bool first = true;
            for(const auto& elem : value) {
                if(first) {
                    first = false;
                } else {
                    errors |= backend.separate_attribute(extract(subctx));
                }
                auto subsubctx{backend.begin_element(extract(subctx), idx)};
                errors |= driver.write(backend, extract(subsubctx), elem);
                errors |= backend.finish_element(extract(subsubctx), idx);
                ++idx;
            }
            errors |= backend.finish_list(extract(subctx));
        } else {
            errors |= std::get<serialization_errors>(subctx);
        }
        return errors;
    }
};
//------------------------------------------------------------------------------
template <typename T, size_t N>
struct serializer<std::span<T, N>> : serializer<std::span<const T, N>> {};
//------------------------------------------------------------------------------
template <typename T, size_t N>
struct serializer<std::array<T, N>>
  : serializer<std::span<std::add_const_t<T>, N>> {
    template <write_backend Backend>
    auto write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::array<T, N> value) const noexcept {
        return serializer<std::span<std::add_const_t<T>, N>>::write(
          driver, backend, ctx, std::span(value));
    }
};
//------------------------------------------------------------------------------
template <typename T, typename A>
struct serializer<std::vector<T, A>>
  : serializer<std::span<std::add_const_t<T>>> {
    template <write_backend Backend>
    auto write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::vector<T, A> value) const noexcept {
        return serializer<std::span<std::add_const_t<T>>>::write(
          driver, backend, ctx, std::span(value));
    }
};
//------------------------------------------------------------------------------
template <typename T>
struct serializer {
private:
    template <write_backend Backend>
    auto _do_write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      const T& value,
      metaobject auto mt) const noexcept -> serialization_errors
      requires(reflects_record(mt)) {
        serialization_errors errors{};
        const auto mdms{get_data_members(mt)};
        auto subctx{backend.begin_record(ctx, get_size(mdms))};
        if(has_value(subctx)) {
            bool first = true;
            for_each(mdms, [&](auto mdm) {
                if(first) {
                    first = false;
                } else {
                    errors |= backend.separate_attribute(extract(subctx));
                }
                const auto name{get_name(mdm)};
                auto subsubctx{backend.begin_attribute(extract(subctx), name)};
                if(has_value(subsubctx)) {
                    errors |= driver.write(
                      backend, extract(subsubctx), get_value(mdm, value));
                    errors |=
                      backend.finish_attribute(extract(subsubctx), name);
                } else {
                    errors |= std::get<serialization_errors>(subsubctx);
                }
            });
            errors |= backend.finish_record(extract(subctx));
        } else {
            errors |= std::get<serialization_errors>(subctx);
        }
        return errors;
    }

    template <write_backend Backend>
    auto _do_write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      const T& value,
      metaobject auto mt) const noexcept -> serialization_errors
      requires(reflects_enum(mt)) {
        serialization_errors errors{};
        const auto mes{get_enumerators(mt)};
        if(backend.enum_as_string(ctx)) {
            for_each(mes, [&](auto me) {
                if(get_constant(me) == value) {
                    errors |= driver.write(backend, ctx, get_name(me));
                }
            });
        } else {
            errors |= driver.write(
              backend, ctx, static_cast<std::underlying_type_t<T>>(value));
        }
        return errors;
    }

public:
    template <write_backend Backend>
    auto write(
      const write_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      const T& value) const noexcept {
        return _do_write(driver, backend, ctx, value, mirror(T));
    }
};
//------------------------------------------------------------------------------
/// @brief Serializes a value with the specified serialization backend.
/// @ingroup serialization
/// @see deserialize
template <typename T, write_backend Backend>
auto write(
  const T& value,
  Backend& backend,
  typename Backend::context_param ctx) noexcept -> serialization_errors {
    serialization_errors errors{};
    auto subctx{backend.begin(ctx)};
    if(MIRROR_LIKELY(has_value(subctx))) {
        write_driver driver;
        errors |= driver.write(backend, extract(subctx), value);
        errors |= backend.finish(extract(subctx));
    } else {
        errors |= std::get<serialization_errors>(subctx);
    }
    return errors;
}
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif
