#include <stdio.h>

#define SIZE 10

int stack[SIZE];
int top = -1;

int isFull()
{
    if (top == SIZE - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty()
{
    if (top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(int value)
{
    if (isFull())
    {
        printf("Stack Overflow!\n");
        return;
    }
    else
    {
        top++;
        stack[top] = value;
        printf("Pushed %d to stack.\n", value);
    }
}

int pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow!\n");
        return -1;
    }
    else
    {
        int value = stack[top];
        top--;
        printf("Popped %d from stack.\n", value);
        return value;
    }
}

void peek()
{
    if (isEmpty())
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Top element is %d\n", stack[top]);
    }
}

void display()
{
    if (isEmpty())
    {
        printf("Stack is Emppty!\n");
    }
    else
    {
        printf("Stack elements are:\n");
        for (int i = top; i >= 0; i--)
        {
            if (top != 0)
            {
                printf("| %d |\n", stack[i]);
            }
            else
            {
                printf("|_%d_|\n", stack[i]);
            }
        }
    }
}

int main()
{
    int choice, value;
    while (1)
    {
        printf("\nStack Operations Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}