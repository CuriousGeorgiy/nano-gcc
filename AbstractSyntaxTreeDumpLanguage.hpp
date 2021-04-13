#ifndef ABSTRACTSYNTAXTREEDUMPLANGUAGE_HPP
#define ABSTRACTSYNTAXTREEDUMPLANGUAGE_HPP

namespace AbstractSyntaxTreeDumpLanguage {
    enum class Keyword {
        Nil,
        FunctionDeclaration,
        FunctionImplementationParameter,
        Concatenation,
        If,
        While,
        FunctionCallParameter,
        Return
    };

    extern const char *Keywords[8];
    extern char Symbols[13];

    struct Lexem {
        enum class Type {
            Keyword,
            Identifier,
            Symbol,
            Number,
        } type;

        union {
            Keyword keyword;
            char *identifier;
            char symbol;
            double number;
        } data;
    };
}

#endif /* ABSTRACTSYNTAXTREEDUMPLANGUAGE_HPP */
