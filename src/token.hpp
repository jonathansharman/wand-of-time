#pragma once

#include <regex>
#include <string>

namespace wot {
	enum class lexeme { //
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
		wait,
		take,
		pick,
		use,
		give,
		put,
		// Prepositions
		at,
		to,
		from,
		with,
		on,
		onto,
		off,
		in,
		into,
		out,
		around,
		// Nouns
		you,
		self,
		wand
	};

	struct token {
		lexeme lex;
		std::string_view text = "";

		token(std::string_view text) : lex{classify(text)}, text{text} {}

		static lexeme classify(std::string_view text) {
			static std::vector<std::tuple<std::regex, lexeme>> map = {//
				// Directions
				{std::regex{"n|north"}, lexeme::north},
				{std::regex{"s|south"}, lexeme::south},
				{std::regex{"e|east"}, lexeme::east},
				{std::regex{"w|west"}, lexeme::west},
				{std::regex{"u|up"}, lexeme::up},
				{std::regex{"d|down"}, lexeme::down},
				// Verbs
				{std::regex{"l|look|view|inspect|observe|check"}, lexeme::look},
				{std::regex{"go|exit"}, lexeme::go},
				{std::regex{"wait"}, lexeme::wait},
				{std::regex{"take|get"}, lexeme::take},
				{std::regex{"pick"}, lexeme::pick},
				{std::regex{"use"}, lexeme::use},
				{std::regex{"give"}, lexeme::give},
				{std::regex{"put|place"}, lexeme::put},
				// Prepositions
				{std::regex{"at"}, lexeme::at},
				{std::regex{"to"}, lexeme::to},
				{std::regex{"from"}, lexeme::from},
				{std::regex{"with"}, lexeme::with},
				{std::regex{"on"}, lexeme::on},
				{std::regex{"onto"}, lexeme::onto},
				{std::regex{"off"}, lexeme::off},
				{std::regex{"in"}, lexeme::in},
				{std::regex{"into"}, lexeme::into},
				{std::regex{"out"}, lexeme::out},
				{std::regex{"around"}, lexeme::around},
				// Nouns
				{std::regex{"you|yourself"}, lexeme::you},
				{std::regex{"me|myself|self"}, lexeme::self},
				{std::regex{"wand"}, lexeme::wand}};

			for (auto const& [regex, lexeme] : map) {
				if (std::regex_match(text.begin(), text.end(), regex)) { return lexeme; }
			}

			return lexeme::unknown;
		}
	};
}
