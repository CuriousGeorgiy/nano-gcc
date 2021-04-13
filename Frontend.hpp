#ifndef FRONTEND_HPP
#define FRONTEND_HPP

#include "ProgramLanguageAnalyser.hpp"

class Frontend {
public:
    Frontend();
    void FrontendDtor();

    void translate(const char *programLanguageInputFileName, const char *translationOutputFileName);

private:
    ProgramLanguageAnalyser analyser;
};

#endif /* FRONTEND_HPP */
