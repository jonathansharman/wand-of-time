#pragma once

#include "id.hpp"

#include <string>
#include <vector>

namespace wot {
	enum class dir { up, down, north, south, east, west };

	struct room;

	struct exit {
		dir dir;
		id<room> to;
	};

	struct room {
		id<room> id;
		std::string desc;
		std::vector<exit> exits;
	};
}
