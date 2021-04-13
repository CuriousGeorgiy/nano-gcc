#ifndef BACKEND_HPP
#define BACKEND_HPP

#include "AbstractSyntaxTreeDumpLanguageAnalyser.hpp"

#include <cstdio>
#include <map>

class Backend {
public:
    Backend();
    void BackendDtor();

    void translate(const char *abstractSyntaxTreeInputFileName, const char *translationOutputFileName);

private:
    AbstractSyntaxTreeDumpLanguageAnalyser analyser;

    AbstractSyntaxTreeDumpLanguageAnalyser::FunctionScope *currentFunctionScope;

    std::FILE *translationOutputFile;

    void translateFunctionDeclaration(const AbstractSyntaxTree::Node *node);
    void translateFunctionImplementation(const AbstractSyntaxTree::Node *node);
    void translateBlock(const AbstractSyntaxTree::Node *node);
    void translateConcatenation(const AbstractSyntaxTree::Node *node);
    void translateStatement(const AbstractSyntaxTree::Node *node);
    void translateIf(const AbstractSyntaxTree::Node *node);
    void translateWhile(const AbstractSyntaxTree::Node *node);
    void translateCondition(const AbstractSyntaxTree::Node *node, bool isIfCondition, size_t uniqueJumpLabelNo);
    void translateOperator(const AbstractSyntaxTree::Node *node);
    void translateAssignmentOperator(const AbstractSyntaxTree::Node *node);
    void translateFunctionCallOperator(const AbstractSyntaxTree::Node *node);
    void translateFunctionCallParameter(const AbstractSyntaxTree::Node *node, size_t parameterNo);
    void translateReturnOperator(const AbstractSyntaxTree::Node *node);
    void translateMathematicalOperator(const AbstractSyntaxTree::Node *node);
    void translateExpression(const AbstractSyntaxTree::Node *node);
    void translateVariable(const AbstractSyntaxTree::Node *node, bool forAssignment);
    void translateNumber(const AbstractSyntaxTree::Node *node);
};

#endif /* BACKEND_HPP */
