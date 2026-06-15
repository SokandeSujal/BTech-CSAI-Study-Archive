#include <stdio.h>
#include <stdlib.h>

// Threaded Binary Tree Node
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int lbit; // 0 = thread, 1 = child
    int rbit; // 0 = thread, 1 = child
} Node;

// Create new node
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->lbit = 0; // Initially threads
    newNode->rbit = 0;
    return newNode;
}

// Initialize dummy head node
Node *initializeHead()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->data = -999; // Dummy data
    head->lbit = 0;
    head->rbit = 1;
    head->left = head;
    head->right = head;
    return head;
}

// Insert node into threaded binary tree
void insert(Node *head, int data)
{
    Node *newNode = createNode(data);

    // If tree is empty (first node)
    if (head->lbit == 0)
    {
        head->lbit = 1;
        head->left = newNode;
        newNode->left = head;  // Thread to head
        newNode->right = head; // Thread to head
        printf("✓ Inserted %d as root\n", data);
        return;
    }

    // Tree is not empty - find position
    Node *curr = head->left;
    int inserted = 0;

    while (!inserted)
    {
        printf("Insert %d to left(0) or right(1) of %d? ", data, curr->data);
        int choice;
        scanf("%d", &choice);

        if (choice == 0)
        { // Insert LEFT
            if (curr->lbit == 0)
            {                               // No left child (thread exists)
                newNode->left = curr->left; // Copy thread
                newNode->right = curr;      // Thread to parent
                curr->left = newNode;       // Make it left child
                curr->lbit = 1;             // Now it's a child, not thread
                inserted = 1;
                printf("✓ Inserted %d to left of %d\n", data, curr->data);
            }
            else
            {
                curr = curr->left; // Move to left child
            }
        }
        else
        { // Insert RIGHT
            if (curr->rbit == 0)
            {                                 // No right child (thread exists)
                newNode->right = curr->right; // Copy thread
                newNode->left = curr;         // Thread to parent
                curr->right = newNode;        // Make it right child
                curr->rbit = 1;               // Now it's a child, not thread
                inserted = 1;
                printf("✓ Inserted %d to right of %d\n", data, curr->data);
            }
            else
            {
                curr = curr->right; // Move to right child
            }
        }
    }
}

// Find inorder successor (next node in inorder)
Node *inorderSuccessor(Node *node)
{
    // If right is a thread, just follow it
    if (node->rbit == 0)
    {
        return node->right;
    }

    // If right is a child, go right then leftmost
    node = node->right;
    while (node->lbit == 1)
    {
        node = node->left;
    }
    return node;
}

// Inorder traversal (Left -> Root -> Right)
void inorder(Node *head)
{
    if (head->lbit == 0)
    {
        printf("Tree is empty!\n");
        return;
    }

    // Find leftmost node (first in inorder)
    Node *curr = head->left;
    while (curr->lbit == 1)
    {
        curr = curr->left;
    }

    // Traverse using inorder successor
    printf("Inorder: ");
    while (curr != head)
    {
        printf("%d ", curr->data);
        curr = inorderSuccessor(curr);
    }
    printf("\n");
}

// Preorder traversal (Root -> Left -> Right)
void preorder(Node *head)
{
    if (head->lbit == 0)
    {
        printf("Tree is empty!\n");
        return;
    }

    Node *curr = head->left;
    printf("Preorder: ");

    while (curr != head)
    {
        printf("%d ", curr->data);

        // If left child exists, go left
        if (curr->lbit == 1)
        {
            curr = curr->left;
        }
        // Else if right child exists, go right
        else if (curr->rbit == 1)
        {
            curr = curr->right;
        }
        // Else follow thread
        else
        {
            // Move up using right thread until we find unvisited right subtree
            while (curr != head && curr->rbit == 0)
            {
                curr = curr->right;
            }
            // If not head, go to right child
            if (curr != head)
            {
                curr = curr->right;
            }
        }
    }
    printf("\n");
}

int main()
{
    Node *head = initializeHead();

    printf("========== THREADED BINARY TREE ==========\n\n");

    char choice;
    do
    {
        int data;
        printf("Enter data to insert: ");
        scanf("%d", &data);
        insert(head, data);

        printf("\nInsert more nodes? (y/n): ");
        scanf(" %c", &choice);
        printf("\n");
    } while (choice == 'y' || choice == 'Y');

    printf("\n========== TRAVERSALS ==========\n");
    inorder(head);
    preorder(head);

    return 0;
}