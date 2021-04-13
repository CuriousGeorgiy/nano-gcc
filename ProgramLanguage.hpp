#ifndef PROGRAMLANGUAGE_HPP
#define PROGRAMLANGUAGE_HPP

namespace ProgramLanguage {
    enum class Keyword {
        Function,
        If,
        While,
        Return
    };

    extern const char *Keywords[4];
    extern const char Symbols[16];

    struct Lexem {
        enum class Type {
            Keyword,
            Identifier,
            Number,
            Symbol,
        } type;

        union {
            ProgramLanguage::Keyword keyword;
            char *identifier;
            double number;
            char symbol;
        } data;
    };
}

#endif /* PROGRAMLANGUAGE_HPP */
