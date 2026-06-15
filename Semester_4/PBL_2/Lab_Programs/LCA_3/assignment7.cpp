#include <iostream>
using namespace std;

#define MAX 50

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{

    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    int weight[MAX], profit[MAX];

    cout << "Enter weights:\n";
    for (int i = 1; i <= n; i++)
        cin >> weight[i];

    cout << "Enter profits:\n";
    for (int i = 1; i <= n; i++)
        cin >> profit[i];

    cout << "Enter capacity: ";
    cin >> W;

    int KS[MAX][MAX];

    for (int i = 0; i <= n; i++)
    {
        KS[i][0] = 0;
    }

    for (int w = 0; w <= W; w++)
    {
        KS[0][w] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= W; w++)
        {
            if (weight[i] <= w)
            {
                KS[i][w] = max(
                    KS[i - 1][w - weight[i]] + profit[i],
                    KS[i - 1][w]);
            }
            else
            {
                KS[i][w] = KS[i - 1][w];
            }
        }
    }

    cout << "\nKnapsack Table:\n";
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            cout << KS[i][w] << "\t";
        }
        cout << endl;
    }

    cout << "\nMaximum Profit = " << KS[n][W] << endl;

    return 0;
}