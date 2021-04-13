#ifndef REVERSEDFRONTEND_HPP
#define REVERSEDFRONTEND_HPP

#include "AbstractSyntaxTreeDumpLanguageAnalyser.hpp"

class ReversedFrontend {
public:
    ReversedFrontend();
    void ReversedFrontendDtor();

    void translate(const char *abstractSyntaxTreeInputFileName, const char *translationOutputFileName);

private:
    AbstractSyntaxTreeDumpLanguageAnalyser analyser;

    std::FILE *translationOutputFile;

    int currentBlockDepth;

    void translateFunctionDeclaration(const AbstractSyntaxTree::Node *node);
    void translateFunctionImplementation(const AbstractSyntaxTree::Node *node);
    void translateFunctionImplementationParameter(const AbstractSyntaxTree::Node *node);
    void translateBlock(const AbstractSyntaxTree::Node *node);
    void translateConcatenation(const AbstractSyntaxTree::Node *node);
    void translateStatement(const AbstractSyntaxTree::Node *node);
    void translateIf(const AbstractSyntaxTree::Node *node);
    void translateWhile(const AbstractSyntaxTree::Node *node);
    void translateCondition(const AbstractSyntaxTree::Node *node);
    void translateOperator(const AbstractSyntaxTree::Node *node);
    void translateAssignmentOperator(const AbstractSyntaxTree::Node *node);
    void translateFunctionCallOperator(const AbstractSyntaxTree::Node *node);
    void translateFunctionCallParameter(const AbstractSyntaxTree::Node *node);
    void translateReturnOperator(const AbstractSyntaxTree::Node *node);
    void translateMathematicalOperator(const AbstractSyntaxTree::Node *node);
    void translateExpression(const AbstractSyntaxTree::Node *node);
    void translateVariable(const AbstractSyntaxTree::Node *node);
    void translateNumber(const AbstractSyntaxTree::Node *node);

    static bool mathematicalOperatorOperandNeedsParentheses(char mathematicalOperator, const AbstractSyntaxTree::Node *node);
};

#endif /* REVERSEDFRONTEND_HPP */
