/// @example mirror/gen_puml_diagram.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/all.hpp>
#include <vector>
//------------------------------------------------------------------------------
template <typename MT>
void print_type_puml(std::ostream& out, MT mt) {
    if(is_enum(mt)) {
        out << "enum";
    } else if(is_union(mt)) {
        out << "union";
    } else {
        out << "class";
    }
    out << " " << get_name(mt) << " {\n";
    if constexpr(is_enum(mt)) {
        for_each(get_enumerators(mt), [&](auto mo) {
            out << "  " << get_name(mo) << "\n";
        });
    } else {
        for_each_info(get_member_functions(mt), [&](auto mo, auto info) {
            out << "  ";
            if(is_private(mo)) {
                out << "-";
            } else if(is_protected(mo)) {
                out << "#";
            } else {
                out << "+";
            }
            out << get_name(get_type(mo)) << " ";
            out << get_name(mo) << "(";
            for_each(get_parameters(mo), [&](auto mp) {
                if(!info.is_first()) {
                    out << ", ";
                }
                out << get_name(mp) << ": ";
                out << get_name(get_type(mp));
            });
            out << ")\n";
        });
        out << "  __\n";
        for_each(get_data_members(mt), [&](auto mo) {
            out << "  ";
            if(is_private(mo)) {
                out << "-";
            } else if(is_protected(mo)) {
                out << "#";
            } else {
                out << "+";
            }
            out << get_name(mo) << ": ";
            out << get_name(get_type(mo)) << "\n";
        });
    }
    out << "}\n";
}

template <typename T, typename MS>
std::string_view do_get_related_type_name(std::type_identity<T>, MS ms) {
    const auto mt = get_aliased(mirror(T));
    if constexpr(reflects_scope_member(mt)) {
        if constexpr(reflects_same(get_scope(mt), ms)) {
            return get_name(mt);
        }
    }
    return {};
}

template <typename T, typename MS>
std::string_view do_get_related_type_name(std::type_identity<T*>, MS ms) {
    return do_get_related_type_name(std::type_identity<T>{}, ms);
}

template <typename T, typename MS>
std::string_view do_get_related_type_name(std::type_identity<T&>, MS ms) {
    return do_get_related_type_name(std::type_identity<T>{}, ms);
}

template <typename T, typename MS>
std::string_view
do_get_related_type_name(std::type_identity<std::vector<T>>, MS ms) {
    return do_get_related_type_name(std::type_identity<T>{}, ms);
}

template <typename MT, typename MS>
std::string_view get_related_type_name(MT mt, MS ms) {
    return do_get_related_type_name(get_reflected_type(mt), ms);
}

template <typename MT>
void print_type_rel_puml(std::ostream& out, MT mt) {
    if constexpr(reflects_record(mt)) {
        for_each(get_member_functions(mt), [&](auto mf) {
            auto rel_name = get_related_type_name(get_type(mf), get_scope(mt));
            if(!rel_name.empty()) {
                out << get_name(mt) << " --> " << rel_name << "\n";
            }
            for_each(get_parameters(mf), [&](auto mp) {
                rel_name = get_related_type_name(get_type(mp), get_scope(mt));
                if(!rel_name.empty()) {
                    out << get_name(mt) << " --> " << rel_name << "\n";
                }
            });
        });
    }
    if constexpr(reflects_class(mt)) {
        for_each(get_base_classes(mt), [&](auto mb) {
            out << get_name(get_class(mb)) << " <|- " << get_name(mt) << "\n";
        });
    }
}

template <typename... T>
std::ostream& print_puml(std::ostream& out) {
    out << "@startuml\n";
    (..., print_type_puml(out, get_aliased(mirror(T))));
    out << "\n";
    (..., print_type_rel_puml(out, get_aliased(mirror(T))));
    out << "@enduml\n";
    return out;
}
//------------------------------------------------------------------------------
namespace myexample {

enum class weekday : int {
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

class calendar;

class person {
public:
    const std::string& get_name() const {
        return _name;
    }

    const std::string& get_email() const {
        return _email;
    }

    void set_calendar(calendar& c) {
        _main_calendar = &c;
    }

private:
    std::string _name;
    std::string _email;
    calendar* _main_calendar{nullptr};
};

class manager : public person {
public:
    calendar& add_calendar() {
        _owned_calendars.emplace_back();
        return _owned_calendars.back();
    }

private:
    std::vector<calendar> _owned_calendars;
};

class event {
public:
    void set_year(int year) {
        _year = year;
    }

    void set_date(int week, weekday day) {
        _week = week;
        _day = day;
    }

    void set_time(int hour, int minute) {
        _hour = hour;
        _minute = minute;
    }

    void set_duration(int minutes) {
        _duration_minutes = minutes;
    }

    void add_attendee(person who) {
        _attendees.emplace_back(std::move(who));
    }

private:
    int _year;
    int _week;
    weekday _day;
    int _hour;
    int _minute;
    int _duration_minutes;

    std::vector<person> _attendees;
};

class calendar {
public:
    size_t event_count() const {
        return _events.size();
    }

private:
    std::vector<event> _events;
};
} // namespace myexample
//------------------------------------------------------------------------------
int main() {
    using namespace myexample;
    print_puml<weekday, person, manager, event, calendar>(std::cout);
    return 0;
}
