#include "log.h"
#include <iostream>


namespace logger {
	void debug(const std::string& s) {
		if (!DEBUG) {
			return;
		}
		std::cerr << s << std::endl;
	}
}