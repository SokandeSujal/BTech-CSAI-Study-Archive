#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== TREE NODE STRUCTURE ==========
typedef struct Node
{
    char data[10];
    struct Node *left;
    struct Node *right;
} Node;

// ========== STACK FOR NON-RECURSIVE TRAVERSAL ==========
#define MAX 100
Node *stack[MAX];
int top = -1;

void push(Node *node)
{
    if (top < MAX - 1)
    {
        stack[++top] = node;
    }
}

Node *pop()
{
    if (top >= 0)
    {
        return stack[top--];
    }
    return NULL;
}

int isStackEmpty()
{
    return top == -1;
}

Node *stackTop()
{
    if (top >= 0)
    {
        return stack[top];
    }
    return NULL;
}

// ========== 1. CREATION OF BINARY TREE ==========
Node *createTree()
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    char data[10];
    char choice;

    printf("Enter data: ");
    scanf("%s", data);
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;

    // Ask for left child
    printf("Do you want to add left child of '%s'? (y/n): ", newNode->data);
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        printf("\n--- Creating left child of '%s' ---\n", newNode->data);
        newNode->left = createTree();
    }

    // Ask for right child
    printf("Do you want to add right child of '%s'? (y/n): ", newNode->data);
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        printf("\n--- Creating right child of '%s' ---\n", newNode->data);
        newNode->right = createTree();
    }

    return newNode;
}

// ========== 2. INORDER TRAVERSAL ==========

// Recursive
void inorder_recursive(Node *root)
{
    if (root != NULL)
    {
        inorder_recursive(root->left);
        printf("%s ", root->data);
        inorder_recursive(root->right);
    }
}

// Non-Recursive
void inorder_nonrecursive(Node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }

    Node *temp = root;
    top = -1; // Reset stack

    while (1)
    {
        // Go to leftmost node
        while (temp != NULL)
        {
            push(temp);
            temp = temp->left;
        }

        // If stack is empty, we're done
        if (isStackEmpty())
        {
            break;
        }

        // Pop and print
        temp = pop();
        printf("%s ", temp->data);

        // Move to right subtree
        temp = temp->right;
    }
}

// ========== 3. PREORDER TRAVERSAL ==========

// Recursive
void preorder_recursive(Node *root)
{
    if (root != NULL)
    {
        printf("%s ", root->data);
        preorder_recursive(root->left);
        preorder_recursive(root->right);
    }
}

// Non-Recursive
void preorder_nonrecursive(Node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }

    Node *temp = root;
    top = -1; // Reset stack

    while (1)
    {
        // Print and go left
        while (temp != NULL)
        {
            printf("%s ", temp->data);
            push(temp);
            temp = temp->left;
        }

        // If stack is empty, we're done
        if (isStackEmpty())
        {
            break;
        }

        // Pop and move to right
        temp = pop();
        temp = temp->right;
    }
}

// ========== 4. POSTORDER TRAVERSAL ==========

// Recursive
void postorder_recursive(Node *root)
{
    if (root != NULL)
    {
        postorder_recursive(root->left);
        postorder_recursive(root->right);
        printf("%s ", root->data);
    }
}

// Non-Recursive
void postorder_nonrecursive(Node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }

    Node *temp = root;
    top = -1; // Reset stack

    while (1)
    {
        // Go to leftmost node
        while (temp != NULL)
        {
            push(temp);
            temp = temp->left;
        }

        // Check if right child is NULL or already visited
        if (!isStackEmpty() && stackTop()->right == NULL)
        {
            temp = pop();
            printf("%s ", temp->data);
        }

        // Check if we just visited right child
        while (!isStackEmpty() && stackTop()->right == temp)
        {
            temp = pop();
            printf("%s ", temp->data);
        }

        // If stack is empty, we're done
        if (isStackEmpty())
        {
            break;
        }

        // Move to right child
        temp = stackTop()->right;
    }
}

// ========== MAIN FUNCTION ==========
int main()
{
    Node *root = NULL;
    int choice;

    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║     BINARY TREE - ASSIGNMENT 6            ║\n");
    printf("╚════════════════════════════════════════════╝\n");

    while (1)
    {
        printf("\n┌─────────────────────────────────────────┐\n");
        printf("│           MENU OPTIONS                  │\n");
        printf("├─────────────────────────────────────────┤\n");
        printf("│ 1. Create Binary Tree                   │\n");
        printf("│ 2. Inorder (Recursive)                  │\n");
        printf("│ 3. Inorder (Non-Recursive)              │\n");
        printf("│ 4. Preorder (Recursive)                 │\n");
        printf("│ 5. Preorder (Non-Recursive)             │\n");
        printf("│ 6. Postorder (Recursive)                │\n");
        printf("│ 7. Postorder (Non-Recursive)            │\n");
        printf("│ 8. Exit                                 │\n");
        printf("└─────────────────────────────────────────┘\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (root != NULL)
            {
                printf("\n✗ Tree already exists! Delete it first.\n");
            }
            else
            {
                printf("\n--- CREATING BINARY TREE ---\n");
                printf("--- Creating Root Node ---\n");
                root = createTree();
                printf("\n✓ Binary tree created successfully!\n");
            }
            break;

        case 2:
            printf("\n--- INORDER TRAVERSAL (RECURSIVE) ---\n");
            if (root == NULL)
            {
                printf("Tree is empty!\n");
            }
            else
            {
                printf("Output: ");
                inorder_recursive(root);
                printf("\n");
            }
            break;

        case 3:
            printf("\n--- INORDER TRAVERSAL (NON-RECURSIVE) ---\n");
            if (root == NULL)
            {
                printf("Tree is empty!\n");
            }
            else
            {
                printf("Output: ");
                inorder_nonrecursive(root);
                printf("\n");
            }
            break;

        case 4:
            printf("\n--- PREORDER TRAVERSAL (RECURSIVE) ---\n");
            if (root == NULL)
            {
                printf("Tree is empty!\n");
            }
            else
            {
                printf("Output: ");
                preorder_recursive(root);
                printf("\n");
            }
            break;

        case 5:
            printf("\n--- PREORDER TRAVERSAL (NON-RECURSIVE) ---\n");
            if (root == NULL)
            {
                printf("Tree is empty!\n");
            }
            else
            {
                printf("Output: ");
                preorder_nonrecursive(root);
                printf("\n");
            }
            break;

        case 6:
            printf("\n--- POSTORDER TRAVERSAL (RECURSIVE) ---\n");
            if (root == NULL)
            {
                printf("Tree is empty!\n");
            }
            else
            {
                printf("Output: ");
                postorder_recursive(root);
                printf("\n");
            }
            break;

        case 7:
            printf("\n--- POSTORDER TRAVERSAL (NON-RECURSIVE) ---\n");
            if (root == NULL)
            {
                printf("Tree is empty!\n");
            }
            else
            {
                printf("Output: ");
                postorder_nonrecursive(root);
                printf("\n");
            }
            break;

        case 8:
            printf("\n✓ Thank you for using Binary Tree!\n");
            printf("✓ Exiting...\n\n");
            exit(0);

        default:
            printf("\n✗ Invalid choice! Please try again.\n");
        }
    }

    return 0;
}