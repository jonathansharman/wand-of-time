#pragma once

#include "token.hpp"

#include <regex>
#include <string>
#include <vector>

namespace wot {
	//! Lexes @p line into a list of tokens.
	std::vector<token> lex(std::string_view line) {
		std::vector<token> tokens;
		// Checks if a character is whitespace.
		auto space_pred = [](char const c) { return isspace(c); };
		// Find first non-whitespace character.
		auto word_begin = std::find_if_not(line.begin(), line.end(), space_pred);

		while (word_begin != line.end()) {
			// End of word is the next whitespace character or end of line.
			auto word_end = std::find_if(std::next(word_begin), line.end(), space_pred);
			// Add word to list.
			tokens.push_back(token{std::string_view{&*word_begin, std::size_t(std::distance(word_begin, word_end))}});
			// Start of the next word is the next non-whitespace character.
			word_begin = std::find_if_not(word_end, line.end(), space_pred);
		}

		return tokens;
	}
}
