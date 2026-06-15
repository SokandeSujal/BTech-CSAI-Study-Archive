// Tree Traversal in C based on left right child representation Non Recursive

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct StackNode
{
    struct Node *treeNode;
    struct StackNode *next;
};

struct StackNode *createStackNode(struct Node *treeNode)
{
    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    stackNode->treeNode = treeNode;
    stackNode->next = NULL;
    return stackNode;
}

struct StackNode *push(struct StackNode *top, struct Node *treeNode)
{
    struct StackNode *stackNode = createStackNode(treeNode);
    stackNode->next = top;
    return stackNode;
}

struct StackNode *pop(struct StackNode **top)
{
    if (*top == NULL)
        return NULL;
    struct StackNode *temp = *top;
    *top = (*top)->next;
    return temp;
}

int isEmpty(struct StackNode *top)
{
    return top == NULL;
}

void preOrder(struct Node *root)
{
    if (root == NULL)
        return;

    struct StackNode *stack = NULL;
    stack = push(stack, root);

    while (!isEmpty(stack))
    {
        struct StackNode *stackNode = pop(&stack);
        struct Node *currentNode = stackNode->treeNode;
        free(stackNode);

        printf("%d ", currentNode->data);

        if (currentNode->right)
            stack = push(stack, currentNode->right);
        if (currentNode->left)
            stack = push(stack, currentNode->left);
    }
}

void inOrder(struct Node *root)
{
    struct StackNode *stack = NULL;
    struct Node *currentNode = root;

    while (currentNode != NULL || !isEmpty(stack))
    {
        while (currentNode != NULL)
        {
            stack = push(stack, currentNode);
            currentNode = currentNode->left;
        }

        struct StackNode *stackNode = pop(&stack);
        currentNode = stackNode->treeNode;
        free(stackNode);

        printf("%d ", currentNode->data);
        currentNode = currentNode->right;
    }
}

void postOrder(struct Node *root)
{
    if (root == NULL)
        return;

    struct StackNode *stack1 = NULL;
    struct StackNode *stack2 = NULL;

    stack1 = push(stack1, root);

    while (!isEmpty(stack1))
    {
        struct StackNode *stackNode = pop(&stack1);
        struct Node *currentNode = stackNode->treeNode;
        free(stackNode);

        stack2 = push(stack2, currentNode);

        if (currentNode->left)
            stack1 = push(stack1, currentNode->left);
        if (currentNode->right)
            stack1 = push(stack1, currentNode->right);
    }

    while (!isEmpty(stack2))
    {
        struct StackNode *stackNode = pop(&stack2);
        struct Node *currentNode = stackNode->treeNode;
        free(stackNode);
        printf("%d ", currentNode->data);
    }
}

int main()
{
    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Pre-order Traversal: ");
    preOrder(root);
    printf("\n");

    printf("In-order Traversal: ");
    inOrder(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postOrder(root);
    printf("\n");

    return 0;
}