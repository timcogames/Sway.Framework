#ifndef SWAY_UTILS_STRINGCONVERTER_H
#define SWAY_UTILS_STRINGCONVERTER_H

#include "../defines.h"
#include "../types.h"

#include <string> // std::string
#include <algorithm> // std::transform

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(utils)

class StringConverter {
public:
	static std::string toLower(const std::string &str) {
		std::string buffer(str);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
		return buffer;
	}
	
	static std::string toUpper(const std::string &str) {
		std::string buffer(str);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);
		return buffer;
	}
};

NAMESPACE_END(utils)
NAMESPACE_END(sway)

#endif // SWAY_UTILS_STRINGCONVERTER_H