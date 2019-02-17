#pragma once

#include "parser.hpp"

#include "chara.hpp"
#include "room.hpp"

#include <fmt/format.h>

namespace wot {
	token parser::read() {
		return *(it++);
	}

	token parser::peek() {
		return *it;
	}

	void parser::parse() {
		token next = read();

		if (next.lexeme == lexeme::eol) return;

		switch (next.lexeme) {
			case lexeme::look:
				look();
				break;
			case lexeme::go:
				go();
				break;
			case lexeme::take:
				take();
				break;
			case lexeme::pick:
				pick();
				break;
			case lexeme::use:
				use();
				break;
			case lexeme::give:
				give();
				break;
			case lexeme::put:
				give();
				break;
			case lexeme::unknown:
				unknown_command();
				break;
			default:
				unknown_command();
				break;
		}
	}

	void parser::unknown_command() {
		fmt::print("I don't understand that.\n");
	}

	void parser::look() {
		fmt::print("You see {}.\n", state_mgr.cur().room().desc);
	}

	void parser::go() {}

	void parser::take() {}

	void parser::pick() {}

	void parser::use() {}

	void parser::give() {}

	void parser::put() {}
}
