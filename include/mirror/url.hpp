/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_URL_HPP
#define MIRROR_URL_HPP

#include "diagnostic.hpp"
#include <cassert>
#include <charconv>
#include <optional>
#include <regex>
#include <string_view>

namespace mirror {

/// @brief Class parsing and providing access to parts of a URL.
/// @ingroup utilities
class url {
private:
    url(std::string, std::match_results<std::string::iterator>) noexcept;

    void _cover(
      std::string_view& part,
      const std::match_results<std::string::iterator>& match,
      const std::size_t index) const noexcept;

    static auto _get_regex() noexcept -> const std::regex&;

    std::string _url_str;
    std::string_view _scheme;
    std::string_view _login;
    std::string_view _passwd;
    std::string_view _host;
    std::string_view _port;
    std::string_view _path;
    std::string_view _query;
    std::string_view _fragment;
    bool _parsed{false};

    static auto _get_opt(std::string_view str) noexcept
      -> std::optional<std::string_view> {
        if(!str.empty()) {
            return {str};
        }
        return {};
    }

public:
    /// @brief Default constructor.
    url() noexcept = default;

    /// @brief Construction from a string.
    url(std::string url_str) noexcept
      : url{std::move(url_str), std::match_results<std::string::iterator>{}} {}

    /// @brief Equality comparison.
    friend auto operator==(const url& l, const url& r) noexcept {
        return l._url_str == r._url_str;
    }

    /// @brief Less-thancomparison.
    friend auto operator<(const url& l, const url& r) noexcept {
        return l._url_str < r._url_str;
    }

    /// @brief Indicates if the URL was parsed successfully.
    auto is_valid() const noexcept {
        return _parsed;
    }

    /// @brief Indicates if the URL was parsed successfully.
    /// @see is_valid
    explicit operator bool() const noexcept {
        return is_valid();
    }

    /// @brief Returns the whole URL string.
    auto str() const noexcept -> std::string_view {
        return {_url_str};
    }

    /// @brief Returns the scheme.
    /// @see has_scheme
    auto scheme() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_scheme);
    }

    /// @brief Checks if the url scheme matches the given string.
    /// @see scheme
    auto has_scheme(const std::string_view str) const noexcept -> bool {
        return str == _scheme;
    }

    /// @brief Returns the login name.
    auto login() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_login);
    }

    /// @brief Returns the login password.
    auto password() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_passwd);
    }

    /// @brief Returns the host name or IP address.
    auto host() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_host);
    }

    /// @brief Checks if the url host matches the given string.
    /// @see host
    auto has_host(const std::string_view str) const noexcept -> bool {
        return str == _host;
    }

    /// @brief Returns the port string.
    auto port_str() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_port);
    }

    /// @brief Returns the port number.
    auto port() const noexcept -> std::optional<int> {
        int result = 0;
        if(std::from_chars(_port.begin(), _port.end(), result).ec == std::errc{}) {
            return {result};
        }
        return {};
    }

    /// @brief Returns the path string.
    auto path() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_path);
    }

    /// @brief Checks if the path matches the given string.
    /// @see path_str
    /// @see path
    auto has_path(const std::string_view str) const noexcept -> bool {
        return str == _path;
    }

    /// @brief Returns the query string.
    auto query() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_query);
    }

    /// @brief Returns the value of the specified query argument.
    /// @see query
    auto argument(const std::string_view arg_name) const noexcept
      -> std::optional<std::string_view>;

    /// @brief Returns the fragment.
    auto fragment() const noexcept -> std::optional<std::string_view> {
        return _get_opt(_fragment);
    }
};
//------------------------------------------------------------------------------
inline auto url::_get_regex() noexcept -> const std::regex& {
#ifdef __clang__
    MIRROR_DIAG_PUSH()
    MIRROR_DIAG_OFF(exit-time-destructors)
#endif
    // clang-format off
    static const std::regex re{
      R"(^((([\w]+):)?\/\/)(([^:]+)(:(\S+))?@)?((((\w[\w_-]{0,62}(\.\w[\w_-]{0,62})*))|((10|127)(\.\d{1,3}){3})|((169\.254|192\.168)(\.\d{1,3}){2})|(172\.(1[6-9]|2\d|3[0-1])(\.\d{1,3}){2})|([1-9]\d?|1\d\d|2[01]\d|22[0-3])(\.(1?\d{1,2}|2[0-4]\d|25[0-5])){2}(\.([1-9]\d?|1\d\d|2[0-4]\d|25[0-4])))(:(\d{1,5}))?)?((/[\w_-]+)*/?)?(\?(([\w_]+=[^+#]*)(\+([\w_]+=[^+#]*))*))?(#([\w_-]*))?$)",
      std::regex::ECMAScript};
    // clang-format on
#ifdef __clang__
    MIRROR_DIAG_POP()
#endif
    return re;
}
//------------------------------------------------------------------------------
inline void url::_cover(
  std::string_view& part,
  const std::match_results<std::string::iterator>& match,
  const std::size_t index) const noexcept {
    assert(index < match.size());
    auto& m = match[index];
    part = str().substr(
      static_cast<std::size_t>(m.first - _url_str.begin()),
      static_cast<std::size_t>(m.second - m.first));
}
//------------------------------------------------------------------------------
inline url::url(
  std::string url_str,
  std::match_results<std::string::iterator> match) noexcept
  : _url_str{std::move(url_str)}
  , _parsed{
      std::regex_match(_url_str.begin(), _url_str.end(), match, _get_regex())} {

    if(_parsed) {
        _cover(_scheme, match, 3);
        _cover(_login, match, 5);
        _cover(_passwd, match, 7);
        _cover(_host, match, 9);
        _cover(_port, match, 28);
        _cover(_path, match, 29);
        _cover(_query, match, 32);
        _cover(_fragment, match, 37);
    }
}
//------------------------------------------------------------------------------
auto url::argument(const std::string_view arg_name) const noexcept
  -> std::optional<std::string_view> {
    auto src = _query;
    while(!src.empty()) {
        const auto pos = src.find('+');
        const auto pair = src.substr(0Z, pos);
        if(pair.starts_with(arg_name)) {
            return pair.substr(arg_name.size() + 1Z);
        }
        src = src.substr(pos + 1Z);
    }
    return {};
}
//------------------------------------------------------------------------------
} // namespace mirror

#endif
