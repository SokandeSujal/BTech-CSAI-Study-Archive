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

void reverse(char str[])
{
    int len = strlen(str);
    int i, j;
    char temp;

    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void swapParentheses(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '(')
        {
            str[i] = ')';
        }
        else if (str[i] == ')')
        {
            str[i] = '(';
        }
    }
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

void infixToPrefix(char inexp[], char prefixexp[])
{
    int k = 0, i = 0;
    char tkn;

    reverse(inexp);
    swapParentheses(inexp);

    tkn = inexp[i];

    while (tkn != '\0')
    {
        if (isalnum(tkn))
        {
            prefixexp[k] = tkn;
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
                        prefixexp[k] = tkn;
                        k++;
                    }
                }
                else
                {
                    while (top >= 0 && isp(stk[top]) >= icp(tkn))
                    {
                        prefixexp[k] = pop();
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
        prefixexp[k] = pop();
        k++;
    }

    prefixexp[k] = '\0';

    reverse(prefixexp);
}

int main()
{
    char inexp[MAX], prefixexp[MAX];

    printf("Enter Infix Expression: ");
    scanf("%s", inexp);

    infixToPrefix(inexp, prefixexp);

    printf("Prefix Expression: %s\n", prefixexp);

    return 0;
}