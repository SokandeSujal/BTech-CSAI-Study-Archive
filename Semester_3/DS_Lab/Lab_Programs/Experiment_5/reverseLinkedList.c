#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

void insert(int data)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
    printf("Node with data %d inserted.\n", data);
}

void traverse()
{
    if (head == NULL)
    {
        printf("Linked List is Empty!\n");
        return;
    }
    else
    {
        struct node *temp = head;
        while (temp != NULL)
        {
            printf(" %d ->", temp->data);
            temp = temp->next;
        }

        printf(" NULL\n");
    }
}

void reverseLinkedList()
{

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    else
    {
        struct node *prev = NULL, *curr = head, *next = NULL;

        while (curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
}

int main()
{
    int data, choice;

    while (1)
    {
        printf("\nOperations On Linked List: \n");
        printf("1. Insert\n");
        printf("2. Traverse\n");
        printf("3. Reverse\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Element to insert: ");
            scanf("%d", &data);
            insert(data);
            break;
        case 2:
            traverse();
            break;
        case 3:
            printf("List Before Reverse: ");
            traverse();
            reverseLinkedList();
            printf("List After Reverse: ");
            traverse();
            break;
        case 4:
            printf("Exiting!...\n");
            exit(0);
            break;
        default:
            printf("Invalid Choice!\n");
            break;
        }
    }

    return 0;
}