#include "SyntaxError.hpp"

SyntaxError::SyntaxError(const char *fileName, int lineNo, const char *functionName, const char *comment)
: std::runtime_error(comment), fileName(fileName), lineNo(lineNo), functionName(functionName)
{
    size_t explanationLength = std::snprintf(nullptr, 0, "%s(%d):\n"
                                                         "%s: syntax error: %s\n", fileName, lineNo, functionName,
                                             std::runtime_error::what());
    explanation = (char *) std::calloc(explanationLength + 1, sizeof(char));
    std::snprintf(explanation, explanationLength, "%s(%d):\n"
                                                  "%s: syntax error: %s\n", fileName, lineNo, functionName,
                  std::runtime_error::what());
}

const char *SyntaxError::what() const
{
    return explanation;
}

void SyntaxError::SyntaxErrorDtor()
{
    std::free(explanation);
    explanation = nullptr;
}
