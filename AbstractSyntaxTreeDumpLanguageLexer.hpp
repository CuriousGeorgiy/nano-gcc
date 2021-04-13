#ifndef ABSTRACTSYNTAXTREEDUMPLANGUAGELEXER_HPP
#define ABSTRACTSYNTAXTREEDUMPLANGUAGELEXER_HPP

#include "Stack.hpp"
#include "AbstractSyntaxTreeDumpLanguage.hpp"

#include <cstdio>

class AbstractSyntaxTreeDumpLanguageLexer {
public:
    AbstractSyntaxTreeDumpLanguageLexer();

    void tokenizeText(const char *textBuffer, Stack<AbstractSyntaxTreeDumpLanguage::Lexem> *newLexemList);

private:
    const char *textBufferReader;
    Stack<AbstractSyntaxTreeDumpLanguage::Lexem> *lexemList;

    void skipWhitespaces();

    bool lookForKeyword();
    bool lookForSymbol();

    void addKeywordLexem(AbstractSyntaxTreeDumpLanguage::Keyword keyword, size_t keywordLength);
    void addIdentifierLexem();
    void addNumberLexem();
    void addSymbolLexem(char symbol);
};

#endif /* ABSTRACTSYNTAXTREEDUMPLANGUAGELEXER_HPP */
