#include <iostream>
using namespace std;

class Knapsack
{
private:
    int n;
    int capacity;
    int weights[100];
    int values[100];
    int dp[100][1000];

public:
    void input()
    {
        cout << "Enter number of items: ";
        cin >> n;

        cout << "Enter knapsack capacity: ";
        cin >> capacity;

        cout << "\nEnter weights and values:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Item " << (i + 1) << " - Weight: ";
            cin >> weights[i];
            cout << "Item " << (i + 1) << " - Value: ";
            cin >> values[i];
        }
    }

    void displayInput()
    {
        cout << "\nKnapsack Capacity: " << capacity << endl;
        cout << "Number of Items: " << n << endl;

        cout << "\nItems details:\n";
        cout << "Item\tWeight\tValue\n";
        for (int i = 0; i < n; i++)
        {
            cout << (i + 1) << "\t" << weights[i] << "\t" << values[i] << endl;
        }
    }

    int solve()
    {
        for (int i = 0; i <= n; i++)
        {
            for (int w = 0; w <= capacity; w++)
            {
                if (i == 0 || w == 0)
                {
                    dp[i][w] = 0;
                }
                else if (weights[i - 1] <= w)
                {
                    dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]],
                                   dp[i - 1][w]);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        return dp[n][capacity];
    }

    void printSolution()
    {
        int maxValue = solve();

        cout << "\nMaximum value: " << maxValue << endl;

        cout << "Items selected:\n";
        int w = capacity;
        for (int i = n; i > 0 && maxValue > 0; i--)
        {
            if (maxValue != dp[i - 1][w])
            {
                cout << "Item " << i << " (Weight=" << weights[i - 1]
                     << ", Value=" << values[i - 1] << ")\n";
                maxValue -= values[i - 1];
                w -= weights[i - 1];
            }
        }
    }

    void displayTable()
    {
        cout << "\nDP Table:\n";
        cout << "W\\I\t";
        for (int i = 0; i <= n; i++)
        {
            cout << i << "\t";
        }
        cout << endl;

        for (int w = 0; w <= capacity; w++)
        {
            cout << w << "\t";
            for (int i = 0; i <= n; i++)
            {
                cout << dp[i][w] << "\t";
            }
            cout << endl;
        }
    }
};

int main()
{
    Knapsack k;
    int choice;

    k.input();

    do
    {
        cout << "\n1. Solve Knapsack\n2. Display DP Table\n3. Display Input\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            k.printSolution();
            break;
        case 2:
            k.displayTable();
            break;
        case 3:
            k.displayInput();
            break;

        case 4:
            cout << "Exiting\n";
            break;
        default:
            cout << "Invalid\n";
        }
    } while (choice != 4);

    return 0;
}
