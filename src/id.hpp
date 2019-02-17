#pragma once

namespace wot {
	template <typename T>
	struct id {
		static id make() {
			static int next_value = 0;
			return id{next_value++};
		}

		int value;

		constexpr bool operator==(id other) const {
			return value == other.value;
		}
		constexpr bool operator!=(id other) const {
			return value != other.value;
		}
		constexpr bool operator<(id other) const {
			return value < other.value;
		}
		constexpr bool operator<=(id other) const {
			return value <= other.value;
		}
		constexpr bool operator>(id other) const {
			return value > other.value;
		}
		constexpr bool operator>=(id other) const {
			return value >= other.value;
		}
	};
}
