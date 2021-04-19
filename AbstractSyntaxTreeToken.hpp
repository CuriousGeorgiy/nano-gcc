#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Language.hpp"

struct Token {
    enum class Type {
        Keyword,
        Identifier,
        Number,
        Symbol,
    } type;

    union {
        Keyword keyword;
        char *identifier;
        double number;
        char symbol;
    } data;
};

#endif /* TOKEN_HPP */
