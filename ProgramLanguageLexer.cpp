#include "ProgramLanguageLexer.hpp"

#include "ProgramLanguage.hpp"
#include "SyntaxError.hpp"

#include <cctype>
#include <cstring>

ProgramLanguageLexer::ProgramLanguageLexer()
: textBufferReader(nullptr), lexemList(nullptr)
{
}

void ProgramLanguageLexer::tokenizeText(const char *textBuffer, Stack<ProgramLanguage::Lexem> *newLexemList)
{
    textBufferReader = textBuffer;
    lexemList = newLexemList;

    skipWhitespaces();

    while (*textBufferReader) {
        if (lookForKeyword() || lookForSymbol()) {
        } else if (std::isdigit(*textBufferReader)) {
            addNumberLexem();
        } else if (std::isalpha(*textBufferReader) || (*textBufferReader == '_')) {
            addIdentifierLexem();
        } else {
            throw SyntaxError(__FILE__, __LINE__, __func__, "illegal symbol found");
        }

        skipWhitespaces();
    }
}

void ProgramLanguageLexer::skipWhitespaces()
{
    while (std::isspace(*textBufferReader)) ++textBufferReader;
}

bool ProgramLanguageLexer::lookForKeyword()
{
    bool foundKeyword = false;
    for (size_t i = 0; i < sizeof(ProgramLanguage::Keywords) / sizeof(ProgramLanguage::Keywords[0]); ++i) {
        if (std::strstr(textBufferReader, ProgramLanguage::Keywords[i]) == textBufferReader) {
            foundKeyword = true;
            addKeywordLexem((ProgramLanguage::Keyword) i, std::strlen(ProgramLanguage::Keywords[i]));
            continue;
        }
    }

    return foundKeyword;
}

bool ProgramLanguageLexer::lookForSymbol()
{
    bool foundSymbol = false;
    for (auto &symbol: ProgramLanguage::Symbols) {
        if (*textBufferReader == symbol) {
            foundSymbol = true;
            addSymbolLexem(symbol);
            continue;
        }
    }

    return foundSymbol;
}

void ProgramLanguageLexer::addKeywordLexem(ProgramLanguage::Keyword keyword, size_t keywordLength)
{
    ProgramLanguage::Lexem lexem{.type = ProgramLanguage::Lexem::Type::Keyword, .data{.keyword = keyword}};
    lexemList->push(lexem);

    textBufferReader += keywordLength;
}

void ProgramLanguageLexer::addIdentifierLexem()
{
    const char *identifierReader = textBufferReader;
    while (std::isalpha(*identifierReader) || std::isdigit(*identifierReader) || (*identifierReader == '_')) ++identifierReader;
    ptrdiff_t identifierLength = identifierReader - textBufferReader;

    ProgramLanguage::Lexem lexem{.type = ProgramLanguage::Lexem::Type::Identifier,
                                 .data{.identifier = (char *) std::calloc(identifierLength + 1, sizeof(char))}};
    std::strncpy(lexem.data.identifier, textBufferReader, identifierLength);
    lexem.data.identifier[identifierLength] = '\0';
    lexemList->push(lexem);

    textBufferReader = identifierReader;
}

void ProgramLanguageLexer::addNumberLexem()
{
    double number = 0;
    while (std::isdigit(*textBufferReader)) {
        number = number * 10 + (*textBufferReader++ - '0');
    }

    ProgramLanguage::Lexem lexem{.type = ProgramLanguage::Lexem::Type::Number, .data{.number = number}};
    lexemList->push(lexem);
}

void ProgramLanguageLexer::addSymbolLexem(char symbol)
{
    ProgramLanguage::Lexem lexem{.type = ProgramLanguage::Lexem::Type::Symbol, .data{.symbol = symbol}};
    lexemList->push(lexem);

    ++textBufferReader;
}
