#ifndef PROGRAMLANGUAGELEXER_HPP
#define PROGRAMLANGUAGELEXER_HPP

#include "Stack.hpp"
#include "ProgramLanguage.hpp"

#include <cstdio>

class ProgramLanguageLexer {
public:
    ProgramLanguageLexer();

    void tokenizeText(const char *textBuffer, Stack<ProgramLanguage::Lexem> *newLexemList);

private:
    const char *textBufferReader;
    Stack<ProgramLanguage::Lexem> *lexemList;

    void skipWhitespaces();

    bool lookForKeyword();
    bool lookForSymbol();

    void addKeywordLexem(ProgramLanguage::Keyword keyword, size_t keywordLength);
    void addIdentifierLexem();
    void addNumberLexem();
    void addSymbolLexem(char symbol);
};

#endif /* PROGRAMLANGUAGELEXER_HPP */
