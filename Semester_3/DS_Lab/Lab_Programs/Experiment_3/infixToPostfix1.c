#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stk[MAX];
int top = -1;

void push(char ch)
{
    if (top < MAX - 1)
    {
        top++;
        stk[top] = ch;
    }
}

char pop()
{
    if (top >= 0)
        return stk[top--];
    return '\0';
}

int icp(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '^')
        return 4;
    else if (ch == '(')
        return 5;
    else
        return 0;
}

int isp(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '^')
        return 3;
    else
        return 0;
}

void infixToPostfix(char inexp[], char postexp[])
{
    int k = 0, i = 0;
    char tkn;

    tkn = inexp[i];

    while (tkn != '\0')
    {
        if (isalnum(tkn))
        {
            postexp[k] = tkn;
            k++;
        }
        else
        {
            if (tkn == '(')
            {
                push(tkn);
            }
            else
            {
                if (tkn == ')')
                {
                    while ((tkn = pop()) != '(')
                    {
                        postexp[k] = tkn;
                        k++;
                    }
                }
                else
                {
                    while (top >= 0 && isp(stk[top]) >= icp(tkn))
                    {
                        postexp[k] = pop();
                        k++;
                    }
                    push(tkn);
                }
            }
        }
        i++;
        tkn = inexp[i];
    }

    while (top >= 0)
    {
        postexp[k] = pop();
        k++;
    }

    postexp[k] = '\0';
}

int main()
{
    char inexp[MAX], postexp[MAX];

    printf("Enter Infix Expression: ");
    scanf("%s", inexp);

    infixToPostfix(inexp, postexp);

    printf("Postfix Expression: %s\n", postexp);

    return 0;
}