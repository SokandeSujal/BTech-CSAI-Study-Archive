#include <stdio.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

int isFull()
{
    if (rear == MAX - 1)
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
    if (front == -1 || rear == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(int data)
{
    if (isFull())
    {
        printf("Queue is full\n");
        return;
    }
    else
    {
        if (front == -1 || rear == -1)
        {
            front = 0;
            rear = 0;
            queue[rear] = data;
        }
        else
        {
            rear++;
            queue[rear] = data;
        }
    }
}

void dequeue()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        if (front == rear)
        {
            printf("Dequeued element: %d\n", queue[front]);
            front = -1;
            rear = -1;
        }
        else
        {
            printf("Dequeued element: %d\n", queue[front]);
            front++;
        }
    }
}

void display()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++)
        {
            printf("%d ", queue[i]);
        }
    }
}

int main()
{
    int choice, data;

    while (1)
    {

        printf("Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to enqueue: ");
            scanf("%d", &data);
            enqueue(data);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            printf("\n");
            break;
        case 4:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    }

    return 0;
}