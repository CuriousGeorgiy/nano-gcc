#ifndef MIDDLEEND_HPP
#define MIDDLEEND_HPP

#include "AbstractSyntaxTreeDumpLanguageAnalyser.hpp"

class Middleend {
public:
    Middleend();
    void MiddleendDtor();

    void optimize(const char *abstractSyntaxTreeFileName);

private:
    AbstractSyntaxTreeDumpLanguageAnalyser analyser;

    void lookForDifferentiationOperatorRecursively(AbstractSyntaxTree::Node *node);

    AbstractSyntaxTree::Node *differentiateNode(const AbstractSyntaxTree::Node *node);
    AbstractSyntaxTree::Node *differentiateNodeRecursively(const AbstractSyntaxTree::Node *node);

    void optimizeTree(AbstractSyntaxTree::Node **root);
    bool optimizeNeutralElementNodesRecursively(AbstractSyntaxTree::Node **node);
    bool optimizeEvaluableNodesRecursively(AbstractSyntaxTree::Node *node);
    bool optimizeSpecialConstantNodesRecursively(AbstractSyntaxTree::Node **node);

    static void optimizeLeftNode(AbstractSyntaxTree::Node **node);
    static void optimizeRightNode(AbstractSyntaxTree::Node **node);
    static void zeroNode(AbstractSyntaxTree::Node *node);

    static bool isConstant(const AbstractSyntaxTree::Node *node, int constant);
};

#endif /* MIDDLEEND_HPP */
