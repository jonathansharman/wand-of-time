#include "chara.hpp"
#include "item.hpp"
#include "lexer.hpp"
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
		room main_room{
			id<room>::make(), "your jail cell", "It's a cold, cramped stone cell secured with sturdy iron bars.", {}};

		state first_state;
		{
			chara main_chara{id<chara>::make(), "you", "You're wearing prisoner's rags.", 0};
			first_state.main_chara_id = main_chara.chara_id;
			main_room.charas.push_back(main_chara);
			main_room.charas.push_back(main_chara);

			item wand_of_time{id<item>::make(),
				"a small wand",
				"It's composed of two intertwined pieces of wood, capped with polished brass at both ends."};
			main_room.items.push_back(wand_of_time);
			main_room.items.push_back(wand_of_time);
			main_room.exits.insert({dir::north, main_room.room_id});

			first_state.rooms.push_back(main_room);

			state_mgr.advance(first_state);
		}

		fmt::print("~ The Wand of Time ~\n\n");
		parser{{lex("look")}, state_mgr}.parse();

		for (;;) {
			fmt::print("> ");
			std::string line;
			std::getline(std::cin, line);
			fmt::print("\n");
			parser{lex(line), state_mgr}.parse();
		}
	}

	return 0;
}
