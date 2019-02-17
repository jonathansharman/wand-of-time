#pragma once

#include "state.hpp"

#include <vector>

namespace wot {
	struct state_mgr {
		//! The current state.
		state const& cur() const {
			return *_cur;
		}

		void add(state new_state) {
			_states.push_back(std::move(new_state));
		}

		void forward() {
			_cur = _states.end();
		}

	private:
		std::vector<state> _states;

		std::vector<state>::iterator _cur;
	};
}
