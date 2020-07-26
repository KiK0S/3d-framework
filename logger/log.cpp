#pragma once
#include <iostream>
#include <string>

namespace logger {
	const bool DEBUG = false;

	void debug(const std::string& s) {
		if (!DEBUG) {
			return;
		}
		std::cerr << s << std::endl;
	}
};