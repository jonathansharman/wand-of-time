#include "parser.hpp"

#include "chara.hpp"
#include "item.hpp"
#include "room.hpp"

#include <fmt/format.h>
#include <range/v3/all.hpp>

namespace wot {
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

	std::optional<dir> to_dir(lexeme lex) {
		switch (lex) {
			case lexeme::north:
				return dir::north;
			case lexeme::south:
				return dir::south;
			case lexeme::east:
				return dir::east;
			case lexeme::west:
				return dir::west;
			case lexeme::up:
				return dir::up;
			case lexeme::down:
				return dir::down;
			default:
				return std::nullopt;
		}
	}

	void parser::go(dir direction) {
		if (auto target_room = state_mgr.cur().find_mr()->room_towards(direction)) {
			state new_state = state_mgr.cur();
			new_state.find_mr()->move(*new_state.find_mc(), *new_state.find(*target_room));
			state_mgr.advance(new_state);
			look_around();
		} else {
			if (rand() % 2) {
				fmt::print("There's no exit in that direction.");
			} else {
				fmt::print("There's no way over there.");
			}
		}
	}

	void parser::parse() {
		static auto is_any = [](lexeme) { return true; };
		static auto is_dir = [](lexeme lex) {
			switch (lex) {
				case lexeme::north:
					return true;
				case lexeme::south:
					return true;
				case lexeme::east:
					return true;
				case lexeme::west:
					return true;
				case lexeme::up:
					return true;
				case lexeme::down:
					return true;
				default:
					return false;
			}
		};
		static auto is_item = [](lexeme lex) {
			switch (lex) {
				case lexeme::wand:
					return true;
				default:
					return false;
			}
		};
		static auto is_chara = [](lexeme lex) {
			switch (lex) {
				case lexeme::self:
					return true;
				case lexeme::you:
					return true;
				default:
					return false;
			}
		};

		if (match({})) {
			// [empty line]
			fmt::print("What are you going to do?");
		} else if (match({is_dir})) {
			// [direction]
			go(*to_dir(tokens.front().lex));
		} else if (match({lexeme::go})) {
			// go
			fmt::print("Go where?");
		} else if (match({lexeme::go, is_dir})) {
			// go [direction]
			go(*to_dir(tokens[1].lex));
		} else if (match({lexeme::look}) || match({lexeme::look, lexeme::around})) {
			// look; look around
			look_around();
		} else if (match({lexeme::look, is_dir})) {
			// look [direction]
			dir direction = *to_dir(tokens[1].lex);
			if (auto target_room = state_mgr.cur().find_mr()->room_towards(direction)) {
				fmt::print("Looking {}, you see {}.", name(direction), state_mgr.cur().find(*target_room)->name);
			} else {
				fmt::print("There's nothing in that direction.");
			}
		} else if (match({lexeme::look, lexeme::at})) {
			// look at
			fmt::print("Look at what?");
		} else if (match({lexeme::look, is_item})) {
			// look [item]
			fmt::print("\"Look at\" not implemented.");
		} else if (match({lexeme::look, is_chara})) {
			// look [chara]
			fmt::print("\"Look at\" not implemented.");
		} else if (match({lexeme::look, lexeme::at, is_chara})) {
			// look at [chara]
			fmt::print("\"Look at\" not implemented.");
		} else if (match({lexeme::look, is_any})) {
			// look [anything]
			fmt::print("You don't see that anywhere.");
		} else if (match({lexeme::look, lexeme::at, is_item})) {
			// look at [item]
			fmt::print("\"Look at\" not implemented.");
		} else if (match({lexeme::look, lexeme::at, is_any})) {
			// look at [anything]
			fmt::print("You don't see that anywhere.");
		} else if (match({lexeme::wait})) {
			// wait
			fmt::print("You wait a moment.");
			state_mgr.advance(state_mgr.cur());
		} else if (match({lexeme::take})) {
			// take
			fmt::print("Take what?");
		} else if (match({lexeme::pick})) {
			// pick
			fmt::print("Pick what?");
		} else if (match({lexeme::pick, lexeme::up})) {
			// pick up
			fmt::print("Pick up what?");
		} else if (match({lexeme::use})) {
			// use
			fmt::print("Use what?");
		} else if (match({lexeme::give})) {
			// give
			fmt::print("Give what to whom?");
		} else if (match({lexeme::put})) {
			// put
			fmt::print("Put what where?");
		} else {
			switch (rand() % 4) {
				case 0:
					fmt::print("I don't understand what you mean.");
					break;
				case 1:
					fmt::print("Huh?");
					break;
				case 2:
					fmt::print("Pardon me?");
					break;
				case 3:
					fmt::print("Come again?");
					break;
			}
		}
	}

	void parser::look_around() {
		room* room = state_mgr.cur().find_mr();
		if (room == nullptr) { fmt::print("You aren't anywhere."); }
		// Look at the room in general.
		fmt::print("You're in {}. {}", room->name, room->desc);
		// Look at characters.
		if (!room->charas.empty()) {
			fmt::print("\n\nThe room is occupied by ");
			print_list(room->charas | ranges::view::transform([](chara const& c) { return c.name; }));
			fmt::print(".");
		}
		// Look at items.
		if (!room->items.empty()) {
			fmt::print("\n\nYou see ");
			print_list(room->items | ranges::view::transform([](item const& i) { return i.name; }));
			fmt::print(".");
		}
		// Show exits.
		if (!room->exits.empty()) {
			fmt::print("\n\nExits: ");
			std::vector<std::string> exit_descriptions;
			for (auto const& [direction, room_id] : room->exits) {
				exit_descriptions.push_back(name(direction) + " to " + state_mgr.cur().find(room_id)->name);
			}
			print_list(exit_descriptions);
			fmt::print(".");
		}
	}

	bool parser::match(std::vector<std::variant<lexeme, std::function<bool(lexeme)>>> const& preds) {
		if (preds.size() != tokens.size()) return false;
		for (std::size_t i = 0; i < preds.size(); ++i) {
			struct visitor {
				lexeme lex;
				bool operator()(lexeme lex2) {
					return lex == lex2;
				}
				bool operator()(std::function<bool(lexeme)> const& f) {
					return f(lex);
				}
			};
			if (!std::visit(visitor{tokens[i].lex}, preds[i])) { return false; }
		}
		return true;
	}
}
