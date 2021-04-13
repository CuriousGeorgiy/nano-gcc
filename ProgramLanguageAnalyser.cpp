#include "ProgramLanguageAnalyser.hpp"

#include "SyntaxError.hpp"

ProgramLanguageAnalyser::ProgramLanguageAnalyser()
: lexemList(), abstractSyntaxTree(), lexemListTraverser(nullptr)
{
}

void ProgramLanguageAnalyser::ProgramLanguageAnalyserDtor()
{
    for (size_t i = 0; i < lexemList.size; ++i) {
        if (lexemList.data[i].type == ProgramLanguage::Lexem::Type::Identifier) {
            std::free(lexemList.data[i].data.identifier);
            lexemList.data[i].data.identifier = nullptr;
        }
    }

    lexemList.StackDtor();
    abstractSyntaxTree.AbstractSyntaxTreeDtor();
}

void ProgramLanguageAnalyser::analyseText(const char *textBuffer)
{
    lexer.tokenizeText(textBuffer, &lexemList);

    lexemListTraverser = lexemList.data;
    abstractSyntaxTree.root = analyseProgram();
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseProgram()
{
    AbstractSyntaxTree::Node *node = nullptr;
    if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Keyword) &&
        (lexemListTraverser->data.keyword == ProgramLanguage::Keyword::Function)) {
        node = analyseFunctionDeclaration();
        return node;
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "at least the \"main\" function must be declared");
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseFunctionDeclaration()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::FunctionDeclaration;
        ++lexemListTraverser;

        node->left = analyseFunctionImplementation();
        node->right = analyseFunctionDeclarationList();

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseFunctionDeclarationList()
{
    if ((lexemListTraverser->type != ProgramLanguage::Lexem::Type::Keyword) ||
        (lexemListTraverser->data.keyword != ProgramLanguage::Keyword::Function)) {
        return nullptr;
    }

    AbstractSyntaxTree::Node *node = analyseFunctionDeclaration();

    return node;
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseFunctionImplementation()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        if (lexemListTraverser->type == ProgramLanguage::Lexem::Type::Identifier) {
            node->type = AbstractSyntaxTree::Node::Type::FunctionImplementation;
            node->data.identifier = lexemListTraverser->data.identifier;
            ++lexemListTraverser;

            requireSymbol('(');
            node->left = analyseFunctionImplementationParameterList();
            requireSymbol(')');

            node->right = analyseBlock();

            return node;
        } else {
            throw SyntaxError(__FILE__, __LINE__, __func__, "expected functionIdentifier");
        }
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseFunctionImplementationParameterList()
{
    if (lookForSymbol(')')) return nullptr;

    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::FunctionImplementationParameter;

    node->right = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->right->type = AbstractSyntaxTree::Node::Type::Variable;
    node->right->data.identifier = lexemListTraverser->data.identifier;
    ++lexemListTraverser;

    if (lookForSymbol(',')) {
        ++lexemListTraverser;

        node->left = analyseFunctionImplementationParameterList();
    }

    return node;
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseBlock()
{
    requireSymbol('{');
    if (lookForSymbol('}')) throw SyntaxError(__FILE__, __LINE__, __func__, "empty block body");

    AbstractSyntaxTree::Node *node = analyseStatement();

    try {
        node->right = analyseBlockBody();

        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }

}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseStatement()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::Concatenation;

    try {
        if (lexemListTraverser->type == ProgramLanguage::Lexem::Type::Keyword) {
            if (lexemListTraverser->data.keyword == ProgramLanguage::Keyword::If) {
                node->left = analyseIf();
            } else if (lexemListTraverser->data.keyword == ProgramLanguage::Keyword::While) {
                node->left = analyseWhile();
            } else if (lexemListTraverser->data.keyword == ProgramLanguage::Keyword::Return) {
                node->left = analyseReturnOperator();
            } else {
                throw SyntaxError(__FILE__, __LINE__, __func__, "function declaration inside function body");
            }
        } else {
            node->left = analyseOperator();
        }

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseBlockBody()
{
    if (lookForSymbol('}')) return nullptr;

    AbstractSyntaxTree::Node *node = analyseStatement();
    try {
        node->right = analyseBlockBody();

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseIf()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::If;
        ++lexemListTraverser;

        requireSymbol('(');
        node->left = analyseCondition();
        requireSymbol(')');

        node->right = analyseBlock();

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseWhile()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));

    try {
        node->type = AbstractSyntaxTree::Node::Type::While;
        ++lexemListTraverser;

        requireSymbol('(');
        node->left = analyseCondition();
        requireSymbol(')');

        node->right = analyseBlock();

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseCondition()
{

    return analyseExpression();
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseExpression()
{
    AbstractSyntaxTree::Node *node = analyseTertiaryExpression();
    if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Symbol) && ((lexemListTraverser->data.symbol == '+') ||
                                                                               (lexemListTraverser->data.symbol == '-') ||
                                                                               (lexemListTraverser->data.symbol == '<') ||
                                                                               (lexemListTraverser->data.symbol == '=') ||
                                                                               (lexemListTraverser->data.symbol == '>') ||
                                                                               (lexemListTraverser->data.symbol == '|'))) {
        auto operationNode = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
        operationNode->type = AbstractSyntaxTree::Node::Type::MathematicalOperator;
        operationNode->data.mathematicalOperator[0] = lexemListTraverser->data.symbol;

        try {
            if ((lexemListTraverser->data.symbol == '<') || (lexemListTraverser->data.symbol == '>')) {
                ++lexemListTraverser;

                if (lookForSymbol('=')) {
                    ++lexemListTraverser;

                    operationNode->data.mathematicalOperator[1] = '=';
                }
            } else if ((lexemListTraverser->data.symbol == '|') || (lexemListTraverser->data.symbol == '=')) {
                ++lexemListTraverser;

                requireSymbol(operationNode->data.mathematicalOperator[0]);
                operationNode->data.mathematicalOperator[1] = operationNode->data.mathematicalOperator[0];
            } else {
                ++lexemListTraverser;
            }

            operationNode->left = node;
            operationNode->right = analyseExpression();

            return operationNode;
        } catch (...) {
            AbstractSyntaxTree::deleteRecursively(&operationNode);
            throw;
        }
    } else {
        return node;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseTertiaryExpression()
{
    AbstractSyntaxTree::Node *node = analyseSecondaryExpression();
    if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Symbol) && ((lexemListTraverser->data.symbol == '*') ||
                                                                               (lexemListTraverser->data.symbol == '/') ||
                                                                               (lexemListTraverser->data.symbol == '&'))) {
        auto operationNode = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
        operationNode->type = AbstractSyntaxTree::Node::Type::MathematicalOperator;
        operationNode->data.mathematicalOperator[0] = lexemListTraverser->data.symbol;

        try {
            if (lexemListTraverser->data.symbol == '&') {
                ++lexemListTraverser;

                requireSymbol('&');
                operationNode->data.mathematicalOperator[1] = '&';
            } else {
                ++lexemListTraverser;
            }

            operationNode->left = node;
            operationNode->right = analyseTertiaryExpression();

            return operationNode;
        } catch (...) {
            AbstractSyntaxTree::deleteRecursively(&operationNode);
            throw;
        }
    } else {
        return node;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseSecondaryExpression()
{
    AbstractSyntaxTree::Node *node = analysePrimaryExpression();
    if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Symbol) && (lexemListTraverser->data.symbol == '^')) {
        auto operationNode = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
        operationNode->type = AbstractSyntaxTree::Node::Type::MathematicalOperator;
        operationNode->data.mathematicalOperator[0] = '^';
        ++lexemListTraverser;

        try {
            operationNode->left = node;
            operationNode->right = analyseSecondaryExpression();

            return operationNode;
        } catch (...) {
            AbstractSyntaxTree::deleteRecursively(&operationNode);
            throw;
        }
    } else {
        return node;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analysePrimaryExpression()
{
    AbstractSyntaxTree::Node *node = nullptr;
    try {
        if (lookForSymbol('(')) {
            ++lexemListTraverser;

            node = analyseExpression();
            requireSymbol(')');
        } else if (lexemListTraverser->type == ProgramLanguage::Lexem::Type::Identifier) {
            if ((lexemListTraverser[1].type == ProgramLanguage::Lexem::Type::Symbol) && (lexemListTraverser[1].data.symbol == '(')) {
                node = analyseFunctionCallOperator();
            } else {
                node = analyseVariable();
            }
        } else if (lexemListTraverser->type == ProgramLanguage::Lexem::Type::Number) {
            node = analyseNumber();
        } else {
            throw SyntaxError(__FILE__, __LINE__, __func__, "invalid primary expression");
        }

        return node;
    } catch (...) {
        if (node != nullptr) {
            AbstractSyntaxTree::deleteRecursively(&node);
        }

        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseVariable()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::Variable;
    node->data.identifier = lexemListTraverser->data.identifier;

    ++lexemListTraverser;

    return node;
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseNumber()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::Number;
    node->data.number = lexemListTraverser->data.number;

    ++lexemListTraverser;

    return node;
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseReturnOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::ReturnOperator;
    ++lexemListTraverser;

    try {
        node->left = analyseExpression();
        requireSymbol(';');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseOperator()
{
    AbstractSyntaxTree::Node *node = nullptr;
    if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Identifier) &&
        (lexemListTraverser[1].type == ProgramLanguage::Lexem::Type::Symbol)) {
        if (lexemListTraverser[1].data.symbol == '=') {
            node = analyseAssignmentOperator();
        } else if (lexemListTraverser[1].data.symbol == '(') {
            node = analyseFunctionCallOperator();
        } else {
            throw SyntaxError(__FILE__, __LINE__, __func__, "invalid operator");
        }
    } else if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Keyword) &&
               (lexemListTraverser->data.keyword == ProgramLanguage::Keyword::Return)) {
        node = analyseReturnOperator();
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "invalid operator");
    }

    try {
        requireSymbol(';');
        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseAssignmentOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::AssignmentOperator;

    try {
        node->left = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
        node->left->type = AbstractSyntaxTree::Node::Type::Variable;
        node->left->data.identifier = lexemListTraverser->data.identifier;
        ++lexemListTraverser;

        requireSymbol('=');

        node->right = analyseExpression();

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseFunctionCallOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::FunctionCallOperator;
    node->data.identifier = lexemListTraverser->data.identifier;
    ++lexemListTraverser;

    try {
        requireSymbol('(');
        node->left = analyseFunctionCallParameterList();
        requireSymbol(')');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *ProgramLanguageAnalyser::analyseFunctionCallParameterList()
{

    if (lookForSymbol(')')) return nullptr;

    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    node->type = AbstractSyntaxTree::Node::Type::FunctionCallParameter;

    try {
        node->right = analyseExpression();

        if (lookForSymbol(',')) {
            ++lexemListTraverser;

            node->left = analyseFunctionCallParameterList();
        }

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

void ProgramLanguageAnalyser::requireSymbol(char symbol)
{
    if ((lexemListTraverser->type == ProgramLanguage::Lexem::Type::Symbol) && (lexemListTraverser->data.symbol == symbol)) {
        ++lexemListTraverser;
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "expected symbol");
    }
}

bool ProgramLanguageAnalyser::lookForSymbol(char symbol) const
{
    return (lexemListTraverser->type == ProgramLanguage::Lexem::Type::Symbol) && (lexemListTraverser->data.symbol == symbol);
}
