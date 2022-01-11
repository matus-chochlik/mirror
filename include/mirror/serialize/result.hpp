/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_RESULT_HPP
#define MIRROR_SERIALIZE_RESULT_HPP

#include "../bitfield.hpp"
#include <cstdint>
#include <variant>

namespace mirror::serialize {
//------------------------------------------------------------------------------
/// @brief Serialization error code bits enumeration.
/// @ingroup serialization
/// @see write_errors
/// @see serializer_backend
/// @see serializer_data_sink
enum class write_error_code : std::uint8_t {
    /// @brief Value type or format not supported.
    not_supported = 1U << 0U,
    /// @brief Too much data to fit into serialization data sink.
    too_much_data = 1U << 1U,
    /// @brief Incomplete write, remaining data should be written later.
    incomplete_write = 1U << 2U,
    /// @brief Internal error in the serialization data sink.
    data_sink_error = 1U << 3U,
    /// @brief Internal error in the serialization backend.
    backend_error = 1U << 4U
};
//------------------------------------------------------------------------------
/// @brief Deserialization error code bits enumeration.
/// @ingroup serialization
/// @see read_errors
/// @see deserializer_backend
/// @see deserializer_data_sink
enum class read_error_code : std::uint16_t {
    /// @brief Value type or format not supported.
    not_supported = 1U << 0U,
    /// @brief Not enough data to deserialize the value.
    not_enough_data = 1U << 1U,
    /// @brief Superfluous data in the deserialization source.
    unexpected_data = 1U << 2U,
    /// @brief Incomplete read, remaining data should be read later.
    incomplete_read = 1U << 3U,
    /// @brief Missing data for container element.
    missing_element = 1U << 4U,
    /// @brief Superfluous data for container element.
    excess_element = 1U << 5U,
    /// @brief Missing data for class data member.
    missing_member = 1U << 6U,
    /// @brief Superfluous data for class data member.
    excess_member = 1U << 7U,
    /// @brief Invalid data format.
    invalid_format = 1U << 8U,
    /// @brief Internal error in the deserialization data source.
    data_source_error = 1U << 9U,
    /// @brief Internal error in the deserialization backend.
    backend_error = 1U << 10U
};
//------------------------------------------------------------------------------
/// @brief Alias for serialization error bitfield.
/// @ingroup serialization
/// @see write_result
/// @see read_errors
using write_errors = bitfield<write_error_code>;

/// @brief Alias for deserialization error bitfield.
/// @ingroup serialization
/// @see read_result
/// @see write_errors
using read_errors = bitfield<read_error_code>;
//------------------------------------------------------------------------------
} // namespace mirror::serialize

#endif // EAGINE_SERIALIZE_RESULT_HPP
