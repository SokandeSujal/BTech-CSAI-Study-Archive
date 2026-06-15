#include <stdio.h>

int main()
{
    int rows = 4;
    int cols = 3;

    int arr[4][3] = {
        {0, 0, 3},
        {4, 0, 0},
        {0, 0, 0},
        {0, 5, 6}};

    // Compact Form Representation
    int maxElements = rows * cols;
    int compact[maxElements][3];
    int k = 1;

    compact[0][0] = rows;
    compact[0][1] = cols;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] != 0)
            {
                compact[k][0] = i;
                compact[k][1] = j;
                compact[k][2] = arr[i][j];
                k++;
            }
        }
    }

    compact[0][2] = k - 1;

    // Print Compact Form

    printf("Compact Form Representation:\n");
    printf("R C V\n");
    printf("------\n");
    for (int i = 0; i < k; i++)
    {
        printf("%d %d %d\n", compact[i][0], compact[i][1], compact[i][2]);
    }

    // Simple Transpose
    int simpleTranspose[maxElements][3];
    simpleTranspose[0][0] = cols;
    simpleTranspose[0][1] = rows;
    simpleTranspose[0][2] = compact[0][2];

    int index = 1;

    for (int i = 0; i < compact[0][1]; i++)
    {
        for (int j = 1; j <= compact[0][2]; j++)
        {
            if (compact[j][1] == i)
            {
                simpleTranspose[index][0] = compact[j][1];
                simpleTranspose[index][1] = compact[j][0];
                simpleTranspose[index][2] = compact[j][2];
                index++;
            }
        }
    }

    // Print Simple Transpose
    printf("\nSimple Transpose Representation:\n");
    printf("R C V\n");
    printf("------\n");
    for (int i = 0; i < index; i++)
    {
        printf("%d %d %d\n", simpleTranspose[i][0], simpleTranspose[i][1], simpleTranspose[i][2]);
    }

    // Fast Transpose
    int loc, col_no;
    int fastTranspose[maxElements][3];

    int total[cols];
    int indexFast[cols + 1];

    for (int i = 0; i < cols; i++)
    {
        total[i] = 0;
    }

    for (int i = 1; i <= compact[0][2]; i++)
    {
        col_no = compact[i][1];
        total[col_no] = total[col_no] + 1;
    }

    indexFast[0] = 1;
    for (int i = 1; i < cols; i++)
    {
        indexFast[i] = indexFast[i - 1] + total[i - 1];
    }

    fastTranspose[0][0] = cols;
    fastTranspose[0][1] = rows;
    fastTranspose[0][2] = compact[0][2];

    for (int i = 1; i <= compact[0][2]; i++)
    {
        col_no = compact[i][1];
        loc = indexFast[col_no];

        fastTranspose[loc][0] = compact[i][1];
        fastTranspose[loc][1] = compact[i][0];
        fastTranspose[loc][2] = compact[i][2];
        indexFast[col_no] = indexFast[col_no] + 1;
    }

    // Print Fast Transpose
    printf("\nFast Transpose Representation:\n");
    printf("R C V\n");
    printf("------\n");
    for (int i = 0; i <= compact[0][2]; i++)
    {
        printf("%d %d %d\n", fastTranspose[i][0], fastTranspose[i][1], fastTranspose[i][2]);
    }

    return 0;
}