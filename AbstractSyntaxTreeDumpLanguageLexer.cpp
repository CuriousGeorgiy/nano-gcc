#include "AbstractSyntaxTreeDumpLanguageLexer.hpp"

#include "AbstractSyntaxTree.hpp"
#include "SyntaxError.hpp"

#include <cctype>
#include <cstring>

AbstractSyntaxTreeDumpLanguageLexer::AbstractSyntaxTreeDumpLanguageLexer()
: textBufferReader(nullptr), lexemList(nullptr)
{
}

void AbstractSyntaxTreeDumpLanguageLexer::tokenizeText(const char *textBuffer, Stack<AbstractSyntaxTreeDumpLanguage::Lexem> *newLexemList)
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

void AbstractSyntaxTreeDumpLanguageLexer::skipWhitespaces()
{
    while (std::isspace(*textBufferReader)) ++textBufferReader;
}

bool AbstractSyntaxTreeDumpLanguageLexer::lookForKeyword()
{
    bool foundKeyword = false;
    for (size_t i = 0; i < sizeof(AbstractSyntaxTreeDumpLanguage::Keywords) / sizeof(AbstractSyntaxTreeDumpLanguage::Keywords[i]); ++i) {
        if (std::strstr(textBufferReader, AbstractSyntaxTreeDumpLanguage::Keywords[i]) == textBufferReader) {
            foundKeyword = true;
            addKeywordLexem((AbstractSyntaxTreeDumpLanguage::Keyword) i, std::strlen(AbstractSyntaxTreeDumpLanguage::Keywords[i]));
            break;
        }
    }

    return foundKeyword;
}

bool AbstractSyntaxTreeDumpLanguageLexer::lookForSymbol()
{
    bool foundSymbol = false;
    for (auto &symbol: AbstractSyntaxTreeDumpLanguage::Symbols) {
        if (*textBufferReader == symbol) {
            foundSymbol = true;
            addSymbolLexem(symbol);
            continue;
        }
    }

    return foundSymbol;
}

void AbstractSyntaxTreeDumpLanguageLexer::addKeywordLexem(AbstractSyntaxTreeDumpLanguage::Keyword keyword, size_t keywordLength)
{
    AbstractSyntaxTreeDumpLanguage::Lexem lexem{.type = AbstractSyntaxTreeDumpLanguage::Lexem::Type::Keyword, .data{.keyword = keyword}};
    lexemList->push(lexem);

    textBufferReader += keywordLength;
}

void AbstractSyntaxTreeDumpLanguageLexer::addIdentifierLexem()
{
    const char *identifierReader = textBufferReader;
    while (std::isalpha(*identifierReader) || std::isdigit(*identifierReader) || (*identifierReader == '_')) ++identifierReader;
    ptrdiff_t identifierLength = identifierReader - textBufferReader;

    AbstractSyntaxTreeDumpLanguage::Lexem lexem{.type = AbstractSyntaxTreeDumpLanguage::Lexem::Type::Identifier,
    .data{.identifier = (char *) std::calloc(identifierLength + 1, sizeof(char))}};

    std::strncpy(lexem.data.identifier, textBufferReader, identifierLength);
    lexem.data.identifier[identifierLength] = '\0';
    lexemList->push(lexem);

    textBufferReader = identifierReader;
}

void AbstractSyntaxTreeDumpLanguageLexer::addNumberLexem()
{
    double number = 0;
    while (std::isdigit(*textBufferReader)) {
        number = number * 10 + (*textBufferReader++ - '0');
    }

    AbstractSyntaxTreeDumpLanguage::Lexem lexem{.type = AbstractSyntaxTreeDumpLanguage::Lexem::Type::Number, .data{.number = number}};
    lexemList->push(lexem);
}

void AbstractSyntaxTreeDumpLanguageLexer::addSymbolLexem(char symbol)
{
    AbstractSyntaxTreeDumpLanguage::Lexem lexem{.type = AbstractSyntaxTreeDumpLanguage::Lexem::Type::Symbol, .data{.symbol = symbol}};
    lexemList->push(lexem);

    ++textBufferReader;
}
