#pragma once

#include "id.hpp"

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace wot {
	enum class dir { up, down, north, south, east, west };

	struct chara;
	struct item;

	struct room {
		id<room> room_id;
		std::string name;
		std::string desc;
		std::map<dir, wot::id<room>> exits;
		std::vector<chara> charas;
		std::vector<item> items;

		chara* find(id<chara> id);

		item* find(id<item> id);

		std::optional<id<room>> room_towards(dir direction);

		void move(chara& chara, room& room);
	};
}
