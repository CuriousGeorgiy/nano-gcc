#include "ReversedFrontend.hpp"

#include "File.hpp"

ReversedFrontend::ReversedFrontend()
: analyser(), translationOutputFile(nullptr), currentBlockDepth(0)
{
}

void ReversedFrontend::ReversedFrontendDtor()
{
    analyser.AbstractSyntaxTreeDumpAnalyserDtor();
}

void ReversedFrontend::translate(const char *abstractSyntaxTreeInputFileName, const char *translationOutputFileName)
{
    char *buffer = readFileToBuffer(abstractSyntaxTreeInputFileName, false);

    analyser.analyseText(buffer);
    std::free(buffer);
    buffer = nullptr;

    translationOutputFile = std::fopen(translationOutputFileName, "w");
    translateFunctionDeclaration(analyser.tree.root);
    std::fclose(translationOutputFile);
}

void ReversedFrontend::translateFunctionDeclaration(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    translateFunctionImplementation(node->left);
    translateFunctionDeclaration(node->right);
}

void ReversedFrontend::translateFunctionImplementation(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    std::fprintf(translationOutputFile, "function %s(", node->data.identifier);
    translateFunctionImplementationParameter(node->left);
    std::fprintf(translationOutputFile, ")\n");
    translateBlock(node->right);
}

void ReversedFrontend::translateFunctionImplementationParameter(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    translateVariable(node->right);

    if (node->left != nullptr) {
        std::fprintf(translationOutputFile, ", ");
        translateFunctionImplementationParameter(node->left);
    }
}

void ReversedFrontend::translateBlock(const AbstractSyntaxTree::Node *node)
{
    ++currentBlockDepth;

    if (currentBlockDepth == 1) {
        std::fprintf(translationOutputFile, "{\n");
        translateConcatenation(node);
        std::fprintf(translationOutputFile, "}\n");
    } else {
        std::fprintf(translationOutputFile, "%*c{\n", (currentBlockDepth - 1) * 4, ' ');
        translateConcatenation(node);
        std::fprintf(translationOutputFile, "%*c}\n"
                                            "\n", (currentBlockDepth - 1) * 4, ' ');
    }

    --currentBlockDepth;
}

void
ReversedFrontend::translateConcatenation(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    translateStatement(node->left);
    translateConcatenation(node->right);
}

void ReversedFrontend::translateStatement(const AbstractSyntaxTree::Node *node)
{
    switch (node->type) {
        case AbstractSyntaxTree::Node::Type::If: {
            translateIf(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::While: {
            translateWhile(node);
            break;
        }
        default:
            translateOperator(node);
            break;
    }
}

void ReversedFrontend::translateIf(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "\n"
                                        "%*cif (", currentBlockDepth * 4, ' ');
    translateCondition(node->left);
    std::fprintf(translationOutputFile, ")\n");

    translateBlock(node->right);
}

void ReversedFrontend::translateWhile(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "%*cwhile (", currentBlockDepth * 4, ' ');
    translateCondition(node->left);
    std::fprintf(translationOutputFile, ")\n");

    translateBlock(node->right);
}

void ReversedFrontend::translateCondition(const AbstractSyntaxTree::Node *node)
{
    translateExpression(node);
}

void ReversedFrontend::translateOperator(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "%*c", currentBlockDepth * 4, ' ');

    switch (node->type) {
        case AbstractSyntaxTree::Node::Type::AssignmentOperator: {
            translateAssignmentOperator(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::FunctionCallOperator: {
            translateFunctionCallOperator(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::ReturnOperator: {
            translateReturnOperator(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::MathematicalOperator: {
            translateMathematicalOperator(node);
            break;
        }
        default:
            break;
    }

    std::fprintf(translationOutputFile, ";\n");
}

void ReversedFrontend::translateAssignmentOperator(const AbstractSyntaxTree::Node *node)
{
    translateVariable(node->left);
    std::fprintf(translationOutputFile, " = ");
    translateExpression(node->right);
}

void ReversedFrontend::translateVariable(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "%s", node->data.identifier);
}

void ReversedFrontend::translateFunctionCallOperator(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "%s(", node->data.identifier);
    translateFunctionCallParameter(node->left);
    std::fprintf(translationOutputFile, ")");
}

void ReversedFrontend::translateFunctionCallParameter(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    translateExpression(node->right);

    if (node->left != nullptr) {
        std::fprintf(translationOutputFile, ", ");
        translateFunctionCallParameter(node->left);
    }
}

void ReversedFrontend::translateReturnOperator(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "return ");
    translateExpression(node->left);
}

void ReversedFrontend::translateMathematicalOperator(const AbstractSyntaxTree::Node *node)
{
    if (mathematicalOperatorOperandNeedsParentheses(node->data.mathematicalOperator[0], node->left)) {
        std::fprintf(translationOutputFile, "(");
        translateExpression(node->left);
        std::fprintf(translationOutputFile, ")");
    } else {
        translateExpression(node->left);
    }

    std::fprintf(translationOutputFile, " %s ", node->data.mathematicalOperator);

    if (mathematicalOperatorOperandNeedsParentheses(node->data.mathematicalOperator[0], node->right)) {
        std::fprintf(translationOutputFile, "(");
        translateExpression(node->right);
        std::fprintf(translationOutputFile, ")");
    } else {
        translateExpression(node->right);
    }
}

void ReversedFrontend::translateExpression(const AbstractSyntaxTree::Node *node)
{
    switch (node->type) {
        case AbstractSyntaxTree::Node::Type::Variable: {
            translateVariable(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::Number: {
            translateNumber(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::FunctionCallOperator: {
            translateFunctionCallOperator(node);
            break;
        }
        case AbstractSyntaxTree::Node::Type::MathematicalOperator: {
            translateMathematicalOperator(node);
            break;
        }
        default:
            break;
    }
}

void ReversedFrontend::translateNumber(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "%lg", node->data.number);
}

bool ReversedFrontend::mathematicalOperatorOperandNeedsParentheses(char mathematicalOperator, const AbstractSyntaxTree::Node *node)
{
    return ((mathematicalOperator == '*') || (mathematicalOperator == '/')) &&
           (node->type == AbstractSyntaxTree::Node::Type::MathematicalOperator) &&
           (node->data.mathematicalOperator[0] != mathematicalOperator);
}
