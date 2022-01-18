/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SQLITE3_HPP
#define MIRROR_SQLITE3_HPP

#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#if !MIRROR_HAS_SQLITE3
#error "SQLite3 required but not found!"
#else
#include <sqlite3.h>

namespace mirror {

class sqlite3_db;
class sqlite3_error : std::runtime_error {
private:
    friend class sqlite3_db;

    sqlite3_error(std::string msg) noexcept
      : std::runtime_error{std::move(msg)} {}

    sqlite3_error(::sqlite3* handle)
      : sqlite3_error{::sqlite3_errmsg(handle)} {}
};

class sqlite3_row {
private:
    std::vector<std::string_view> _values;
    std::vector<std::string_view> _names;

public:
    auto set(int count, char** values, char** names) noexcept -> const auto& {
        _values.clear();
        _names.clear();
        if(count > 0) {
            _values.reserve(static_cast<size_t>(count));
            _names.reserve(static_cast<size_t>(count));
            for(int i = 0; i < count; ++i) {
                _values.emplace_back(values[i]);
                _names.emplace_back(names[i]);
            }
        }
        return *this;
    }

    auto size() const noexcept -> size_t {
        return _values.size();
    }

    auto names() const noexcept -> std::span<const std::string_view> {
        return {_names};
    }

    auto values() const noexcept -> std::span<const std::string_view> {
        return {_values};
    }
};

class sqlite3_db {
private:
    using handle_ptr = std::unique_ptr<::sqlite3, int (*)(::sqlite3*)>;
    handle_ptr _handle{nullptr, nullptr};

    static auto _open(std::string_view path) {
        ::sqlite3* handle{nullptr};
        if(::sqlite3_open(path.data(), &handle)) {
            throw sqlite3_error(handle);
        }
        return handle_ptr{handle, &::sqlite3_close};
    }

public:
    sqlite3_db() noexcept = default;
    sqlite3_db(std::string_view path)
      : _handle{_open(path)} {}

    template <typename Callback>
    void execute(std::string_view sql, Callback callback) {
        sqlite3_row row_store;
        auto context = std::tie(callback, row_store);
        char* err_msg = nullptr;
        auto wrapper =
          [](void* pcontext, int count, char** values, char** names) -> int {
            auto& [handle, row] =
              *reinterpret_cast<decltype(context)*>(pcontext);
            handle(row.set(count, values, names));
            return 0;
        };
        if(
          ::sqlite3_exec(
            _handle.get(), sql.data(), wrapper, &context, &err_msg) !=
          SQLITE_OK) {
            const std::unique_ptr<char, void (*)(void*)> free_msg{
              err_msg, &::sqlite3_free};
            throw sqlite3_error(err_msg);
        }
    }
};

} // namespace mirror

#endif // MIRROR_HAS_SQLITE3

#endif
