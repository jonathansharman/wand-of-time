#pragma once

#include <regex>
#include <string>

namespace wot {
	enum class lexeme { //
		eol,
		unknown,
		// Directions
		north,
		south,
		east,
		west,
		up,
		down,
		// Verbs
		look,
		go,
		take,
		pick,
		use,
		give,
		put,
		// Prepositions
		to,
		from,
		on,
		onto,
		off,
		in,
		into,
		out
	};

	struct token {
		lexeme lexeme = lexeme::eol;
		std::string_view text = "";

		token() = default;
		token(std::string_view text) : lexeme{classify(text)}, text{text} {}

		static wot::lexeme classify(std::string_view text) {
			static std::vector<std::tuple<std::regex, wot::lexeme>> map = {//
				// Directions
				{std::regex{"n|north"}, lexeme::north},
				{std::regex{"s|south"}, lexeme::south},
				{std::regex{"e|east"}, lexeme::east},
				{std::regex{"w|west"}, lexeme::west},
				{std::regex{"u|up"}, lexeme::up},
				{std::regex{"d|down"}, lexeme::down},
				// Verbs
				{std::regex{"l|look|view|inspect|observe"}, lexeme::look},
				{std::regex{"go"}, lexeme::go},
				{std::regex{"take|get"}, lexeme::take},
				{std::regex{"pick"}, lexeme::pick},
				{std::regex{"use"}, lexeme::use},
				{std::regex{"give"}, lexeme::give},
				{std::regex{"put|place"}, lexeme::put},
				// Prepositions
				{std::regex{"to"}, lexeme::to},
				{std::regex{"from"}, lexeme::from},
				{std::regex{"on"}, lexeme::on},
				{std::regex{"onto"}, lexeme::onto},
				{std::regex{"off"}, lexeme::off},
				{std::regex{"in"}, lexeme::in},
				{std::regex{"into"}, lexeme::into},
				{std::regex{"out"}, lexeme::out}};

			for (auto const& [regex, lexeme] : map) {
				if (std::regex_match(text.begin(), text.end(), regex)) { return lexeme; }
			}

			return lexeme::unknown;
		}
	};
}
