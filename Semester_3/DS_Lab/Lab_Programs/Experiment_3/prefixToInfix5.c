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

void Prefix_To_Infix(char E[])
{
    int l = strlen(E);
    char x;
    char op1[MAX], op2[MAX], E1[MAX];

    for (int i = l - 1; i >= 0; i--)
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
            pop(op1);
            pop(op2);

            strcpy(E1, "(");
            strcat(E1, op1);

            char op[2];
            op[0] = x;
            op[1] = '\0';
            strcat(E1, op);

            strcat(E1, op2);
            strcat(E1, ")");
            push(E1);
        }
    }

    printf("Infix Expression: %s\n", stack[top]);
}

int main()
{
    char E[MAX];
    printf("Enter a Prefix Expression: ");
    scanf("%s", E);

    Prefix_To_Infix(E);

    return 0;
}