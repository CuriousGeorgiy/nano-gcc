#include "AbstractSyntaxTreeDumpLanguageAnalyser.hpp"

#include "SyntaxError.hpp"

AbstractSyntaxTreeDumpLanguageAnalyser::AbstractSyntaxTreeDumpLanguageAnalyser()
: tree(), functionScopeTable(), lexemListTraverser(nullptr), lexemList(), lexer(), currentFunctionScope(nullptr)
{
}

void AbstractSyntaxTreeDumpLanguageAnalyser::AbstractSyntaxTreeDumpAnalyserDtor()
{
    for (size_t i = 0; i < lexemList.size; ++i) {
        if (lexemList.data[i].type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Identifier) {
            std::free(lexemList.data[i].data.identifier);
            lexemList.data[i].data.identifier = nullptr;
        }
    }

    lexemList.StackDtor();
    tree.AbstractSyntaxTreeDtor();
}

void AbstractSyntaxTreeDumpLanguageAnalyser::analyseText(const char *textBuffer)
{
    lexer.tokenizeText(textBuffer, &lexemList);

    lexemListTraverser = lexemList.data;
    tree.root = analyseAbstractSyntaxTree();
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseAbstractSyntaxTree()
{
    requireSymbol('{');
    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::FunctionDeclaration)) {
        ++lexemListTraverser;

        AbstractSyntaxTree::Node *node = analyseFunctionDeclaration();
        requireSymbol('}');

        return node;
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "at least the \"main\" function must be declared");
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseFunctionDeclaration()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::FunctionDeclaration;

        requireSymbol('{');
        node->left = analyseFunctionImplementation();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseFunctionDeclarationList();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseFunctionDeclarationList()
{
    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil)) {
        ++lexemListTraverser;
        return nullptr;
    }

    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::FunctionDeclaration)) {
        ++lexemListTraverser;

        AbstractSyntaxTree::Node *node = analyseFunctionDeclaration();

        return node;
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "expected function declaration");
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseFunctionImplementation()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        if (lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Identifier) {
            node->type = AbstractSyntaxTree::Node::Type::FunctionImplementation;
            node->data.identifier = lexemListTraverser->data.identifier;
            ++lexemListTraverser;

            currentFunctionScope = insertFunctionScope(node->data.identifier);

            requireSymbol('{');
            node->left = analyseFunctionImplementationParameter();
            requireSymbol('}');

            requireSymbol('{');
            node->right = analyseBlock();
            requireSymbol('}');

            return node;
        } else {
            throw SyntaxError(__FILE__, __LINE__, __func__, "expected function identifier");
        }
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseFunctionImplementationParameter()
{
    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil)) {
        ++lexemListTraverser;
        return nullptr;
    }

    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::FunctionImplementationParameter;
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::FunctionImplementationParameter);

        requireSymbol('{');
        node->left = analyseFunctionImplementationParameter();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseVariable();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseVariable()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::Variable;
        node->data.identifier = lexemListTraverser->data.identifier;
        ++lexemListTraverser;

        if (!lookUpVariable(currentFunctionScope, node->data.identifier)) {
            insertVariable(currentFunctionScope, node->data.identifier);
        }

        requireSymbol('{');
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil);
        requireSymbol('}');

        requireSymbol('{');
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil);
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseBlock()
{
    return analyseConcatenation();
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseConcatenation()
{
    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil)) {
        ++lexemListTraverser;
        return nullptr;
    }

    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::Concatenation;
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Concatenation);

        requireSymbol('{');
        node->left = analyseStatement();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseConcatenation();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseStatement()
{
    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::If)) {
        ++lexemListTraverser;

        return analyseIf();
    } else if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::While)) {
        ++lexemListTraverser;

        return analyseWhile();
    } else {
        return analyseOperator();
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseIf()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::If;

        requireSymbol('{');
        node->left = analyseCondition();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseBlock();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseWhile()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::While;

        requireSymbol('{');
        node->left = analyseCondition();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseBlock();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseCondition()
{
    return analyseExpression();
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseExpression()
{
    if (lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Number) {
        return analyseNumber();
    } else if (lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Identifier) {
        return analyseVariable();
    } else if (lookForSymbol('$')) {
        ++lexemListTraverser;
        return analyseFunctionCallOperator();
    } else if (lookForSymbol('+') || lookForSymbol('-') || lookForSymbol('*') || lookForSymbol('/') || lookForSymbol('^') ||
               lookForSymbol('&') || lookForSymbol('|') || lookForSymbol('<') || lookForSymbol('=') || lookForSymbol('>')) {
        return analyseMathematicalOperator();
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "expected expression");
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseFunctionCallOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::FunctionCallOperator;

        if (lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Identifier) {
            node->data.identifier = lexemListTraverser->data.identifier;
            ++lexemListTraverser;

            requireSymbol('{');
            node->left = analyseFunctionCallParameter();
            requireSymbol('}');

            requireSymbol('{');
            requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil);
            requireSymbol('}');

            return node;
        } else {
            throw SyntaxError(__FILE__, __LINE__, __func__, "expected functionIdentifier");
        }
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseFunctionCallParameter()
{
    if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil)) {
        ++lexemListTraverser;
        return nullptr;
    }

    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::FunctionCallParameter;
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::FunctionCallParameter);

        requireSymbol('{');
        node->left = analyseFunctionCallParameter();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseExpression();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseMathematicalOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::MathematicalOperator;
        node->data.mathematicalOperator[0] = lexemListTraverser->data.symbol;
        ++lexemListTraverser;

        if ((node->data.mathematicalOperator[0] == '|') || (node->data.mathematicalOperator[0] == '&') ||
            (node->data.mathematicalOperator[0] == '=')) {
            requireSymbol(node->data.mathematicalOperator[0]);
            node->data.mathematicalOperator[1] = node->data.mathematicalOperator[0];
        }

        if ((node->data.mathematicalOperator[0] == '<') || (node->data.mathematicalOperator[0] == '>')) {
            if (lookForSymbol('=')) {
                ++lexemListTraverser;
                node->data.mathematicalOperator[1] = '=';
            }
        }

        requireSymbol('{');
        node->left = analyseExpression();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseExpression();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseNumber()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::Number;
        node->data.number = lexemListTraverser->data.number;
        ++lexemListTraverser;

        requireSymbol('{');
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil);
        requireSymbol('}');

        requireSymbol('{');
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil);
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseOperator()
{
    if (lookForSymbol('=')) {
        ++lexemListTraverser;
        return analyseAssignmentOperator();
    } else if (lookForSymbol('$')) {
        ++lexemListTraverser;
        return analyseFunctionCallOperator();
    } else if (lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Return)) {
        ++lexemListTraverser;
        return analyseReturnOperator();
    } else if (lookForSymbol('+') || lookForSymbol('-') || lookForSymbol('*') || lookForSymbol('/') || lookForSymbol('^') ||
               lookForSymbol('&') || lookForSymbol('|') || lookForSymbol('<') || lookForSymbol('=') || lookForSymbol('>')) {
        return analyseMathematicalOperator();
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "invalid operator");
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseAssignmentOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::AssignmentOperator;

        requireSymbol('{');
        node->left = analyseVariable();
        requireSymbol('}');

        requireSymbol('{');
        node->right = analyseExpression();
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

AbstractSyntaxTree::Node *AbstractSyntaxTreeDumpLanguageAnalyser::analyseReturnOperator()
{
    auto node = (AbstractSyntaxTree::Node *) std::calloc(1, sizeof(AbstractSyntaxTree::Node));
    try {
        node->type = AbstractSyntaxTree::Node::Type::ReturnOperator;

        requireSymbol('{');
        node->left = analyseExpression();
        requireSymbol('}');

        requireSymbol('{');
        requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword::Nil);
        requireSymbol('}');

        return node;
    } catch (...) {
        AbstractSyntaxTree::deleteRecursively(&node);
        throw;
    }
}

void AbstractSyntaxTreeDumpLanguageAnalyser::requireSymbol(char symbol)
{
    if ((lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Symbol) && (lexemListTraverser->data.symbol == symbol)) {
        ++lexemListTraverser;
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "expected symbol");
    }
}

bool AbstractSyntaxTreeDumpLanguageAnalyser::lookForSymbol(char symbol) const
{
    return (lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Symbol) && (lexemListTraverser->data.symbol == symbol);
}

bool AbstractSyntaxTreeDumpLanguageAnalyser::lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword keyword)
{
    return (lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Keyword) &&
           (lexemListTraverser->data.keyword == keyword);
}

void AbstractSyntaxTreeDumpLanguageAnalyser::requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword keyword)
{
    if ((lexemListTraverser->type == AbstractSyntaxTreeDumpLanguage::Lexem::Type::Keyword) &&
        (lexemListTraverser->data.keyword == keyword)) {
        ++lexemListTraverser;
    } else {
        throw SyntaxError(__FILE__, __LINE__, __func__, "expected keyword");
    }
}

AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope *
AbstractSyntaxTreeDumpLanguageAnalyser::lookUpFunctionScope(const char *functionIdentifier)
{
    for (size_t i = 0; i < functionScopeTable.size; ++i) {
        if (std::strcmp(functionIdentifier, functionScopeTable.data[i].identifier) == 0) {
            return functionScopeTable.data + i;
        }
    }

    return nullptr;
}

const AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope::Variable *
AbstractSyntaxTreeDumpLanguageAnalyser::lookUpVariable(const AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope *functionScope,
                                                       const char *variableIdentifier)
{
    for (size_t i = 0; i < functionScope->variableTable.size; ++i) {
        if (std::strcmp(variableIdentifier, functionScope->variableTable.data[i].identifier) == 0) {
            return functionScope->variableTable.data + i;
        }
    }

    return nullptr;
}

AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope *
AbstractSyntaxTreeDumpLanguageAnalyser::insertFunctionScope(const char *functionIdentifier)
{
    functionScopeTable.push(FunctionScope{.identifier = functionIdentifier, .variableTable{}});

    return functionScopeTable.data + (functionScopeTable.size - 1);
}

const AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope::Variable *
AbstractSyntaxTreeDumpLanguageAnalyser::insertVariable(AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope *functionScope,
                                                       const char *variableIdentifier)
{
    functionScope->variableTable.push(FunctionScope::Variable{.identifier = variableIdentifier,
    .memoryOffset = functionScope->variableTable.size + 1});

    return functionScope->variableTable.data + (functionScopeTable.size - 1);
}
