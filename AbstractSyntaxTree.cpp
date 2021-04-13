#include "AbstractSyntaxTree.hpp"

#include <cstdio>
#include <cstdlib>

AbstractSyntaxTree::AbstractSyntaxTree()
: root(nullptr)
{
}

void AbstractSyntaxTree::AbstractSyntaxTreeDtor()
{
    if (root != nullptr) {
        deleteRecursively(&root);
    }
}

void AbstractSyntaxTree::deleteRecursively(Node **node)
{
    if ((*node)->left != nullptr) {
        deleteRecursively(&(*node)->left);
    }

    if ((*node)->right != nullptr) {
        deleteRecursively(&(*node)->right);
    }

    std::free(*node);
    *node = nullptr;
}

void AbstractSyntaxTree::dumpToText(const char *outputFileName) const
{
    std::FILE *outputFile = std::fopen(outputFileName, "w");
    std::fprintf(outputFile, "{\n");
    dumpToTextRecursively(outputFile, root);
    std::fprintf(outputFile, "}\n");
    std::fclose(outputFile);
}

void AbstractSyntaxTree::dumpToTextRecursively(std::FILE *outputFile, Node *node)
{
    if (node == nullptr) {
        std::fprintf(outputFile, "nil\n");
        return;
    }

    switch (node->type) {
        case Node::Type::FunctionDeclaration: {
            std::fprintf(outputFile, "function-declaration\n"
                                     "{\n");
            break;
        }
        case Node::Type::FunctionImplementation: {
            std::fprintf(outputFile, "%s\n"
                                     "{\n", node->data.identifier);
            break;
        }
        case Node::Type::FunctionImplementationParameter: {
            std::fprintf(outputFile, "function-implementation-parameter\n"
                                     "{\n");
            break;
        }
        case Node::Type::Variable: {
            std::fprintf(outputFile, "%s\n"
                                     "{\n", node->data.identifier);
            break;
        }
        case Node::Type::Concatenation: {
            std::fprintf(outputFile, "concatenation\n"
                                     "{\n");
            break;
        }
        case Node::Type::If: {
            std::fprintf(outputFile, "if\n"
                                     "{\n");
            break;
        }
        case Node::Type::While: {
            std::fprintf(outputFile, "while\n"
                                     "{\n");
            break;
        }
        case Node::Type::AssignmentOperator: {
            std::fprintf(outputFile, "=\n"
                                     "{\n");
            break;
        }
        case Node::Type::FunctionCallOperator: {
            std::fprintf(outputFile, "$%s\n"
                                     "{\n", node->data.identifier);
            break;
        }
        case Node::Type::FunctionCallParameter: {
            std::fprintf(outputFile, "function-call-parameter\n"
                                     "{\n");
            break;
        }
        case Node::Type::ReturnOperator: {
            std::fprintf(outputFile, "return\n"
                                     "{\n");
            break;
        }
        case Node::Type::MathematicalOperator: {
            std::fprintf(outputFile, "%s\n"
                                     "{\n", node->data.mathematicalOperator);
            break;
        }
        case Node::Type::Number: {
            std::fprintf(outputFile, "%lg\n"
                                     "{\n", node->data.number);
            break;
        }
    }

    dumpToTextRecursively(outputFile, node->left);
    std::fprintf(outputFile, "}\n"
                             "{\n");
    dumpToTextRecursively(outputFile, node->right);
    std::fprintf(outputFile, "}\n");
}

AbstractSyntaxTree::Node *AbstractSyntaxTree::copySubtreeRecursively(const Node *node)
{
    if (node == nullptr) return nullptr;

    auto nodeCopy = (Node *) std::calloc(1, sizeof(Node));
    nodeCopy->type = node->type;
    nodeCopy->data = node->data;
    nodeCopy->left = copySubtreeRecursively(node->left);
    nodeCopy->right = copySubtreeRecursively(node->right);

    return nodeCopy;
}

#if 0
AbstractSyntaxTree::Node *AbstractSyntaxTree::createNumberNode(double number)
{
    auto node = (Node *) std::calloc(1, sizeof(Node));
}
#endif
