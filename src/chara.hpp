#pragma once

#include "id.hpp"

#include <string>

namespace wot {
	struct room;

	struct chara {
		id<chara> chara_id;
		std::string name;
		std::string desc;
		int time;

		constexpr bool operator==(chara const& other) {
			return chara_id == other.chara_id && time == other.time;
		}

		constexpr bool operator!=(chara const& other) {
			return chara_id != other.chara_id || time != other.time;
		}
	};
}
