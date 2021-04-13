#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "ProgramLanguage.hpp"

#include <cstdio>

class AbstractSyntaxTree {
public:
    struct Node {
        enum class Type {
            FunctionDeclaration,
            FunctionImplementation,
            FunctionImplementationParameter,
            Variable,
            Concatenation,
            If,
            While,
            AssignmentOperator,
            FunctionCallOperator,
            FunctionCallParameter,
            ReturnOperator,
            MathematicalOperator,
            Number
        } type;

        union {
            const char *identifier;
            char mathematicalOperator[3];
            double number;
        } data;

        Node *left;
        Node *right;
    } *root;

    AbstractSyntaxTree();

    void AbstractSyntaxTreeDtor();
    static void deleteRecursively(Node **node);

    void dumpToText(const char *outputFileName) const;
    static void dumpToTextRecursively(std::FILE *outputFile, Node *node);

    static Node *copySubtreeRecursively(const Node *node);

    Node *createNumberNode(double number);
};

#endif /* ABSTRACTSYNTAXTREE_HPP */
