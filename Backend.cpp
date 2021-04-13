#include "Backend.hpp"

#include "File.hpp"

Backend::Backend()
: analyser(), currentFunctionScope(nullptr), translationOutputFile(nullptr)
{
}

void Backend::BackendDtor()
{
    analyser.AbstractSyntaxTreeDumpAnalyserDtor();
}

void Backend::translate(const char *abstractSyntaxTreeInputFileName, const char *translationOutputFileName)
{
    char *buffer = readFileToBuffer(abstractSyntaxTreeInputFileName, false);

    analyser.analyseText(buffer);
    std::free(buffer);
    buffer = nullptr;

    translationOutputFile = std::fopen(translationOutputFileName, "w");

    std::fprintf(translationOutputFile, "push 0\n"
                                        "pop rax\n"
                                        "push 0\n"
                                        "pop rbx\n"
                                        "push 0\n"
                                        "pop rcx\n"
                                        "push 0\n"
                                        "pop rdx\n"
                                        "call :main\n"
                                        "hlt\n");
    translateFunctionDeclaration(analyser.tree.root);

    std::fclose(translationOutputFile);
}

void Backend::translateFunctionDeclaration(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    translateFunctionImplementation(node->left);
    translateFunctionDeclaration(node->right);
}

void Backend::translateFunctionImplementation(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    std::fprintf(translationOutputFile, "\n"
                                        "; translation of function implementation\n"
                                        "%s:\n", node->data.identifier);
    currentFunctionScope = analyser.lookUpFunctionScope(node->data.identifier);
    translateBlock(node->right);
}

void Backend::translateBlock(const AbstractSyntaxTree::Node *node)
{
    translateConcatenation(node);
}

void
Backend::translateConcatenation(const AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    translateStatement(node->left);
    translateConcatenation(node->right);
}

void Backend::translateStatement(const AbstractSyntaxTree::Node *node)
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

void Backend::translateIf(const AbstractSyntaxTree::Node *node)
{
    static size_t uniqueLabelNo = 0;

    size_t labelNo = uniqueLabelNo++;
    translateCondition(node->left, true, labelNo);
    translateBlock(node->right);
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of label for if ending\n"
                                        "EndIf%zu:\n", labelNo);
}

void Backend::translateWhile(const AbstractSyntaxTree::Node *node)
{
    static size_t uniqueLabelNo = 0;

    size_t labelNo = uniqueLabelNo++;
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of label for while beginning\n"
                                        "BeginWhile%zu:\n", labelNo);
    translateCondition(node->left, false, labelNo);
    translateBlock(node->right);
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of jump to while beginning\n"
                                        "jmp :BeginWhile%zu\n", labelNo);
    std::fprintf(translationOutputFile, "; translation of label for while ending\n"
                                        "EndWhile%zu:\n", labelNo);
}

void Backend::translateCondition(const AbstractSyntaxTree::Node *node, bool isIfCondition, size_t uniqueJumpLabelNo)
{
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of jump for conditional statement\n");

    switch (node->data.mathematicalOperator[0]) {
        case '<': {
            translateExpression(node->left);
            translateExpression(node->right);
            std::fprintf(translationOutputFile, "%s :%s%zu\n", (node->data.mathematicalOperator[1] == '=') ? "ja" : "jae",
                         isIfCondition ? "EndIf" : "EndWhile", uniqueJumpLabelNo);
            break;
        }
        case '=': {
            translateExpression(node->left);
            translateExpression(node->right);
            std::fprintf(translationOutputFile, "jne :%s%zu\n", isIfCondition ? "EndIf" : "EndWhile", uniqueJumpLabelNo);
            break;
        }
        case '>': {
            translateExpression(node->left);
            translateExpression(node->right);
            std::fprintf(translationOutputFile, "%s :%s%zu\n", (node->data.mathematicalOperator[1] == '=') ? "jb" : "jbe",
                         isIfCondition ? "EndIf" : "EndWhile", uniqueJumpLabelNo);
            break;
        }
    }
}

void Backend::translateOperator(const AbstractSyntaxTree::Node *node)
{
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
}

void Backend::translateAssignmentOperator(const AbstractSyntaxTree::Node *node)
{
    translateExpression(node->right);
    translateVariable(node->left, true);
}

void Backend::translateVariable(const AbstractSyntaxTree::Node *node, bool forAssignment)
{
    if (forAssignment) {
        std::fprintf(translationOutputFile, "\n"
                                            "; translation of variable \"%s\" assignment\n"
                                            "pop [rbx+%zu]\n", node->data.identifier,
                     analyser.lookUpVariable(currentFunctionScope, node->data.identifier)->memoryOffset);
    } else {
        std::fprintf(translationOutputFile, "\n"
                                            "; translation of variable \"%s\" access\n"
                                            "push [rbx+%zu]\n", node->data.identifier,
                     analyser.lookUpVariable(currentFunctionScope, node->data.identifier)->memoryOffset);
    }
}

void Backend::translateFunctionCallOperator(const AbstractSyntaxTree::Node *node)
{
    if (strcmp(node->data.identifier, "print") == 0) {
        translateExpression(node->left->right);
        std::fprintf(translationOutputFile, "\n"
                                            "; translation of \"print\" function\n"
                                            "out\n");
    } else if (strcmp(node->data.identifier, "scan") == 0) {
        std::fprintf(translationOutputFile, "\n"
                                            "; translation of \"scan\" function\n"
                                            "in\n");
        translateVariable(node->left->right, true);
    } else if (strcmp(node->data.identifier, "sqrt") == 0) {
        translateExpression(node->left->right);
        std::fprintf(translationOutputFile, "\n"
                                            "; translation of \"sqrt\" function\n"
                                            "sqrt\n");
    } else {
        std::fprintf(translationOutputFile, "\n"
                                            "; translation of function call operator (\"%s\" function)\n"
                                            "; set rcx to next rpb\n"
                                            "push %zu\n"
                                            "push rbx\n"
                                            "add\n"
                                            "pop rcx\n", node->data.identifier, currentFunctionScope->variableTable.size);
        translateFunctionCallParameter(node->left, 1);
        std::fprintf(translationOutputFile, "\n"
                                            "; remember current rbp\n"
                                            "push rbx\n"
                                            "pop [rcx]\n"
                                            "; move rbp before function call operator\n"
                                            "push rcx\n"
                                            "pop rbx\n");
        std::fprintf(translationOutputFile, "call :%s\n", node->data.identifier);
        std::fprintf(translationOutputFile, "\n"
                                            "; retrieve function's return value\n"
                                            "push rax\n"
                                            "; retrieve rbp after function call operator\n"
                                            "push [rcx]\n"
                                            "pop rbx\n"
                                            "; set rcx to current rbp\n"
                                            "push rbx\n"
                                            "pop rcx\n");
    }
}

void Backend::translateFunctionCallParameter(const AbstractSyntaxTree::Node *node, size_t parameterNo)
{
    if (node == nullptr) return;

    translateExpression(node->right);
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of function call parameter\n"
                                        "pop [rcx+%zu]\n", parameterNo);
    translateFunctionCallParameter(node->left, parameterNo + 1);
}

void Backend::translateReturnOperator(const AbstractSyntaxTree::Node *node)
{
    translateExpression(node->left);
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of return operator\n"
                                        "pop rax\n"
                                        "ret\n");
}

void Backend::translateMathematicalOperator(const AbstractSyntaxTree::Node *node)
{
    translateExpression(node->left);
    translateExpression(node->right);

    switch (node->data.mathematicalOperator[0]) {
        case '+': {
            std::fprintf(translationOutputFile, "\n"
                                                "; translation of \'+\'\n"
                                                "add\n");
            break;
        }
        case '-': {
            std::fprintf(translationOutputFile, "\n"
                                                "; translation of \'-\'\n"
                                                "sub\n");
            break;
        }
        case '*': {
            std::fprintf(translationOutputFile, "\n"
                                                "; translation of \'*\'\n"
                                                "mul\n");
            break;
        }
        case '/': {
            std::fprintf(translationOutputFile, "\n"
                                                "; translation of \'/\'\n"
                                                "div\n");
            break;
        }
        case '^': {
            std::fprintf(translationOutputFile, "\n"
                                                "; translation of \'^\'\n"
                                                "pow\n");
            break;
        }
    }
}

void Backend::translateExpression(const AbstractSyntaxTree::Node *node)
{
    switch (node->type) {
        case AbstractSyntaxTree::Node::Type::Variable: {
            translateVariable(node, false);
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

void Backend::translateNumber(const AbstractSyntaxTree::Node *node)
{
    std::fprintf(translationOutputFile, "\n"
                                        "; translation of number\n"
                                        "push %lg\n", node->data.number);
}
