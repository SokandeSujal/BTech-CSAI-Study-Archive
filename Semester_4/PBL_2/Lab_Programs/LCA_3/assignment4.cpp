#include <iostream>
using namespace std;

#define MAX 10
#define INF 999

class graph
{
    int cost[MAX][MAX], n;

public:
    void input()
    {
        cout << "Enter number of offices (nodes): ";
        cin >> n;

        cout << "Enter cost matrix (enter 0 if no edge):\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> cost[i][j];
                if (cost[i][j] == 0)
                {
                    cost[i][j] = INF;
                }
            }
        }
    }

    void prims()
    {
        int visited[MAX] = {0};
        int minCost = 0;

        visited[0] = 1;
        cout << "\nEdges in MST: \n";

        for (int k = 0; k < n - 1; k++)
        {
            int min = INF, a = -1, b = -1;

            for (int i = 0; i < n; i++)
            {
                if (visited[i])
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (!visited[j] && cost[i][j] < min)
                        {
                            min = cost[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }

            if (a != -1 && b != -1)
            {
                cout << a << " - " << b << " : " << min << endl;
                minCost += min;
                visited[b] = 1;
            }
        }
        cout << "\nMinimum Total Cost: " << minCost << endl;
    }
};

int main()
{

    graph g;

    g.input();
    g.prims();

    return 0;
}