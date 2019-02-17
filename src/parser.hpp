#pragma once

#include "state.hpp"
#include "state_mgr.hpp"
#include "token.hpp"

#include <string>

namespace wot {
	struct parser {
		parser(std::vector<token> const& tokens, state_mgr& state_mgr)
			: tokens{tokens}, state_mgr{state_mgr}, it{tokens.begin()} {}

		void parse();

	private:
		std::vector<token> const& tokens;
		state_mgr& state_mgr;

		std::vector<token>::const_iterator it;

		token read();
		token peek();

		void unknown_command();
		void look();
		void go();
		void take();
		void pick();
		void use();
		void give();
		void put();
	};
}
