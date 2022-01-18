/// @example mirror/rest_api.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/rest_api.hpp>
#include <iostream>
#include <map>
#include <sstream>

class too_smart_home {
private:
    std::map<std::string, std::string> _users;

    struct room_info {
        bool lights_on{false};
        bool windows_open{false};
    };

    std::map<std::string, room_info> _rooms;

    struct session_info {
        std::string username;
        bool is_admin{false};
    };

    using session_id_t = std::uintmax_t;
    std::map<session_id_t, session_info> _sessions;
    session_id_t _session_id{0U};
    bool _is_online{true};

    auto _get_session_id() noexcept {
        ++_session_id;
        while(!_session_id) {
            ++_session_id;
        }
        return _session_id;
    }

    auto _find_session(session_id_t sid) const noexcept -> const session_info* {
        if(_is_online) {
            if(const auto pos{_sessions.find(sid)}; pos != _sessions.end()) {
                return &pos->second;
            }
        }
        return nullptr;
    }

public:
    enum class error_code {
        no_such_room,
        invalid_session,
        permission_denied,
        invalid_room_name,
        is_offline
    };

    template <typename T>
    using result = std::variant<T, error_code>;

    too_smart_home() {
        _rooms["kitchen"] = {};
        _rooms["hall"] = {};
        _rooms["living-room"] = {};
        _rooms["study"] = {};
        _rooms["bedroom"] = {};
        _rooms["bathroom"] = {};
    }

    auto ping(std::string what) -> result<std::string> {
        if(!_is_online) {
            return {error_code::is_offline};
        }
        return {what};
    }

    auto login(std::string username, std::string password)
      -> result<session_id_t> {
        if(_is_online) {
            session_info session{};
            session_id_t sid{0U};
            if(username == "admin" && password == "supersecret") {
                sid = _get_session_id();
                session.is_admin = true;
            } else if(const auto pos = _users.find(username);
                      pos != _users.end()) {
                if(password == pos->second) {
                    sid = _get_session_id();
                    session.is_admin = false;
                }
            }
            if(sid) {
                session.username = std::move(username);
                _sessions[sid] = std::move(session);
            }
            return {sid};
        }
        return {error_code::is_offline};
    }

    auto logout(session_id_t sid) -> result<std::string> {
        if(_is_online) {
            if(const auto pos{_sessions.find(sid)}; pos != _sessions.end()) {
                auto result = "Bye, " + pos->second.username + "!";
                _sessions.erase(pos);
                return result;
            }
        }
        return {error_code::is_offline};
    }

    auto add_user(session_id_t sid, std::string username, std::string password)
      -> result<std::string> {
        if(const auto session{_find_session(sid)}) {
            if(session->is_admin) {
                _users[username] = password;
                return {"user added"};
            }
            return {error_code::permission_denied};
        }
        return {error_code::invalid_session};
    }

    auto shutdown(session_id_t sid) -> result<std::string> {
        if(const auto session{_find_session(sid)}) {
            if(session->is_admin) {
                _sessions.clear();
                _is_online = false;
                return {"shutdown"};
            }
            return {error_code::permission_denied};
        }
        return {error_code::invalid_session};
    }

    auto open_windows(session_id_t sid, std::string room_name)
      -> result<std::string> {
        if(_find_session(sid)) {
            if(const auto pos = _rooms.find(room_name); pos != _rooms.end()) {
                if(pos->second.windows_open) {
                    return {"already open"};
                } else {
                    pos->second.windows_open = true;
                    return {"windows opened"};
                }
            }
            return {error_code::invalid_room_name};
        }
        return {error_code::invalid_session};
    }

    auto close_windows(session_id_t sid, std::string room_name)
      -> result<std::string> {
        if(_find_session(sid)) {
            if(const auto pos = _rooms.find(room_name); pos != _rooms.end()) {
                if(!pos->second.windows_open) {
                    return {"already closed"};
                } else {
                    pos->second.windows_open = false;
                    return {"windows closed"};
                }
            }
            return {error_code::invalid_room_name};
        }
        return {error_code::invalid_session};
    }

    auto windows_status(session_id_t sid, std::string room_name) const
      -> result<std::string> {
        if(_find_session(sid)) {
            if(const auto pos = _rooms.find(room_name); pos != _rooms.end()) {
                if(pos->second.windows_open) {
                    return {"open"};
                } else {
                    return {"closed"};
                }
            }
            return {error_code::invalid_room_name};
        }
        return {error_code::invalid_session};
    }
};

int main() {
    mirror::rest_api_adaptor<too_smart_home> server("https", "home", {});

    const auto get =
      [&](const mirror::url& request) -> std::optional<std::string> {
        mirror::rest_api_response response;
        if(server.handle(request, response)) {
            return {response.str()};
        } else {
            std::cerr << server.domain() << ": " << response.str() << std::endl;
        }
        return {};
    };
    const auto show = [&](const auto& response) {
        if(response) {
            std::cout << server.domain() << ": " << *response << std::endl;
        }
    };

    if(get({"https://home/ping?what=hello"})) {
        auto sid = get({"https://admin:supersecret@home/login"});
        if(sid) {
            show(get(
              {"https://home/add_user?username=johnny+password=qwerty+sid=" +
               *sid}));
            show(get({"https://home/logout?sid=" + *sid}));

            sid = get({"https://johnny:qwerty@home/login"});
            show(get({"http://home/shutdown?sid=" + *sid}));
            show(get({"https://home/shutdown?sid=" + *sid}));
            show(
              get({"https://home/open_windows?room_name=kitchen+sid=" + *sid}));
            show(get(
              {"https://home/window_status?room_name=bathroom+sid=" + *sid}));
            show(get(
              {"https://home/windows_status?room_name=bathroom+sid=" + *sid}));
            show(
              get({"https://home/close_windows?room_name=study+sid=" + *sid}));
            show(get({"https://home/logout?sid=" + *sid}));
            show(
              get({"https://home/open_windows?room_name=bedroom+sid=" + *sid}));

            sid = get({"https://admin:supersecret@home/login"});
            show(get({"https://home/shutdown?sid=" + *sid}));
            show(get({"https://home/logout?sid=" + *sid}));
        }
    } else {
        std::cerr << "home server not accessible" << std::endl;
    }

    return 0;
}
