#include "chara.hpp"
#include "lex.hpp"
#include "parser.hpp"
#include "room.hpp"
#include "state.hpp"
#include "state_mgr.hpp"

#include <fmt/format.h>

#include <iostream>
#include <vector>

int main() {
	using namespace wot;

	state_mgr state_mgr;
	{
		state first_state;

		room main_room{id<room>::make(), "a small jail cell", {}};
		first_state.rooms.insert({main_room.id, main_room});

		chara main_chara{id<chara>::make(), 0, main_room.id};
		first_state.charas.insert({main_chara.id, main_chara});
		first_state.main_chara = main_chara.id;

		state_mgr.states.push_back(first_state);
	}

	fmt::print("~ The Wand of Time ~\n");
	parser{{token{"look"}}, state_mgr}.parse();

	for (;;) {
		fmt::print("\n> ");
		std::string line;
		std::getline(std::cin, line);
		parser{lex(line), state_mgr}.parse();
	}

	return 0;
}
