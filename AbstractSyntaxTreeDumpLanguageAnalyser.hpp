#ifndef ABSTRACTSYNTAXTREEDUMPLANGUAGEANALYSER_HPP
#define ABSTRACTSYNTAXTREEDUMPLANGUAGEANALYSER_HPP

#include "AbstractSyntaxTree.hpp"
#include "AbstractSyntaxTreeDumpLanguage.hpp"
#include "AbstractSyntaxTreeDumpLanguageLexer.hpp"
#include "Stack.hpp"

#include <map>

class AbstractSyntaxTreeDumpLanguageAnalyser {
public:
    AbstractSyntaxTree tree;

    struct FunctionScope {
        struct Variable {
            const char *identifier;
            size_t memoryOffset;
        };

        const char *identifier;
        Stack<Variable> variableTable;
    };

    Stack<FunctionScope> functionScopeTable;

    FunctionScope *lookUpFunctionScope(const char *functionIdentifier);
    const FunctionScope::Variable *lookUpVariable(const FunctionScope *functionScope, const char *variableIdentifier);

    FunctionScope *insertFunctionScope(const char *functionIdentifier);
    const FunctionScope::Variable *insertVariable(FunctionScope *functionScope, const char *variableIdentifier);

    AbstractSyntaxTreeDumpLanguageAnalyser();
    void AbstractSyntaxTreeDumpAnalyserDtor();

    void analyseText(const char *textBuffer);

private:
    Stack<AbstractSyntaxTreeDumpLanguage::Lexem> lexemList;
    AbstractSyntaxTreeDumpLanguage::Lexem *lexemListTraverser;
    AbstractSyntaxTreeDumpLanguageLexer lexer;

    FunctionScope *currentFunctionScope;

    AbstractSyntaxTree::Node *analyseAbstractSyntaxTree();
    AbstractSyntaxTree::Node *analyseFunctionDeclaration();
    AbstractSyntaxTree::Node *analyseFunctionDeclarationList();
    AbstractSyntaxTree::Node *analyseFunctionImplementation();
    AbstractSyntaxTree::Node *analyseFunctionImplementationParameter();
    AbstractSyntaxTree::Node *analyseVariable();
    AbstractSyntaxTree::Node *analyseBlock();
    AbstractSyntaxTree::Node *analyseConcatenation();
    AbstractSyntaxTree::Node *analyseStatement();
    AbstractSyntaxTree::Node *analyseIf();
    AbstractSyntaxTree::Node *analyseWhile();
    AbstractSyntaxTree::Node *analyseCondition();
    AbstractSyntaxTree::Node *analyseExpression();
    AbstractSyntaxTree::Node *analyseFunctionCallOperator();
    AbstractSyntaxTree::Node *analyseFunctionCallParameter();
    AbstractSyntaxTree::Node *analyseMathematicalOperator();
    AbstractSyntaxTree::Node *analyseNumber();
    AbstractSyntaxTree::Node *analyseOperator();
    AbstractSyntaxTree::Node *analyseAssignmentOperator();
    AbstractSyntaxTree::Node *analyseReturnOperator();

    void requireSymbol(char symbol);
    void requireKeyword(AbstractSyntaxTreeDumpLanguage::Keyword keyword);

    bool lookForKeyword(AbstractSyntaxTreeDumpLanguage::Keyword keyword);
    bool lookForSymbol(char symbol) const;
};

#endif /* ABSTRACTSYNTAXTREEDUMPLANGUAGEANALYSER_HPP */
