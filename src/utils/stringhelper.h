#ifndef SWAY_UTILS_STRINGHELPER_H
#define SWAY_UTILS_STRINGHELPER_H

#include "../defines.h"
#include "../types.h"

#include <cstring> // std::strcmp
#include <sstream> // std::ostringstream
#include <vector> // std::vector
#include <cstdarg> // va_start, va_end, std::va_list
#include <cstddef> // std::size_t
#include <stdexcept> // std::runtime_error

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(utils)

class StringHelper {
public:
	static bool empty(lpcstr str) {
		return NOT str OR NOT str[0];
	}

	static std::string format(lpcstr const format, ...) {
		auto temp = std::vector<char>();
		auto length = std::size_t(63);
		std::va_list args;
		while (temp.size() <= length) {
			temp.resize(length + 1);
			va_start(args, format);
			const auto status = std::vsnprintf(temp.data(), temp.size(), format, args);
			va_end(args);

			if (status < 0)
				throw std::runtime_error("String formatting error.");

			length = static_cast<std::size_t>(status);
		}

		return std::string(temp.data(), length);
	}
	
	static bool compare(lpcstr const s1, lpcstr const s2) {
		return (std::strcmp(s1, s2) == 0);
	}

	static std::string concat(lpcstr s1, lpcstr s2) {
		std::ostringstream stream;
		stream << s1 << s2;
		return stream.str();
	}

	static void replace(std::string &subject, const std::string &search, const std::string &replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}

	static std::vector<std::string> split(std::string input, const std::string &delimiter) {
		std::vector<std::string> parts;
	
		while (input.find_first_of(delimiter) < input.length()) {
			parts.push_back(input.substr(0, input.find_first_of(delimiter)));
			input = input.substr(input.find_first_of(delimiter) + 1, input.length());
		}

		parts.push_back(input);
		return parts;
	}
};

NAMESPACE_END(utils)
NAMESPACE_END(sway)

#endif // SWAY_UTILS_STRINGHELPER_H