#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
    char data[10];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Stack for non-recursive traversal
#define STACK_SIZE 100
TreeNode *stack[STACK_SIZE];
int top = -1;

int isStackEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

int isStackFull()
{
    if (top == STACK_SIZE - 1)
        return 1;
    else
        return 0;
}

void push(TreeNode *node)
{
    if (node == NULL)
    {
        printf("Cannot push NULL node onto the stack!\n");
        return;
    }

    if (isStackFull())
    {
        printf("Stack Overflow!\n");
        return;
    }
    else
    {
        top++;
        stack[top] = node;
    }
}

TreeNode *pop()
{
    if (isStackEmpty())
    {
        printf("Stack underflow!\n");
        return;
    }
    else
    {
        return stack[top--];
    }
}

TreeNode *stackTop()
{
    if (isStackEmpty())
    {
        return NULL;
    }
    return stack[top];
}

// Queue for BFS
#define QUEUE_SIZE 100
TreeNode *queue[QUEUE_SIZE];
int front = -1, rear = -1;

int isQueueEmpty()
{
    if (front == -1 || rear == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isQueueFull()
{
    if (rear == QUEUE_SIZE - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(TreeNode *node)
{
    if (isQueueFull())
    {
        printf("Queue overflow\n");
        return;
    }
    else
    {
        if (front == -1 || rear == -1)
        {
            front = rear = 0;
        }
        else
        {
            rear++;
            queue[rear] = node;
        }
    }
}

TreeNode *dequeue()
{
    if (isQueueEmpty())
    {
        printf("Queue underflow\n");
        return NULL;
    }
    TreeNode *node = queue[front];
    front++;
    if (front > rear)
    {
        front = rear = -1;
    }
    return node;
}

// ========== TREE CREATION ==========

// Recursive creation
TreeNode *create_r(TreeNode *root)
{
    TreeNode *temp = root;
    char ch;
    TreeNode *curr;

    printf("Do you want to add left child of %s data? (y/n)", temp->data);
    scanf("%c", &ch);

    if (ch == 'y' || ch == "Y")
    {
        curr = (TreeNode *)malloc(sizeof(TreeNode));
        printf("Enter data for left child: ");
        scanf("%s", curr->data);
        curr->left = NULL;
        curr->right = NULL;
        temp->left = curr;
        create_r(curr);
    }

    printf("Do you want to right left child of %s data? (y/n)", temp->data);
    scanf("%c", &ch);

    if (ch == 'y' || ch == "Y")
    {
        curr = (TreeNode *)malloc(sizeof(TreeNode));
        printf("Enter data for left child: ");
        scanf("%s", curr->data);
        curr->left = NULL;
        curr->right = NULL;
        temp->right = curr;
        create_r(curr);
    }

    return root;
}

// Non Recursive
TreeNode *create_nr(TreeNode *root)
{
    TreeNode *temp, *curr;
    char ch, direction;
    int flag;

    do
    {
        temp = root;
        flag = 0;

        curr = (TreeNode *)malloc(sizeof(TreeNode));
        printf("\nEnter data for new node: ");
        scanf("%s", curr->data);
        curr->left = NULL;
        curr->right = NULL;

        while (flag == 0)
        {
            printf("Add node to left(l) or right(r) of %s: ", temp->data);
            scanf("%c", &direction);

            if (direction == 'l' || direction == 'L')
            {
                if (temp->left == NULL)
                {
                    temp->left = curr;
                    flag = 1;
                }
                else
                {
                    temp = temp->left;
                }
            }

            if (direction == 'r' || direction == 'R')
            {
                if (temp->right == NULL)
                {
                    temp->right = curr;
                    flag = 1;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }

        printf("Do you want to continue: (y/n)");
        scanf("%c", &ch);

    } while (ch == 'y' || ch == "Y");

    return root;
}

// ========== INORDER TRAVERSAL ==========

// Recursive
void inorder_r(TreeNode *temp)
{
    if (temp != NULL)
    {
        inorder_r(temp->left);
        printf("%s", temp->data);
        inorder_r(temp->right);
    }
}

void inorder_nr(TreeNode *root)
{
    TreeNode *temp = root;
    top = -1;

    while (1)
    {
        while (temp != NULL)
        {
            push(temp);
            temp = temp->left;
        }

        if (isStackEmpty())
        {
            break;
        }

        temp = pop();
        printf("%s", temp->data);
        temp = temp->right;
    }
}

// ========== PREORDER TRAVERSAL ==========

// Recursive
void preorder_r(TreeNode *temp)
{
    if (temp != NULL)
    {
        printf("%s ", temp->data);
        preorder_r(temp->left);
        preorder_r(temp->right);
    }
}

// Non Recursive
void preorder_nr(TreeNode *root)
{
    TreeNode *temp = root;
    top = -1;

    while (1)
    {
        while (temp != NULL)
        {
            printf("%s ", temp->data);
            push(temp);
            temp = temp->left;
        }

        if (isStackEmpty())
        {
            break;
        }

        temp = pop();
        temp = temp->right;
    }
}

// ========== POSTORDER TRAVERSAL ==========

// Recursive
void postorder_r(TreeNode *temp)
{
    if (temp != NULL)
    {
        postorder_r(temp->left);
        postorder_r(temp->right);
        printf("%s", temp->data);
    }
}

// Non Recursive
void postorder_nr(TreeNode *root)
{
    TreeNode *temp = root;
    top = -1;

    while (1)
    {
        while (temp != NULL)
        {
            push(temp);
            temp = temp->left;
        }

        if (!isStackEmpty() && stackTop()->right == NULL)
        {
            temp = pop();
            printf("%s ", temp->data);
        }

        if (isStackEmpty())
        {
            break;
        }

        temp = temp->right;
    }
}

// ========== BREADTH FIRST SEARCH (LEVEL ORDER) ==========
void bfs(TreeNode *root)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }

    TreeNode *temp = root;
    front = rear = -1;

    enqueue(temp);

    while (!isQueueEmpty())
    {
        temp = dequeue();
        printf("%s", temp->data);

        if (temp->left != NULL)
        {
            enqueue(temp->left);
        }

        if (temp->right != NULL)
        {
            enqueue(temp->right);
        }
    }
}

// ========== COPY BINARY TREE ==========

// Recursive
TreeNode *copy_r(TreeNode *root)
{
    TreeNode *temp = NULL;

    if (root != NULL)
    {
        temp = (TreeNode *)malloc(sizeof(TreeNode));
        strcpy(temp->data, root->data);
        temp->left = copy_r(root->left);
        temp->right = copy_r(root->right);
    }

    return temp;
}

// Non Recursive
TreeNode *copy_nr(TreeNode *root2)
{
    if (root2 == NULL)
        return NULL;

    TreeNode *root1 = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(root1->data, root2->data);
    root1->left = NULL;
    root1->right = NULL;

    TreeNode *temp1 = root1, *temp2 = root2;
    top = -1;

    TreeNode *stack2[STACK_SIZE];
    int top2 = -1;

    while (1)
    {
        while (temp2 != NULL)
        {
            if (temp2->left != NULL)
            {
                temp1->left = (TreeNode *)malloc(sizeof(TreeNode *));
                strcpy(temp1->left->data, temp2->left->data);
                temp1->left->left = NULL;
                temp1->left->right = NULL;
            }

            if (temp2->right != NULL)
            {
                temp1->right = (TreeNode *)malloc(sizeof(TreeNode *));
                strcpy(temp1->right->data, temp2->right->data);
                temp1->right->left = NULL;
                temp1->right->right = NULL;
            }

            top++;
            stack[top] = temp1;

            top2++;
            stack2[top2] = temp2;

            temp1 = temp1->left;
            temp2 = temp2->left;
        }

        if (top == -1)
            break;

        temp1 = stack[top];
        top--;
        temp2 = stack2[top2];
        top2--;

        temp1 = temp1->right;
        temp2 = temp2->right;
    }

    return root1;
}

// ========== MIRROR BINARY TREE ==========

// Recursive
void mirror_r(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    // Swap left and right
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    if (root->left != NULL)
    {
        mirror_r(root->left);
    }

    if (root->right != NULL)
    {
        mirror_r(root->right);
    }
}

// Non-recursive (using queue/BFS)
void mirror_nr(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    TreeNode *temp = root;
    front = rear = -1;

    enqueue(temp);

    while (!isQueueEmpty())
    {
        temp = dequeue();

        TreeNode *t = temp->left;
        temp->left = temp->right;
        temp->right = t;

        if (temp->left != NULL)
        {
            enqueue(temp->left);
        }

        if (temp->right != NULL)
        {
            enqueue(temp->right);
        }
    }
}

// ========== DELETE A SPECIFIC NODE ==========

// Find deepest rightmost node
TreeNode *findDeepest(TreeNode *root)
{
    if (root == NULL)
        return NULL;

    TreeNode *temp = root;
    front = rear = -1; // Reset queue
    TreeNode *deepest = NULL;

    enqueue(temp);

    while (!isQueueEmpty())
    {
        deepest = dequeue();

        if (deepest->left != NULL)
        {
            enqueue(deepest->left);
        }

        if (deepest->right != NULL)
        {
            enqueue(deepest->right);
        }
    }
    return deepest;
}

void deleteDeepest(TreeNode *root, TreeNode *delNode)
{
    if (root == NULL)
        return;

    TreeNode *temp = root;
    front = rear = -1; // Reset queue

    enqueue(temp);

    while (!isQueueEmpty())
    {
        temp = dequeue();

        if (temp == delNode)
        {
            free(temp);
            return;
        }

        if (temp->left != NULL)
        {
            if (temp->left == delNode)
            {
                free(temp->left);
                temp->left = NULL;
                return;
            }
            else
            {
                enqueue(temp->left);
            }
        }
        if (temp->right != NULL)
        {
            if (temp->right == delNode)
            {
                free(temp->right);
                temp->right = NULL;
                return;
            }
            else
            {
                enqueue(temp->right);
            }
        }
    }
}

TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return NULL;
    }

    if (root->left == NULL && root->right == NULL)
    {
        printf("Deleting root node (only node): %d\n", root->data);
        free(root);
        return NULL;
    }

    TreeNode *temp = NULL;
    TreeNode *keyNode = NULL;
    TreeNode *deepest = NULL;

    front = rear = -1;
    enqueue(root);

    while (!isQueueEmpty())
    {
        temp = dequeue();

        if (temp->data == key)
        {
            keyNode = temp;
        }

        if (temp->left != NULL)
            enqueue(temp->left);
        if (temp->right != NULL)
            enqueue(temp->right);
    }

    if (keyNode == NULL)
    {
        printf("Node '%d' not found!\n", key);
        return root;
    }

    deepest = findDeepest(root);
    printf("Deleting node '%d' and replacing with deepest node '%d'\n", keyNode->data, deepest->data);

    // keyNode->data = deepest->data;
    deleteDeepest(root, deepest);

    return root;
}

// ========== DEPTH OF TREE ==========

// Recursive
int depth_r(TreeNode *root)
{
    int t1 = 0;
    int t2 = 0;

    if (root == NULL)
    {
        return 0;
    }
    else
    {
        t1 = depth_r(root->left);
        t2 = depth_r(root->right);

        if (t1 > t2)
        {
            return ++t1;
        }
        else
        {
            return ++t2;
        }
    }
}

// ========== COUNT NODES ==========

int countNodes(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main()
{
    TreeNode *root = NULL, *copy = NULL;
    int choice;
    char cont;

    root = (TreeNode *)malloc(sizeof(TreeNode));
    printf("Enter data for root: ");
    scanf("%s", root->data);
    root->left = root->right = NULL;

    do
    {
        printf("\n==== BINARY TREE MENU ====\n");
        printf("1. Create Tree (Recursive)\n");
        printf("2. Create Tree (Non-Recursive)\n");
        printf("3. Inorder Traversal (Recursive)\n");
        printf("4. Inorder Traversal (Non-Recursive)\n");
        printf("5. Preorder Traversal (Recursive)\n");
        printf("6. Preorder Traversal (Non-Recursive)\n");
        printf("7. Postorder Traversal (Recursive)\n");
        printf("8. BFS Traversal (Level Order)\n");
        printf("9. Copy Tree (Recursive)\n");
        printf("10. Mirror Tree (Recursive)\n");
        printf("11. Count Nodes\n");
        printf("12. Depth of Tree\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice)
        {
        case 1:
            create_r(root);
            break;

        case 2:
            create_nr(root);
            break;

        case 3:
            printf("Inorder (Recursive): ");
            inorder_r(root);
            printf("\n");
            break;

        case 4:
            printf("Inorder (Non-Recursive): ");
            inorder_nr(root);
            printf("\n");
            break;

        case 5:
            printf("Preorder (Recursive): ");
            preorder_r(root);
            printf("\n");
            break;

        case 6:
            printf("Preorder (Non-Recursive): ");
            preorder_nr(root);
            printf("\n");
            break;

        case 7:
            printf("Postorder (Recursive): ");
            postorder_r(root);
            printf("\n");
            break;

        case 8:
            printf("BFS (Level Order): ");
            bfs(root);
            printf("\n");
            break;

        case 9:
            copy = copy_r(root);
            printf("Tree copied (Recursive). Inorder of copy: ");
            inorder_r(copy);
            printf("\n");
            break;

        case 10:
            mirror_r(root);
            printf("Tree mirrored. Inorder after mirroring: ");
            inorder_r(root);
            printf("\n");
            break;

        case 11:
            printf("Total nodes = %d\n", countNodes(root));
            break;

        case 12:
            printf("Depth of tree = %d\n", depth_r(root));
            break;

        case 13:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');

    return 0;
}
