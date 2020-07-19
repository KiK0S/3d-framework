#pragma once
#include <iostream>
#include <string>

namespace logger {
	void debug(const std::string& s) {
		std::cerr << s << std::endl;
	}
};