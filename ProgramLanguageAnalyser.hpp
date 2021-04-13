#ifndef PROGRAMLANGUAGEANALYSER_HPP
#define PROGRAMLANGUAGEANALYSER_HPP

#include "AbstractSyntaxTree.hpp"
#include "Stack.hpp"
#include "ProgramLanguage.hpp"
#include "ProgramLanguageLexer.hpp"

class ProgramLanguageAnalyser {
public:
    AbstractSyntaxTree abstractSyntaxTree;

    ProgramLanguageAnalyser();
    void ProgramLanguageAnalyserDtor();

    void analyseText(const char *textBuffer);

private:
    Stack<ProgramLanguage::Lexem> lexemList;
    ProgramLanguage::Lexem *lexemListTraverser;
    ProgramLanguageLexer lexer;

    AbstractSyntaxTree::Node *analyseProgram();
    AbstractSyntaxTree::Node *analyseFunctionDeclarationList();
    AbstractSyntaxTree::Node *analyseFunctionDeclaration();
    AbstractSyntaxTree::Node *analyseFunctionImplementation();
    AbstractSyntaxTree::Node *analyseFunctionImplementationParameterList();
    AbstractSyntaxTree::Node *analyseBlock();
    AbstractSyntaxTree::Node *analyseStatement();
    AbstractSyntaxTree::Node *analyseIf();
    AbstractSyntaxTree::Node *analyseWhile();
    AbstractSyntaxTree::Node *analyseCondition();
    AbstractSyntaxTree::Node *analyseExpression();
    AbstractSyntaxTree::Node *analyseTertiaryExpression();
    AbstractSyntaxTree::Node *analyseSecondaryExpression();
    AbstractSyntaxTree::Node *analysePrimaryExpression();
    AbstractSyntaxTree::Node *analyseReturnOperator();
    AbstractSyntaxTree::Node *analyseOperator();
    AbstractSyntaxTree::Node *analyseAssignmentOperator();
    AbstractSyntaxTree::Node *analyseFunctionCallOperator();
    AbstractSyntaxTree::Node *analyseFunctionCallParameterList();
    AbstractSyntaxTree::Node *analyseBlockBody();
    AbstractSyntaxTree::Node *analyseVariable();
    AbstractSyntaxTree::Node *analyseNumber();

    void requireSymbol(char symbol);
    bool lookForSymbol(char symbol) const;
};

#endif /* PROGRAMLANGUAGEANALYSER_HPP */
