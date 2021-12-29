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
#include "../placeholder.hpp"
#include "../sequence.hpp"
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
      -> read_errors {
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
    auto read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::span<T, N> value) const noexcept {

        read_errors errors{};
        size_t size = value.size();
        const auto subctx{backend.begin_list(ctx, size)};
        if(size > value.size()) {
            errors |= read_error_code::excess_element;
        } else if(size < value.size()) {
            errors |= read_error_code::missing_element;
        } else if(MIRROR_LIKELY(has_value(subctx))) {
            size_t idx = 0;
            bool first = true;
            for(auto& elem : value) {
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
            errors |= std::get<read_errors>(subctx);
        }
        return errors;
    }
};
//------------------------------------------------------------------------------
template <typename T, size_t N>
struct deserializer<std::array<T, N>> : deserializer<std::span<T, N>> {
    template <read_backend Backend>
    auto read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::array<T, N>& value) const noexcept {
        return deserializer<std::span<T, N>>::read(
          driver, backend, ctx, std::span(value));
    }
};
//------------------------------------------------------------------------------
template <typename T, typename A>
struct deserializer<std::vector<T, A>> {
    template <read_backend Backend>
    auto read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      std::vector<T, A>& value) const noexcept {

        read_errors errors{};
        size_t size{0Z};
        const auto subctx{backend.begin_list(ctx, size)};
        value.resize(size);
        if(MIRROR_LIKELY(has_value(subctx))) {
            size_t idx = 0;
            bool first = true;
            for(auto& elem : value) {
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
            errors |= std::get<read_errors>(subctx);
        }
        return errors;
    }
};
//------------------------------------------------------------------------------
template <typename T>
struct deserializer {
private:
    template <read_backend Backend>
    auto _do_read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      T& value,
      metaobject auto mt) const noexcept -> read_errors
      requires(reflects_record(mt)) {
        read_errors errors{};
        const auto mdms{filter(get_data_members(mt), not_(is_static(_1)))};
        size_t count{get_size(mdms)};
        auto subctx{backend.begin_record(ctx, count)};

        if(count > get_size(mdms)) {
            errors |= read_error_code::excess_member;
        } else if(count < get_size(mdms)) {
            errors |= read_error_code::missing_member;
        }
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
                    errors |= driver.read(
                      backend, extract(subsubctx), get_reference(mdm, value));
                    errors |=
                      backend.finish_attribute(extract(subsubctx), name);
                } else {
                    errors |= std::get<read_errors>(subsubctx);
                }
            });
            errors |= backend.finish_record(extract(subctx));
        } else {
            errors |= std::get<read_errors>(subctx);
        }
        return errors;
    }

    template <read_backend Backend>
    auto _do_read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      T& value,
      metaobject auto mt) const noexcept -> read_errors
      requires(reflects_enum(mt)) {
        read_errors errors{};
        const auto mes{get_enumerators(mt)};
        if(backend.enum_as_string(ctx)) {
            std::string name;
            errors |= driver.read(backend, ctx, name);
            for_each(mes, [&](auto me) {
                if(get_name(me) == name) {
                    value = get_constant(me);
                }
            });
        } else {
            std::underlying_type_t<T> temp{};
            errors |= driver.read(backend, ctx, temp);
            value = static_cast<T>(temp);
        }
        return errors;
    }

public:
    template <read_backend Backend>
    auto read(
      const read_driver& driver,
      Backend& backend,
      typename Backend::context_param ctx,
      T& value) const noexcept {
        return _do_read(driver, backend, ctx, value, mirror(T));
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
  typename Backend::context_param ctx) noexcept -> read_errors {
    read_errors errors{};
    auto subctx{backend.begin(ctx)};
    if(MIRROR_LIKELY(has_value(subctx))) {
        read_driver driver;
        errors |= driver.read(backend, extract(subctx), value);
        errors |= backend.finish(extract(subctx));
    } else {
        errors |= std::get<read_errors>(subctx);
    }
    return errors;
}
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif
