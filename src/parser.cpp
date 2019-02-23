#pragma once

#include "parser.hpp"

#include "chara.hpp"
#include "item.hpp"
#include "room.hpp"

#include <fmt/format.h>
#include <range/v3/all.hpp>

namespace wot {
	token parser::read() {
		return *(it++);
	}

	token parser::peek() {
		return *it;
	}

	void parser::rewind() {
		--it;
	}

	std::string name(dir direction) {
		switch (direction) {
			case dir::north:
				return "North";
			case dir::south:
				return "South";
			case dir::east:
				return "East";
			case dir::west:
				return "West";
			case dir::up:
				return "up";
			case dir::down:
				return "down";
			default:
				return "unknown";
		}
	}

	template <typename Rng>
	void print_list(Rng&& list) {
		if (list.empty()) return;
		fmt::print(list.front());
		if (list.size() > 1) {
			for (std::size_t i = 1; i < list.size() - 1; ++i) {
				fmt::print(", {}", list[i]);
			}
			if (list.size() > 2) { fmt::print(","); }
			fmt::print(" and {}", list.back());
		}
	}

	void parser::parse() {
		token next = read();

		if (next.lex == lexeme::eol) {
			fmt::print("What are you going to do?\n");
			return;
		}

		switch (next.lex) {
			case lexeme::north:
				[[fallthrough]];
			case lexeme::south:
				[[fallthrough]];
			case lexeme::east:
				[[fallthrough]];
			case lexeme::west:
				[[fallthrough]];
			case lexeme::up:
				[[fallthrough]];
			case lexeme::down:
				rewind();
				go();
				break;
			case lexeme::look:
				look();
				break;
			case lexeme::go:
				go();
				break;
			case lexeme::wait:
				wait();
				break;
			case lexeme::take:
				take();
				break;
			case lexeme::pick:
				pick();
				break;
			case lexeme::use:
				use();
				break;
			case lexeme::give:
				give();
				break;
			case lexeme::put:
				give();
				break;
			case lexeme::unknown:
				[[fallthrough]];
			default:
				unknown_command();
				break;
		}
	}

	void parser::unknown_command() {
		switch (rand() % 4) {
			case 0:
				fmt::print("I don't understand what you mean.\n");
				break;
			case 1:
				fmt::print("Huh?\n");
				break;
			case 2:
				fmt::print("Pardon me?\n");
				break;
			case 3:
				fmt::print("Come again?\n");
				break;
		}
	}

	void parser::look() {
		room* room = state_mgr.cur().find_mr();
		if (room == nullptr) { fmt::print("You aren't anywhere.\n"); }

		switch (peek().lex) {
			case lexeme::around:
				[[fallthrough]];
			case lexeme::eol:
				// Look at the room in general.
				fmt::print("You're in {}. {}\n\n", room->name, room->desc);
				// Look at characters.
				if (!room->charas.empty()) {
					fmt::print("The room is occupied by ");
					print_list(room->charas | ranges::view::transform([](chara const& c) { return c.name; }));
					fmt::print(".\n\n");
				}
				// Look at items.
				if (!room->items.empty()) {
					fmt::print("You see ");
					print_list(room->items | ranges::view::transform([](item const& i) { return i.name; }));
					fmt::print(".\n\n");
				}
				// Show exits.
				if (!room->exits.empty()) {
					fmt::print("Exits: ");
					std::vector<std::string> exit_descriptions;
					for (auto const& [direction, room_id] : room->exits) {
						exit_descriptions.push_back(name(direction) + " to " + state_mgr.cur().find(room_id)->name);
					}
					print_list(exit_descriptions);
					fmt::print(".\n\n");
				}
				break;
			case lexeme::at:
				// "at" is optional.
				read();
				[[fallthrough]];
			default:
				fmt::print("You don't see that.\n");
				break;
		}
	}

	void parser::go() {
		dir direction;
		switch (read().lex) {
			case lexeme::north:
				direction = dir::north;
				break;
			case lexeme::south:
				direction = dir::south;
				break;
			case lexeme::east:
				direction = dir::east;
				break;
			case lexeme::west:
				direction = dir::west;
				break;
			case lexeme::up:
				direction = dir::up;
				break;
			case lexeme::down:
				direction = dir::down;
				break;
			case lexeme::eol:
				fmt::print("Go where?\n");
				return;
			default:
				unknown_command();
				return;
		}
		if (auto target_room = state_mgr.cur().find_mr()->room_towards(direction)) {
			state new_state = state_mgr.cur();
			new_state.find_mr()->move(*new_state.find_mc(), *new_state.find(*target_room));
			state_mgr.advance(new_state);
			look();
		} else {
			if (rand() % 2) {
				fmt::print("There's no exit in that direction.\n");
			} else {
				fmt::print("There's no way over there.\n");
			}
		}
	}

	void parser::wait() {
		fmt::print("You wait a moment.\n");
		state_mgr.advance(state_mgr.cur());
	}

	void parser::take() {}

	void parser::pick() {}

	void parser::use() {}

	void parser::give() {}

	void parser::put() {}
}
