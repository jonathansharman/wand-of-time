#pragma once

#include "id.hpp"

#include <string>

namespace wot {
	struct room;

	struct item {
		id<item> item_id;
		std::string name;
		std::string desc;
	};
}
