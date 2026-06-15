#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insertAtBeginning(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return;
    }

    newNode->data = data;
    newNode->next = head;
    head = newNode;

    printf("Node with data %d inserted at beginning!\n", data);
}

void insertAtEnd(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        printf("Node with data %d inserted. (List was empty!)\n", data);
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    printf("Node with data %d inserted at the end.\n", data);
}

void insertAtPosition(int data, int pos)
{
    if (pos < 1)
    {
        printf("Invalid Position! Should start from 1!\n");
        return;
    }

    if (pos == 1)
    {
        insertAtBeginning(data);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    struct Node *temp = head;
    int i;

    for (i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    printf("Node with data %d inserted at position %d.\n", data, pos);
}

void deleteFromBeginning()
{
    if (head == NULL)
    {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    printf("Deleted node with data %d from beginning!\n", temp->data);
    free(temp);
}

void deleteFromEnd()
{
    if (head == NULL)
    {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    if (head->next == NULL)
    {
        printf("Node with data %d deleted from the end!\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    struct Node *prev;

    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    printf("Node with data %d deleted from the end!\n", temp->data);
    free(temp);
    prev->next = NULL;
}

void deleteFromPosition(int pos)
{
    if (head == NULL)
    {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    if (pos < 1)
    {
        printf("Invalid position! Position should be >= 1\n");
        return;
    }

    if (pos == 1)
    {
        deleteFromBeginning();
        return;
    }

    struct Node *temp = head;
    int i = 1;

    for (i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Position out of range!\n");
        return;
    }

    struct Node *delNode = temp->next;

    temp->next = delNode->next;
    printf("Node with data %d deleted from position %d.\n", delNode->data, pos);
    free(delNode);
}

void traverse()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    else
    {
        struct Node *temp = head;

        while (temp != NULL)
        {
            printf(" %d ->", temp->data);
            temp = temp->next;
        }

        printf(" NULL\n");
    }
}

void countNodes()
{
    int count = 0;

    struct Node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    printf("Total nodes in list: %d\n", count);
}

int main()
{
    int choice, data, pos;

    while (1)
    {
        printf("\n========================================\n");
        printf("   SINGLY LINKED LIST OPERATIONS\n");
        printf("========================================\n");
        printf("1.  Insert at Beginning\n");
        printf("2.  Insert at End\n");
        printf("3.  Insert at Position\n");
        printf("4.  Delete from Beginning\n");
        printf("5.  Delete from End\n");
        printf("6.  Delete from Position\n");
        printf("7.  Traverse/Display List\n");
        printf("8.  Count Nodes\n");
        printf("9.  Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            insertAtBeginning(data);
            break;

        case 2:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            insertAtEnd(data);
            break;

        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &pos);
            insertAtPosition(data, pos);
            break;

        case 4:
            deleteFromBeginning();
            break;

        case 5:
            deleteFromEnd();
            break;

        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            deleteFromPosition(pos);
            break;

        case 7:
            traverse();
            break;

        case 8:
            countNodes();
            break;

        case 9:
            printf("Exiting program. Goodbye!\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}