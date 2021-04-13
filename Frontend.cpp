#include "Frontend.hpp"

#include "File.hpp"

Frontend::Frontend()
: analyser()
{
}

void Frontend::FrontendDtor()
{
    analyser.ProgramLanguageAnalyserDtor();
}

void Frontend::translate(const char *programLanguageInputFileName, const char *translationOutputFileName)
{
    char *buffer = readFileToBuffer(programLanguageInputFileName, false);

    analyser.analyseText(buffer);
    std::free(buffer);
    buffer = nullptr;

    analyser.abstractSyntaxTree.dumpToText(translationOutputFileName);
}
