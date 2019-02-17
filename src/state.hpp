#pragma once

#include "id.hpp"

#include <map>

namespace wot {
	struct chara;
	struct room;

	struct state {
		std::map<id<room>, room> rooms;
		std::map<id<chara>, chara> charas;

		id<chara> main_chara_id;

		chara main_chara() const {
			return charas.at(main_chara_id);
		}

		room room() const {
			return rooms.at(main_chara().loc);
		}
	};
}
