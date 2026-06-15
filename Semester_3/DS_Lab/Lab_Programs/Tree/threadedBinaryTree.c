#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tbtNode
{
    int data;
    struct tbtNode *left;
    struct tbtNode *right;
    int lbit;
    int rbit;
};

struct tbtNode *inordersuccessor(struct tbtNode *temp);

struct tbtNode *create(struct tbtNode *head)
{
    struct tbtNode *root = (struct tbtNode *)malloc(sizeof(struct tbtNode));
    printf("Enter data (-1 to stop): ");
    int data;
    scanf("%d", &data);
    root->data = data;
    head->lbit = 1;
    root->left = head;
    root->right = head;
    root->lbit = 0;
    root->rbit = 0;
    head->left = root;

    char ch = 'y';
    do
    {
        int flag = 0;
        struct tbtNode *temp = root;
        struct tbtNode *curr = (struct tbtNode *)malloc(sizeof(struct tbtNode));
        printf("Enter data (-1 to stop): ");
        scanf("%d", &data);
        if (data == -1)
        {
            break;
        }
        curr->data = data;
        curr->lbit = 0;
        curr->rbit = 0;

        while (flag == 0)
        {
            int choice;
            printf("Insert to left(0) or right(1) of %d: ", temp->data);
            scanf("%d", &choice);

            if (choice == 0)
            {
                if (temp->lbit == 0)
                {
                    curr->left = temp->left;
                    curr->right = temp;
                    temp->left = curr;
                    temp->lbit = 1;
                    flag = 1;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if (temp->rbit == 0)
                {
                    curr->right = temp->right;
                    curr->left = temp;
                    temp->right = curr;
                    temp->rbit = 1;
                    flag = 1;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
        printf("Do you want to continue inserting nodes? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
    return head;
}

void inorder(struct tbtNode *head)
{
    struct tbtNode *temp = head->left;

    while (temp->lbit == 1)
    {
        temp = temp->left;
    }

    while (temp != head)
    {
        printf("%d ", temp->data);
        temp = inordersuccessor(temp);
    }
    printf("\n");
}

struct tbtNode *inordersuccessor(struct tbtNode *temp)
{
    struct tbtNode *x = temp->right;
    if (temp->rbit == 1)
    {
        while (x->lbit == 1)
        {
            x = x->left;
        }
    }
    return x;
}

void preorder(struct tbtNode *head)
{
    struct tbtNode *temp = head->left;

    while (temp != head)
    {
        printf("%d ", temp->data);

        if (temp->lbit == 1)
        {
            temp = temp->left;
        }
        else if (temp->rbit == 1)
        {
            temp = temp->right;
        }
        else
        {
            while (temp != head && temp->rbit == 0)
            {
                temp = temp->right;
            }

            if (temp != head)
            {
                temp = temp->right;
            }
        }
    }
    printf("\n");
}

int main()
{
    struct tbtNode *head;
    head = (struct tbtNode *)malloc(sizeof(struct tbtNode));
    head->rbit = 1;
    head->lbit = 0;
    head->left = head->right = head;
    create(head);
    printf("Inorder Traversal: ");
    inorder(head);
    printf("Preorder Traversal: ");
    preorder(head);
    return 0;
}
