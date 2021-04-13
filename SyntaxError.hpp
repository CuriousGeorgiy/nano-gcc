#ifndef SYNTAXERROR_HPP
#define SYNTAXERROR_HPP

#include <stdexcept>

class SyntaxError final: public std::runtime_error {
public:
    SyntaxError(const char *fileName, int lineNo, const char *functionName, const char *comment);
    void SyntaxErrorDtor();

    [[nodiscard]] const char *what() const final;
private:
    const char *fileName;
    int lineNo;
    const char *functionName;
    char *explanation;
};

#endif /* SYNTAXERROR_HPP */
