#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX][MAX];
int top = -1;

void push(char str[])
{
    if (top < MAX - 1)
    {
        top++;
        strcpy(stack[top], str);
    }
}

void pop(char str[])
{
    if (top >= 0)
    {
        strcpy(str, stack[top]);
        top--;
    }
}

void Postfix_To_Prefix(char E[])
{
    int l = strlen(E);
    char x;
    char op1[MAX], op2[MAX], E1[MAX];

    for (int i = 0; i < l; i++)
    {
        x = E[i];

        if (isalnum(x))
        {
            char temp[2];
            temp[0] = x;
            temp[1] = '\0';
            push(temp);
        }
        else
        {
            pop(op2);
            pop(op1);

            E1[0] = x;
            E1[1] = '\0';
            strcat(E1, op1);
            strcat(E1, op2);
            push(E1);
        }
    }

    printf("Prefix expression: %s\n", stack[top]);
}

int main()
{

    char E[MAX];
    printf("Enter a Postfix expression: ");
    scanf("%s", E);

    Postfix_To_Prefix(E);
    return 0;
}