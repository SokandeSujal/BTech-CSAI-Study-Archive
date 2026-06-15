#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head1 = NULL;
struct node *head2 = NULL;
struct node *mergeHead = NULL;

void insert(struct node **head, int data)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("Node with data %d inserted.\n", data);
}

void traverse(struct node *head)
{
    if (head == NULL)
    {
        printf("List is Empty!\n");
        return;
    }

    printf("Linked List: ");
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void mergeLists()
{
    if (head1 == NULL)
    {
        printf("List 1 empty, Insert first!\n");
        return;
    }
    else if (head2 == NULL)
    {
        printf("List 2 empty, Insert first!\n");
        return;
    }
    else
    {
        mergeHead = head1;
        struct node *temp = mergeHead;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = head2;
        printf("Merge completed!\n");
    }
}

void sortList(struct node *head)
{
    if (head == NULL || head->next == NULL)
    {
        printf("List is empty or only has one element!\n");
        return;
    }

    struct node *i, *j;
    for (i = head; i != NULL; i = i->next)
    {
        for (j = head; j->next != NULL; j = j->next)
        {
            if (j->data > j->next->data)
            {
                int temp = j->data;
                j->data = j->next->data;
                j->next->data = temp;
            }
        }
    }

    printf("List sorted successfully!\n");
}

int main()
{
    int data, choice, subChoice;

    while (1)
    {
        printf("\nLinked List Operations: \n");
        printf("1. Insert\n");
        printf("2. Traverse\n");
        printf("3. Merge\n");
        printf("4. Traverse Merged List\n");
        printf("5. Sort\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to insert: ");
            scanf("%d", &data);

            printf("Insert in List 1 or 2: ");
            scanf("%d", &subChoice);
            if (subChoice == 1)
            {
                insert(&head1, data);
            }
            else
            {
                insert(&head2, data);
            }
            break;

        case 2:
            printf("Traverse List 1 or 2: ");
            scanf("%d", &subChoice);

            if (subChoice == 1)
            {
                traverse(head1);
            }
            else
            {
                traverse(head2);
            }
            break;

        case 3:
            mergeLists();
            break;

        case 4:
            printf("Merged ");
            traverse(mergeHead);
            break;

        case 5:
            printf("Sort List 1, 2 or 3 (Merged List): ");
            scanf("%d", &subChoice);

            if (subChoice == 1)
                sortList(head1);
            else if (subChoice == 2)
                sortList(head2);
            else
                sortList(mergeHead);
            break;

        case 6:
            printf("Exiting program...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
