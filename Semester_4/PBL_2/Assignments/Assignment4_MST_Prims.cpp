#include <iostream>
#include <climits>
using namespace std;

class Graph
{
private:
    int vertices;
    int cost[20][20];

public:
    Graph()
    {
        vertices = 0;
    }

    void input()
    {
        cout << "Enter number of vertices: ";
        cin >> vertices;

        cout << "Enter cost adjacency matrix:\n";
        cout << "(Enter 0 for no edge, or actual cost)\n";

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                cout << "Cost[" << i << "][" << j << "]: ";
                cin >> cost[i][j];

                if (i != j && cost[i][j] == 0)
                {
                    cost[i][j] = INT_MAX;
                }
            }
        }
    }

    void displayMatrix()
    {
        cout << "\nCost Adjacency Matrix:\n";
        cout << "   ";
        for (int i = 0; i < vertices; i++)
        {
            cout << i << "   ";
        }
        cout << endl;

        for (int i = 0; i < vertices; i++)
        {
            cout << i << "  ";
            for (int j = 0; j < vertices; j++)
            {
                if (cost[i][j] == INT_MAX)
                {
                    cout << "∞   ";
                }
                else
                {
                    cout << cost[i][j] << "   ";
                }
            }
            cout << endl;
        }
    }

    void primsAlgorithm()
    {
        int parent[20];
        int key[20];
        bool selected[20];

        for (int i = 0; i < vertices; i++)
        {
            key[i] = INT_MAX;
            selected[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < vertices - 1; count++)
        {

            int min = INT_MAX;
            int u = -1;

            for (int v = 0; v < vertices; v++)
            {
                if (!selected[v] && key[v] < min)
                {
                    min = key[v];
                    u = v;
                }
            }

            selected[u] = true;

            for (int v = 0; v < vertices; v++)
            {

                if (!selected[v] && cost[u][v] != INT_MAX && cost[u][v] < key[v])
                {
                    parent[v] = u;
                    key[v] = cost[u][v];
                }
            }
        }

        displayMST(parent);
    }

private:
    void displayMST(int parent[])
    {
        cout << "\nMinimum Spanning Tree (MST):\n";
        cout << "Edge\tWeight\n";

        int totalCost = 0;

        for (int i = 1; i < vertices; i++)
        {
            cout << parent[i] << " - " << i << "\t" << cost[i][parent[i]] << endl;
            totalCost += cost[i][parent[i]];
        }

        cout << "\nTotal Minimum Cost: " << totalCost << endl;
    }
};

int main()
{
    Graph g;
    int choice;

    g.input();

    do
    {
        cout << "\n1. Display Cost Matrix\n";
        cout << "2. Find MST using Prim's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            g.displayMatrix();
            break;
        case 2:
            g.primsAlgorithm();
            break;
        case 3:
            cout << "Exiting\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 3);

    return 0;
}
