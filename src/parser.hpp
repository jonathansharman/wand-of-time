#pragma once

#include "state.hpp"
#include "state_mgr.hpp"
#include "token.hpp"

#include <functional>
#include <optional>
#include <string>
#include <variant>

namespace wot {
	struct parser {
		parser(std::vector<token> const& tokens, state_mgr& state_mgr) : tokens{tokens}, state_mgr{state_mgr} {}

		void parse();

	private:
		std::vector<token> const& tokens;
		state_mgr& state_mgr;

		void go(dir direction);

		void look_around();

		[[nodiscard]] bool match(std::vector<std::variant<lexeme, std::function<bool(lexeme)>>> const& preds);
	};
}
