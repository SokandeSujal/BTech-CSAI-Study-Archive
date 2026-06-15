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

int countNodes()
{
    int count = 0;
    struct node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void swapData(struct node *a, struct node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void bubbleSort()
{
    if (head == NULL || head->next == NULL)
    {
        printf("List is either empty OR only has one element!\n");
        return;
    }

    printf("UnSorted: ");
    traverse();

    int swapped;
    struct node *i, *j;

    for (i = head; i != NULL; i = i->next)
    {
        swapped = 0;
        for (j = head; j->next != NULL; j = j->next)
        {
            if (j->data > j->next->data)
            {
                swapData(j, j->next);
                swapped = 1;
            }
        }

        if (!swapped)
        {
            break;
        }
    }

    printf("Sorted: ");
    traverse();
}

int main()
{
    int data, choice;

    while (1)
    {
        printf("\nOperations On Linked List: \n");
        printf("1. Insert\n");
        printf("2. Traverse\n");
        printf("3. Sort\n");
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
            bubbleSort();
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