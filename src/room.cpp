#include "room.hpp"

#include "chara.hpp"
#include "item.hpp"

#include <algorithm>

namespace wot {
	std::optional<id<room>> room::room_towards(dir direction) {
		auto it = exits.find(direction);
		return it == exits.end() ? std::nullopt : std::make_optional(it->second);
	}

	chara* room::find(id<chara> chara_id) {
		auto it = std::find_if(
			charas.begin(), charas.end(), [chara_id](chara const& chara) { return chara.chara_id == chara_id; });
		return it != charas.end() ? &*it : nullptr;
	}

	item* room::find(id<item> item_id) {
		auto it = std::find_if(
			items.begin(), items.end(), [item_id](item const& item) { return item.item_id == item_id; });
		return it != items.end() ? &*it : nullptr;
	}

	void room::move(chara& mover, room& room) {
		// Do nothing if moving into this room.
		if (room.room_id == room_id) return;

		// Find the character.
		auto it = std::find(charas.begin(), charas.end(), mover);
		if (it != charas.end()) {
			room.charas.push_back(*it);
			charas.erase(it);
		}
	}
}
