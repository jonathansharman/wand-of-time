#pragma once

#include "chara.hpp"
#include "id.hpp"
#include "room.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace wot {
	struct state {
		std::vector<room> rooms;

		id<chara> main_chara_id;

		chara* find_mc() {
			for (auto& r : rooms) {
				for (auto& c : r.charas) {
					if (c.chara_id == main_chara_id) { return &c; }
				}
			}
			return nullptr;
		}

		room* find_mr() {
			for (auto& r : rooms) {
				for (auto& c : r.charas) {
					if (c.chara_id == main_chara_id) { return &r; }
				}
			}
			return nullptr;
		}

		chara* find(id<chara> id) {
			for (auto& room : rooms) {
				if (auto c = room.find(id)) { return c; }
			}
			return nullptr;
		}

		room* find(id<room> room_id) {
			auto it = std::find_if(
				rooms.begin(), rooms.end(), [room_id](room const& room) { return room.room_id == room_id; });
			return it != rooms.end() ? &*it : nullptr;
		}
	};
}
