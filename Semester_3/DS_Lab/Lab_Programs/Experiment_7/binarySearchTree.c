#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char keyword[50];
    char meaning[50];
    struct Node *left;
    struct Node *right;
} Node;

// Queue
#define MAX 100
Node *queue[MAX];
int front = -1, rear = -1;

void enqueue(Node *node)
{
    if (rear == MAX - 1)
    {
        return;
    }

    if (front == -1 || rear == -1)
    {
        front = rear = 0;
        queue[rear] = node;
    }
    else
    {
        rear++;
        queue[rear] = node;
    }
}

Node *dequeue()
{
    if (front == -1)
    {
        return;
    }
    else
    {
        if (front == rear)
        {
            Node *node = queue[front];
            front = rear = -1;
            return node;
        }
        else
        {
            Node *node = queue[front];
            front++;
            return node;
        }
    }
}

int isEmpty()
{
    if (front == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ========== 1. INSERT A KEYWORD ==========
Node *insert(Node *root, char keyword[], char meaning[])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->keyword, keyword);
    strcpy(newNode->meaning, meaning);

    newNode->left = newNode->right = NULL;

    // If tree is empty, return new node as root
    if (root == NULL)
    {
        printf("✓ '%s' inserted as root\n", keyword);
        return newNode;
    }

    Node *current = root;
    Node *parent = NULL;

    while (current != NULL)
    {
        parent = current;

        if (strcmp(keyword, current->keyword) < 0)
        {
            current = current->left;
        }
        else if (strcmp(keyword, current->keyword) > 0)
        {
            current = current->right;
        }
        else
        {
            printf("✗ Keyword '%s' already exists!\n", keyword);
            free(newNode);
            return root;
        }
    }

    if (strcmp(keyword, parent->keyword) < 0)
    {
        parent->left = newNode;
        printf("✓ '%s' inserted to the left of '%s'\n", keyword, parent->keyword);
    }
    else
    {
        parent->right = newNode;
        printf("%s inserted to the right of %s\n", keyword, parent->keyword);
    }

    return root;
}

Node *deleteNode(Node *root, char keyword[])
{
    if (root == NULL)
    {
        printf("Tree is empty!");
        return NULL;
    }

    Node *parent = NULL;
    Node *current = root;

    while (current != NULL && strcmp(current->keyword, keyword) != 0)
    {
        parent = current;

        if (strcmp(keyword, current->keyword) < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (current == NULL)
    {
        printf("✗ Keyword '%s' not found!\n", keyword);
        return root;
    }

    printf("✓ Deleting '%s'...\n", current->keyword);

    // Case 1:
    if (current->left == NULL && current->right == NULL)
    {
        if (current == root)
        {
            free(root);
            return NULL;
        }
        if (parent->left == current)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }

        free(current);
    }

    // Case 2 non leaf node
    else if (current != root)
    {
        // subcase 2a->only right
        if (current->left == NULL)
        {
            if (parent->left == current)
            {
                parent->left = current->right;
            }
            else
            {
                parent->right = current->left;
            }
            free(current);
        }
        else if (current->right == NULL)
        {
            if (parent->left == current)
            {
                parent->left = current->left;
            }
            else
            {
                parent->right = current->left;
            }
            free(current);
        }
        else
        {
            Node *successor = current->right;

            while (successor->left != NULL)
            {
                successor = successor->left;
            }

            successor->left = current->left;
            if (parent->left == current)
            {
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }
            free(current);
        }
    }
    else
    {
        if (current->left == NULL)
        {
            root = current->right;
            free(current);
        }
        else if (current->right == NULL)
        {
            root = current->left;
            free(current);
        }
        else
        {
            Node *successor = current->right;

            while (successor->left != NULL)
            {
                successor = successor->left;
            }

            successor->left = current->left;

            root = current->right;
            free(current);
        }
    }

    printf("✓ Deleted successfully!\n");
    return root;
}

void displayLevelWise(Node *root)
{
    if (root == NULL)
    {
        printf("Dictionary is empty!\n");
        return;
    }

    front = rear = -1;
    enqueue(root);
    enqueue(NULL); // Level marker

    int level = 0;
    printf("\n========== LEVEL-WISE DISPLAY ==========\n");
    printf("Level %d: ", level);

    while (!isEmpty())
    {
        Node *current = dequeue();
        if (current == NULL)
        {
            printf("\n");
            if (!isEmpty())
            {                                // If queue still has nodes
                level++;                     // Increment level counter
                printf("Level %d: ", level); // Print new level label
                enqueue(NULL);               // Add marker for NEXT level
            }
        }
        else
        {
            printf("[%s] ", current->keyword);
            if (current->left != NULL)
            {
                enqueue(current->left); // Add left child to queue
            }
            if (current->right != NULL)
            {
                enqueue(current->right); // Add right child to queue
            }
        }
    }
    printf("========================================\n");
}

// ========== 4. CREATE MIRROR IMAGE ==========
void mirror(Node *root)
{
    if (root == NULL)
        return;

    // Swap left and right children
    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Mirror left and right subtrees
    mirror(root->left);
    mirror(root->right);
}

// ========== 5. COPY DICTIONARY ==========
Node *copy(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    // Create new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->keyword, root->keyword);
    strcpy(newNode->meaning, root->meaning);

    // Copy left and right subtrees
    newNode->left = copy(root->left);
    newNode->right = copy(root->right);

    return newNode;
}

// ========== HELPER: DISPLAY SORTED (INORDER) ==========
void displaySorted(Node *root)
{
    if (root != NULL)
    {
        displaySorted(root->left);
        printf("%-20s : %s\n", root->keyword, root->meaning);
        displaySorted(root->right);
    }
}

int main()
{
    Node *root = NULL;
    Node *copiedRoot = NULL;
    int choice;
    char keyword[50], meaning[50];

    while (1)
    {
        printf("\n====== DICTIONARY MENU ======\n");
        printf("1. Insert a keyword\n");
        printf("2. Delete a keyword\n");
        printf("3. Display dictionary (level-wise)\n");
        printf("4. Display dictionary (sorted)\n");
        printf("5. Create mirror of dictionary\n");
        printf("6. Copy dictionary\n");
        printf("7. Display copied dictionary (sorted)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice)
        {
        case 1:
            printf("Enter Keyword: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, '\n')] = "\0";

            printf("Enter meaning: ");
            fgets(meaning, sizeof(meaning), stdin);
            meaning[strcspn(meaning, "\n")] = '\0'; // Remove newline

            root = insert(root, keyword, meaning);
            break;

        case 2:
            if (root == NULL)
            {
                printf("Dictionary is empty!\n");
                break;
            }
            printf("Enter keyword to delete: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = '\0';

            root = deleteNode(root, keyword);
            break;

        case 3:
            displayLevelWise(root);
            break;

        case 4:
            if (root == NULL)
                printf("Dictionary is empty!\n");
            else
            {
                printf("\n===== SORTED DICTIONARY =====\n");
                displaySorted(root);
                printf("=============================\n");
            }
            break;

        case 5:
            if (root == NULL)
            {
                printf("Dictionary is empty!\n");
            }
            else
            {
                mirror(root);
                printf("Mirror image created!\n");
            }
            break;

        case 6:
            copiedRoot = copy(root);
            printf("Dictionary copied successfully!\n");
            break;

        case 7:
            if (copiedRoot == NULL)
                printf("Copied dictionary is empty!\n");
            else
            {
                printf("\n===== COPIED DICTIONARY (SORTED) =====\n");
                displaySorted(copiedRoot);
                printf("======================================\n");
            }
            break;

        case 0:
            printf("Exiting program. Goodbye!\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
