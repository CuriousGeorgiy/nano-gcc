#include "Middleend.hpp"

#include "File.hpp"

Middleend::Middleend()
: analyser()
{
}

void Middleend::MiddleendDtor()
{
    analyser.AbstractSyntaxTreeDumpAnalyserDtor();
}

void Middleend::optimize(const char *abstractSyntaxTreeFileName)
{
    char *buffer = readFileToBuffer(abstractSyntaxTreeFileName, false);

    analyser.analyseText(buffer);
    std::free(buffer);
    buffer = nullptr;

    lookForDifferentiationOperatorRecursively(analyser.tree.root);

    analyser.tree.dumpToText(abstractSyntaxTreeFileName);
}

void Middleend::lookForDifferentiationOperatorRecursively(AbstractSyntaxTree::Node *node)
{
    if (node == nullptr) return;

    if ((node->type == AbstractSyntaxTree::Node::Type::FunctionCallOperator)
        && (std::strcmp(node->data.identifier, "differentiate") == 0)) {
        differentiateNode(node);
    }
}

#if 0
AbstractSyntaxTree::Node *Middleend::differentiateNodeRecursively(const AbstractSyntaxTree::Node *node)
{
#define L node->left
#define R node->right
#define TYPE node->type
#define lTYPE node->left->type
#define rTYPE node->right->type
#define dL differentiateNodeRecursively(L)
#define dR differentiateNodeRecursively(R)
#define cL AbstractSyntaxTree::copySubtreeRecursively(L)
#define cR AbstractSyntaxTree::copySubtreeRecursively(R)
#define CREATE_MATHEMATICAL_OPERATION_NODE(operation, leftNode, rightNode) \
AbstractSyntaxTree::createMathematicalOperationNode((operation), (leftNode), (rightNode))
#define CONSTANT(constant) AbstractSyntaxTree::createNumberNode(constant)
#define ADDITION(leftNode, rightNode) CREATE_MATHEMATICAL_OPERATION_NODE('+', (leftNode), (rightNode))
#define SUBTRACTION(leftNode, rightNode) CREATE_MATHEMATICAL_OPERATION_NODE('-', (leftNode), (rightNode))
#define MULTIPLICATION(leftNode, rightNode) CREATE_MATHEMATICAL_OPERATION_NODE('*', (leftNode), (rightNode))
#define DIVISION(leftNode, rightNode) CREATE_MATHEMATICAL_OPERATION_NODE('/', (leftNode), (rightNode))
#define POWER(leftNode, rightNode) CREATE_MATHEMATICAL_OPERATION_NODE('^', (leftNode), (rightNode))

    switch (TYPE) {
        case AbstractSyntaxTree::Node::: {
            auto resultNode = CONSTANT(0);
            END_DIFFERENTIATION("Zero the derivative of a constant everyday");
            return
            resultNode;
        }
        case Variable: {
            auto resultNode = CONSTANT(1);
            END_DIFFERENTIATION("Formula from \"An Introduction to Statistical Learning: With Applications in R\"");
            return
            resultNode;
        }
        case Operation: {
            switch (node->data) {
                case Addition: {
                    auto resultNode = ADDITION(dL, dR);
                    END_DIFFERENTIATION("No matter addition or substraction - the differentiation operator is linear");
                    return
                    resultNode;
                }
                case Subtraction: {
                    auto resultNode = SUBTRACTION(dL, dR);
                    END_DIFFERENTIATION("No matter addition or substraction - the differentiation operator is linear");
                    return
                    resultNode;
                }
                case Multiplication: {
                    auto resultNode = ADDITION(MULTIPLICATION(dL, cR), MULTIPLICATION(cL, dR));
                    END_DIFFERENTIATION("At least we dont need the general Leibniz rule here");
                    return
                    resultNode;
                }
                case Division: {
                    auto resultNode = DIVISION(SUBTRACTION(MULTIPLICATION(dL, cR), MULTIPLICATION(cL, dR)), POWER(cR, CONSTANT(2)));
                    END_DIFFERENTIATION("Divide and conquer");
                    return
                    resultNode;
                }
                case Power: {
                    BinaryTree::Node *resultNode = nullptr;
                    if (((lTYPE == Variable) || lTYPE == Operation) && (rTYPE == Constant)) {
                        resultNode = MULTIPLICATION(cR, MULTIPLICATION(POWER(cL, SUBTRACTION(cR, CONSTANT(1))), dL));
                    } else if ((lTYPE == Constant) && ((rTYPE == Variable) || (rTYPE == Operation))) {
                        resultNode = MULTIPLICATION(MULTIPLICATION(POWER(cL, cR), LN(cR)), dR);
                    } else {
                        resultNode = MULTIPLICATION(POWER(cL, cR),
                                                    ADDITION(MULTIPLICATION(dR, LN(cL)),
                                                             MULTIPLICATION(cR, MULTIPLICATION(DIVISION(CONSTANT(1), cL), dL))));
                    }
                    END_DIFFERENTIATION("Every soviet kindergarten graduate knows");
                    return
                    resultNode;
                }
            }
        }
    }
}

bool Middleend::optimizeNeutralElementNodesRecursively(BinaryTree::Node **node)
{
    if (*node == nullptr) return false;

    bool optimizedLeftSubtree = optimizeNeutralElementNodesRecursively(&(*node)->left);
    bool optimizedRightSubtree = optimizeNeutralElementNodesRecursively(&(*node)->right);

    if ((*node)->type != Operation) return optimizedLeftSubtree || optimizedRightSubtree;

    bool optimizedSubtree = false;
    switch ((*node)->data) {
        case Addition: {
            if (isConstant((*node)->left, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "see \"Abstract Algebra: Theory and Applications\"");

                optimizeRightNode(node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);
                break;
            }

            if (isConstant((*node)->right, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "i dunno really why");

                optimizeLeftNode(node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);
                break;
            }

            break;
        }
        case Subtraction: {
            if (isConstant((*node)->right, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "U WOT M8?");

                optimizeLeftNode(node);
                optimizedSubtree = true;

                dumpTreeToLatex(*node);

                END_EXPRESSION_CONVERSION(*node);
                break;
            }

            break;
        }
        case Multiplication: {
            if (isConstant((*node)->left, 1)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "many thanks to Evariste Galoi");

                optimizeRightNode(node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);
                break;
            }

            if (isConstant((*node)->right, 1)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "multiply by one son");

                optimizeLeftNode(node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);
                break;
            }

            break;
        }
        case Division:
        case Power: {
            if (isConstant((*node)->right, 1)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "we call node MATH power");

                optimizeLeftNode(node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);
                break;
            }
        }
    }

    return optimizedSubtree || optimizedLeftSubtree || optimizedRightSubtree;
}

bool Middleend::isConstant(const BinaryTree::Node *node, int constant)
{
    return (node->type == Constant) && (node->data == constant);
}

bool Middleend::optimizeEvaluableNodesRecursively(BinaryTree::Node *node)
{
    if (node == nullptr) return false;

    bool optimizedLeftSubtree = optimizeEvaluableNodesRecursively(node->left);
    bool optimizedRightSubtree = optimizeEvaluableNodesRecursively(node->right);

    if ((node->type != Operation) || ((node->left == nullptr) && (node->right->type != Constant)) || (node->left->type != Constant) ||
        (node->right->type != Constant)) {
        return optimizedLeftSubtree || optimizedRightSubtree;
    }

    switch (node->data) {
        case Addition: {
            BEGIN_EXPRESSION_CONVERSION(node, "trust me, just check rick astley's song");
            node->data = node->left->data + node->right->data;
            break;
        }
        case Subtraction: {
            BEGIN_EXPRESSION_CONVERSION(node, "look, i was gonna go easy on u");
            node->data = node->left->data - node->right->data;
            break;
        }
        case Multiplication: {
            BEGIN_EXPRESSION_CONVERSION(node, "i'm beginning to feel like a rap god");
            node->data = node->left->data * node->right->data;
            break;
        }
        case Division: {
            BEGIN_EXPRESSION_CONVERSION(node, "LMAO");
            node->data = node->left->data / node->right->data;
            break;
        }
        case Power: {
            BEGIN_EXPRESSION_CONVERSION(node, "OK, im out of node shit");
            node->data = std::pow(node->left->data, node->right->data);
            break;
        }
    }

    node->type = Constant;
    std::free(node->left);
    node->left = nullptr;
    std::free(node->right);
    node->right = nullptr;

    END_EXPRESSION_CONVERSION(node);

    return optimizedLeftSubtree || optimizedRightSubtree;
}

bool Middleend::optimizeSpecialConstantNodesRecursively(BinaryTree::Node **node)
{
    if (*node == nullptr) return false;

    bool optimizedLeftSubtree = optimizeSpecialConstantNodesRecursively(&(*node)->left);
    bool optimizedRightSubtree = optimizeSpecialConstantNodesRecursively(&(*node)->right);

    if ((*node)->type != Operation) return optimizedLeftSubtree || optimizedRightSubtree;

    bool optimizedSubtree = false;
    switch ((*node)->data) {
        case Multiplication: {
            if (isConstant((*node)->left, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "okay okay im literally baffled");

                zeroNode(*node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);

                break;
            }

            if (isConstant((*node)->right, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "zero divisor of the integers ring");

                zeroNode(*node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);

                break;
            }

            break;
        }
        case Division: {
            if (isConstant((*node)->left, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "i cant keep myself serious");

                zeroNode(*node);
                optimizedSubtree = true;

                END_EXPRESSION_CONVERSION(*node);

                break;
            }
        }
        case Power: {
            if (isConstant((*node)->right, 0)) {
                BEGIN_EXPRESSION_CONVERSION(*node, "you better tell me its worth it");

                optimizeLeftNode(node);
            }
        }
    }

    return optimizedSubtree || optimizedLeftSubtree || optimizedRightSubtree;
}

void Middleend::optimizeTree(BinaryTree::Node **root)
{
    while (true) {
        bool optimized = false;
        if (optimizeNeutralElementNodesRecursively(root)) optimized = true;
        if (optimizeEvaluableNodesRecursively(*root)) optimized = true;
        if (optimizeSpecialConstantNodesRecursively(root)) optimized = true;

        if (!optimized) break;
    }
}

void Middleend::optimizeLeftNode(BinaryTree::Node **node)
{
    std::free((*node)->right);
    (*node)->right = nullptr;
    auto optimizedNode = (*node)->left;
    std::free(*node);
    *node = optimizedNode;
}

void Middleend::optimizeRightNode(BinaryTree::Node **node)
{
    std::free((*node)->left);
    (*node)->left = nullptr;
    auto optimizedNode = (*node)->right;
    std::free(*node);
    *node = optimizedNode;
}

void Middleend::zeroNode(BinaryTree::Node *node)
{
    BinaryTree::deleteRecursively(&node->left);
    BinaryTree::deleteRecursively(&node->right);
    node->type = Constant;
    node->data = 0;
}

#endif
