#include "File.hpp"

#include <cassert>
#include <cstdlib>

long countFileSize(std::FILE *file)
{
    std::fseek(file, 0, SEEK_END);
    long fileSize = std::ftell(file);
    rewind(file);

    return fileSize;
}

char *readFileToBuffer(const char *fileName, bool binaryMode)
{
    std::FILE *file = std::fopen(fileName, binaryMode ? "b" : "r");

    long fileSize = countFileSize(file);
    auto buffer = (char *) std::calloc(fileSize + !binaryMode, sizeof(char));
    std::fread(buffer, sizeof(char), fileSize, file);

    if (!binaryMode) buffer[fileSize] = '\0';

    std::fclose(file);

    return buffer;
}
