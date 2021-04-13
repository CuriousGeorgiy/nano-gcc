#include "AbstractSyntaxTreeDumpLanguage.hpp"

const char *AbstractSyntaxTreeDumpLanguage::Keywords[] = {"nil", "function-declaration", "function-implementation-parameter", "concatenation", "if", "while",
                          "function-call-parameter", "return"};
char AbstractSyntaxTreeDumpLanguage::Symbols[] = {'$', '{', '}', '+', '-', '*', '/', '^', '&', '|', '<', '=', '>'};

