#include <stdio.h>

#define MAX 5
int circularQueue[MAX];
int front = -1, rear = -1;

int isFull()
{
    if ((rear + 1) % MAX == front)
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
    if (front == -1 && rear == -1)
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
        printf("Queue is full!\n");
        return;
    }
    else
    {
        if (front == -1 || rear == -1)
        {
            front = 0;
            rear = 0;
            circularQueue[rear] = data;
        }
        else
        {
            rear = (rear + 1) % MAX;
            circularQueue[rear] = data;
        }
    }
}

void dequeue()
{
    if (isEmpty())
    {
        printf("Queue is Empty!\n");
        return;
    }
    else
    {
        if (front == rear)
        {
            printf("Dequeued Element: %d", circularQueue[front]);
            front = -1;
            rear = -1;
        }
        else
        {
            printf("Dequeued Element: %d", circularQueue[front]);
            front = (front + 1) % MAX;
        }
    }
}

void display()
{
    if (isEmpty())
    {
        printf("Queue is Empty!\n");
        return;
    }
    else
    {
        printf("Queue Elements: ");
        int i = front;
        while (i != rear)
        {
            printf("%d ", circularQueue[i]);
            i = (i + 1) % MAX;
        }
        printf("%d ", circularQueue[rear]);
        printf("\n");
    }
}

int main()
{

    int choice, data;

    while (1)
    {

        printf("\nCircular Queue Operations: \n");
        printf("1.Enqueue\n");
        printf("2.Dnqueue\n");
        printf("3.Display\n");
        printf("4.Exit\n");

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
            break;
        case 4:
            printf("Exiting!...\n");
            return 0;
        default:
            printf("Invalid Choice!\n");
            break;
        }
    }

    return 0;
}
