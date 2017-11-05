#ifndef SWAY_UTILS_FILE_H
#define SWAY_UTILS_FILE_H

#include "../defines.h"
#include "../types.h"

#include <string> // std::string
#include <fstream> // std::ifstream, std::ofstream

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(utils)

class File {
public:
	/*!
	 * \brief
	 *   Читает бинарный файл.
	 * 
	 * \param[in] filename
	 *   Имя файла.
	 */
	static std::string read(const std::string &filename) {
		std::ios::openmode flags = std::ios::in | std::ios::binary;
		std::ifstream fileStream(filename.c_str(), flags);
		if (NOT fileStream.is_open()) {
			printf("File %s not found\n", filename.c_str());
			return "";
		}

		std::string fileContent((std::istreambuf_iterator<s8>(fileStream)), std::istreambuf_iterator<s8>());
		fileStream.close();
	
		return fileContent;
	}
};

NAMESPACE_END(utils)
NAMESPACE_END(sway)

#endif // SWAY_UTILS_FILE_H