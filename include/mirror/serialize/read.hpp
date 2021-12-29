/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_READ_HPP
#define MIRROR_SERIALIZE_READ_HPP

#include "../branch_predict.hpp"
#include "../primitives.hpp"
#include "../tribool.hpp"
#include "read_backend.hpp"
#include <array>
#include <span>
#include <type_traits>
#include <variant>
#include <vector>

namespace mirror::serialize {
//------------------------------------------------------------------------------
template <typename T>
struct deserializer;

struct read_driver {
    template <typename T, read_backend Backend>
    auto
    read(Backend& backend, typename Backend::context_param ctx, T& value) const
      -> serialization_errors {
        deserializer<std::remove_cv_t<T>> reader;
        return reader.read(*this, backend, ctx, value);
    }
};
//------------------------------------------------------------------------------
template <typename T>
struct deserializer<T&> : deserializer<T> {};
//------------------------------------------------------------------------------
template <typename T>
struct plain_deserializer {
    template <read_backend Backend>
    static auto read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      T& value) noexcept {
        return backend.read(driver, ctx, value);
    }
};
//------------------------------------------------------------------------------
template <>
struct deserializer<bool> : plain_deserializer<bool> {};
template <>
struct deserializer<tribool> : plain_deserializer<tribool> {};
template <>
struct deserializer<char> : plain_deserializer<char> {};
template <>
struct deserializer<std::int8_t> : plain_deserializer<std::int8_t> {};
template <>
struct deserializer<short> : plain_deserializer<short> {};
template <>
struct deserializer<int> : plain_deserializer<int> {};
template <>
struct deserializer<long> : plain_deserializer<long> {};
template <>
struct deserializer<long long> : plain_deserializer<long long> {};
template <>
struct deserializer<std::uint8_t> : plain_deserializer<std::uint8_t> {};
template <>
struct deserializer<unsigned short> : plain_deserializer<unsigned short> {};
template <>
struct deserializer<unsigned> : plain_deserializer<unsigned> {};
template <>
struct deserializer<unsigned long> : plain_deserializer<unsigned long> {};
template <>
struct deserializer<unsigned long long>
  : plain_deserializer<unsigned long long> {};
template <>
struct deserializer<float> : plain_deserializer<float> {};
template <>
struct deserializer<double> : plain_deserializer<double> {};
template <>
struct deserializer<std::string> : plain_deserializer<std::string> {};
//------------------------------------------------------------------------------
template <typename T, size_t N>
struct deserializer<std::span<T, N>> {
    template <read_backend Backend>
    auto write(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::span<T, N> value) const noexcept {

        deserialization_errors errors{};
        size_t size = value.size();
        const auto subctx{backend.begin_list(ctx, size)};
        if(size > value.size()) {
            errors |= deserialization_error_code::excess_element;
        } else if(size < value.size()) {
            errors |= deserialization_error_code::missing_element;
        } else if(MIRROR_LIKELY(has_value(subctx))) {
            size_t idx = 0;
            bool first = true;
            for(const auto& elem : value) {
                if(first) {
                    first = false;
                } else {
                    errors |= backend.separate_attribute(extract(subctx));
                }
                const auto subsubctx{
                  backend.begin_element(extract(subctx), idx)};
                errors |= driver.read(backend, extract(subsubctx), elem);
                errors |= backend.finish_element(extract(subctx), idx);
                ++idx;
            }
            errors |= backend.finish_list(extract(subctx));
        } else {
            errors |= std::get<deserialization_errors>(subctx);
        }
        return errors;
    }
};
//------------------------------------------------------------------------------
/// @brief Deserializes a value with the specified deserialization backend.
/// @ingroup serialization
/// @see serialize
template <typename T, read_backend Backend>
auto read(
  T& value,
  Backend& backend,
  typename Backend::context_param ctx) noexcept -> deserialization_errors {
    deserialization_errors errors{};
    auto subctx{backend.begin(ctx)};
    if(MIRROR_LIKELY(has_value(subctx))) {
        read_driver driver;
        errors |= driver.read(backend, extract(subctx), value);
        errors |= backend.finish(extract(subctx));
    } else {
        errors |= std::get<deserialization_errors>(subctx);
    }
    return errors;
}
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif
