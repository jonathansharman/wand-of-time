#pragma once

#include "id.hpp"

namespace wot {
	struct room;

	struct chara {
		id<chara> id;
		int time;
		wot::id<room> loc;
	};
}
