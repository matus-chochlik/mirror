/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SQLITE3_HPP
#define MIRROR_SQLITE3_HPP
#include <iostream>

#if !MIRROR_HAS_SQLITE3
#error "SQLite3 required but not found!"
#else
#include "extract.hpp"
#include "from_string.hpp"
#include "sequence.hpp"
#include <cassert>
#include <memory>
#include <optional>
#include <set>
#include <span>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

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
    std::vector<std::optional<std::string_view>> _values;
    std::vector<std::string_view> _names;

    friend class sqlite3_db;
    auto set(int count, char** values, char** names) noexcept -> const auto& {
        _values.clear();
        _names.clear();
        if(count > 0) {
            _values.reserve(static_cast<size_t>(count));
            _names.reserve(static_cast<size_t>(count));
            for(int i = 0; i < count; ++i) {
                using vt = std::optional<std::string_view>;
                _values.emplace_back(values[i] ? vt{values[i]} : vt{});
                _names.emplace_back(names[i]);
            }
        }
        return *this;
    }

public:
    sqlite3_row() noexcept = default;
    sqlite3_row(sqlite3_row&&) noexcept = default;
    sqlite3_row(const sqlite3_row&) = delete;
    auto operator=(sqlite3_row&&) = delete;
    auto operator=(const sqlite3_row&) = delete;

    auto size() const noexcept -> size_t {
        return _values.size();
    }

    auto names() const noexcept -> std::span<const std::string_view> {
        return {_names};
    }

    auto index_of(std::string_view name) const noexcept
      -> std::optional<size_t> {
        const auto pos = std::find(_names.begin(), _names.end(), name);
        if(pos != _names.end()) {
            return {static_cast<size_t>(std::distance(_names.begin(), pos))};
        }
        return {};
    }

    auto values() const noexcept
      -> std::span<const std::optional<std::string_view>> {
        return {_values};
    }

    auto value(size_t idx) const noexcept -> std::optional<std::string_view> {
        assert(idx < size());
        return {_values[idx]};
    }

    auto has_value(size_t idx, std::string_view val) const noexcept -> bool {
        return value(idx) == val;
    }

    auto value(std::optional<size_t> idx) const noexcept
      -> std::optional<std::string_view> {
        if(idx) {
            return value(*idx);
        }
        return {};
    }

    auto value_of(std::string_view name) const noexcept
      -> std::optional<std::string_view> {
        return value(index_of(name));
    }

    template <typename T>
    auto fetch(T& instance) const -> bool requires(std::is_class_v<T>) {
        bool result = true;
        for_each(get_data_members(mirror(T)), [&](auto mdm) {
            using mirror::has_value;
            using mirror::extract;
            if(const auto opt_val{from_extractable_string(
                 value_of(get_name(mdm)), get_reflected_type(get_type(mdm)))};
               has_value(opt_val)) {
                get_reference(mdm, instance) = extract(opt_val);
            } else {
                result = false;
            }
        });
        return result;
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

    template <typename T>
    static auto _get_sql_type(std::type_identity<T>, int) -> std::string_view
      requires(std::convertible_to<T, std::string_view>) {
        return "varchar";
    }

    template <typename T>
    static auto _get_sql_type(std::type_identity<T>, int) -> std::string_view
      requires(std::is_integral_v<T>) {
        return "integer";
    }

    template <typename T>
    static auto _get_sql_type(std::type_identity<T>, ...) -> std::string_view
      requires(std::convertible_to<T, std::string_view>) {
        return "varchar";
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

    void execute(std::string_view sql) {
        char* err_msg = nullptr;
        auto wrapper = [](void*, int, char**, char**) -> int {
            return 0;
        };
        if(
          ::sqlite3_exec(
            _handle.get(), sql.data(), wrapper, nullptr, &err_msg) !=
          SQLITE_OK) {
            const std::unique_ptr<char, void (*)(void*)> free_msg{
              err_msg, &::sqlite3_free};
            throw sqlite3_error(err_msg);
        }
    }

    template <typename T>
    void ensure_table(std::type_identity<T> = {}) {
        const auto table_name{get_name(remove_all_aliases(mirror(T)))};
        std::string table_query{
          "SELECT count(1) FROM sqlite_master WHERE type='table' AND name='"};
        table_query.append(table_name);
        table_query.append("'");
        bool needs_table = true;
        execute(table_query, [&](const auto& count_data) {
            needs_table = count_data.has_value(0, "0");
        });

        if(needs_table) {
            std::string table_create{"CREATE TABLE "};
            table_create.append(table_name);
            table_create.append("(");
            bool first = true;
            for_each(get_data_members(mirror(T)), [&](auto mdm) {
                if(first) {
                    first = false;
                } else {
                    table_create.append(", ");
                }
                table_create.append(get_name(mdm));
                table_create.append(" ");
                table_create.append(
                  _get_sql_type(get_reflected_type(get_type(mdm)), 0));
            });
            table_create.append(")");
            execute(table_create);
        } else {
            std::string column_query{"pragma table_info("};
            column_query.append(table_name);
            column_query.append(")");
            std::set<std::string> columns;
            execute(column_query, [&](const auto& col_data) {
                using mirror::has_value;
                using mirror::extract;
                if(const auto col_name{col_data.value_of("name")};
                   has_value(col_name)) {
                    columns.insert(std::string(extract(col_name)));
                }
            });
            for_each(get_data_members(mirror(T)), [&](auto mdm) {
                const auto column_name{get_name(mdm)};
                if(!columns.contains(std::string(column_name))) {
                    std::string column_add{"ALTER TABLE "};
                    column_add.append(table_name);
                    column_add.append(" ADD COLUMN ");
                    column_add.append(column_name);
                    column_add.append(" ");
                    column_add.append(
                      _get_sql_type(get_reflected_type(get_type(mdm)), 0));
                    execute(column_add);
                }
            });
        }
    }

    template <typename T>
    auto fetch(std::string_view sql, std::vector<T>& dest)
      -> auto& requires(std::is_class_v<T>) {
        execute(sql, [&](const auto& row) {
            T instance{};
            if(row.fetch(instance)) {
                dest.emplace_back(std::move(instance));
            }
        });
        return dest;
    }
};

} // namespace mirror

#endif // MIRROR_HAS_SQLITE3

#endif
