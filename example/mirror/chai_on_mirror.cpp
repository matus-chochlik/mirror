/// @example mirror/chai_on_mirror.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/chaiscript.hpp>
#include <mirror/sequence.hpp>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

class person;

class scene {
public:
    void person_says(const person& p, std::string_view line);
    void person_relocates(person& p, std::string_view how);
    void event_happens(std::string_view what);
    void pause();
};

class location {
private:
    std::string _name;
    scene& _scene;

public:
    location(std::string name, scene& s) noexcept
      : _name{std::move(name)}
      , _scene{s} {}

    auto name() const noexcept -> std::string_view {
        return _name;
    }

    auto scene() noexcept -> auto& {
        return _scene;
    }
};

class person {
private:
    std::string _name;
    location* _loc;

public:
    person(std::string name) noexcept
      : _name{std::move(name)} {}

    auto current_location() const noexcept -> auto& {
        assert(_loc);
        return *_loc;
    }

    auto enter(location& loc) noexcept {
        _loc = &loc;
        current_location().scene().person_relocates(*this, "enters");
    }

    auto is_thrown_to(location& loc) noexcept {
        _loc = &loc;
        current_location().scene().person_relocates(*this, "is thrown to");
    }

    auto name() const noexcept -> std::string_view {
        return _name;
    }

    void say(const std::string& line) {
        current_location().scene().person_says(*this, line);
    }
};

class mysterious_force {
private:
    location& _chasm;

public:
    mysterious_force(location& ch) noexcept
      : _chasm{ch} {}

    void throw_person_into_chasm(person& p) {
        p.is_thrown_to(_chasm);
    }
};

void scene::person_says(const person& p, std::string_view line) {
    std::cout << p.name() << ": " << '"' << line << '"' << std::endl;
}

void scene::person_relocates(person& p, std::string_view how) {
    std::cout << "[" << p.name() << " " << how << " "
              << p.current_location().name() << ".]" << std::endl;
}

void scene::pause() {
    std::cout << std::endl;
}

void scene::event_happens(std::string_view what) {
    std::cout << "[" << what << "]" << std::endl;
}

static scene at_the_bridge;

int main() {
    chaiscript::ChaiScript chai;

    mirror::add_to(
      chai,
      mirror::make_sequence(
        mirror(scene),
        mirror(mysterious_force),
        mirror(location),
        mirror(person),
        mirror(at_the_bridge)));

    chai(R"(
		var road = location("road leading to the bridge", at_the_bridge);
		var bridge = location("bridge of death", at_the_bridge);
		var chasm = location("chasm", at_the_bridge);

		var the_force = mysterious_force(chasm);

		var bridgekeeper = person("bridgekeeper");
		var king_arthur = person("king Arthur");
		var sir_lancelot = person("sir Lancelot");
		var sir_robin = person("sir Robin");
		var sir_galahad = person("sir Galahad");
		var sir_bedevere = person("sir Bedevere");

		bridgekeeper.enter(bridge);
		king_arthur.enter(road);
		sir_lancelot.enter(road);
		sir_robin.enter(road);
		sir_galahad.enter(road);
		sir_bedevere.enter(road);

		bridgekeeper.say("Stop. Who would cross the Bridge of Death must answer me these questions three, ere the other side he see.");
		sir_lancelot.say("Ask me the questions, bridgekeeper. I am not afraid.");
		bridgekeeper.say("What... is your name?");
		sir_lancelot.say("My name is Sir Lancelot of Camelot.");
		bridgekeeper.say("What... is your quest?");
		sir_lancelot.say("To seek the Holy Grail.");
		bridgekeeper.say("What... is your favourite colour?");
		sir_lancelot.say("Blue.");
		bridgekeeper.say("Go on. Off you go.");
		sir_lancelot.say("Oh, thank you. Thank you very much.");
		sir_lancelot.enter(bridge);

		sir_robin.say("That’s easy.");
		bridgekeeper.say("Stop. Who would cross the Bridge of Death must answer me these questions three, ere the other side he see.");
		sir_robin.say("Ask me the questions, bridgekeeper. I’m not afraid.");
		bridgekeeper.say("What... is your name?");
		sir_robin.say("My name is Sir Robin of Camelot.");
		bridgekeeper.say("What... is your quest?");
		sir_robin.say("To seek the Holy Grail.");
		bridgekeeper.say("What... is capital of Assyria?");
		sir_robin.say("I don’t know that.");
		the_force.throw_person_into_chasm(sir_robin);
		sir_robin.say("Auuuuuuuugh.");
		at_the_bridge.pause();

		bridgekeeper.say("Stop. What... is your name?");
		sir_galahad.say("Sir Galahad of Camelot.");
		bridgekeeper.say("What... is your quest?");
		sir_galahad.say("To seek the Holy Grail.");
		bridgekeeper.say("What... is your favourite colour?");
		sir_galahad.say("Blue. No. Yel...");
		the_force.throw_person_into_chasm(sir_robin);
		sir_galahad.say("Auuuuuuuugh.");
		at_the_bridge.pause();

		bridgekeeper.say("Hee hee heh. Stop. What... is your name?");
		king_arthur.say("It is ‘Arthur’, King of the Britons.");
		bridgekeeper.say("What... is your quest?");
		king_arthur.say("To seek the Holy Grail.");
		bridgekeeper.say("What... is the air-speed velocity of an unladen swallow?");
		king_arthur.say("What do you mean? An African or European swallow?");
		bridgekeeper.say("Huh? I... I don’t know that.");
		the_force.throw_person_into_chasm(bridgekeeper);
		bridgekeeper.say("Auuuuuuuugh.");
		at_the_bridge.pause();

		sir_bedevere.say("How do know so much about swallows?");
		king_arthur.say("Well, you have to know these things when you’re a king, you know.");
		king_arthur.enter(bridge);
		sir_bedevere.enter(bridge);
	)");

    return 0;
}
