#ifndef FILE_HPP
#define FILE_HPP

#include <cstdio>

long countFileSize(std::FILE *file);
[[nodiscard]] char *readFileToBuffer(const char *fileName, bool binaryMode);

#endif /* FILE_HPP */
