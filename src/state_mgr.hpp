#pragma once

#include "state.hpp"

#include <vector>

namespace wot {
	struct state_mgr {
		//! The current state.
		state& cur() {
			return _states[_cur_index];
		}

		void advance(state new_state) {
			_states.push_back(std::move(new_state));
			forward();
		}

		void forward() {
			_cur_index = _states.size() - 1;
		}

	private:
		std::vector<state> _states;

		std::size_t _cur_index = 0;
	};
}
