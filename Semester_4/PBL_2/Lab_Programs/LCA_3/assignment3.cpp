#include <iostream>
#include <vector>
using namespace std;

#define MAX 10

class Graph
{
    vector<int> adj[MAX];
    int n;

public:
    void createGraph()
    {
        cout << "Enter number of users: ";
        cin >> n;

        int edges;
        cout << "Enter number of friendships: ";
        cin >> edges;

        for (int i = 0; i < edges; i++)
        {
            int u, v;
            cout << "Enter friends IDs (u v): ";
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void display()
    {
        cout << "\nAdjacency List: \n";
        for (int i = 0; i <= n; i++)
        {
            cout << i << " -> ";
            for (int j = 0; j < adj[i].size(); j++)
            {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    // -------- Recursive DFS --------

    void DFS_Recursive(int v, bool visited[])
    {
        cout << v << " ";
        visited[v] = true;
        for (int i = 0; i < adj[v].size(); i++)
        {
            int neighbor = adj[v][i];
            if (!visited[neighbor])
            {
                DFS_Recursive(neighbor, visited);
            }
        }
    }

    void callDFSRecursive(int start)
    {
        bool visited[MAX] = {false};
        cout << "\nDFS (Recursive): ";
        DFS_Recursive(start, visited);
    }

    // -------- Non-Recursive DFS --------

    void DFS_NonRecursive(int start)
    {
        int stack[MAX], top = -1;
        bool visited[MAX] = {false};

        stack[++top] = start;

        cout << "\nDFS (Non-Recursive): ";

        while (top != -1)
        {
            int v = stack[top--];
            if (!visited[v])
            {
                cout << v << " ";
                visited[v] = true;
            }
            for (int i = adj[v].size() - 1; i >= 0; i--)
            {
                int neighbor = adj[v][i];
                if (!visited[neighbor])
                {
                    stack[++top] = neighbor;
                }
            }
        }
    }

    // -------- BFS --------
    void BFS(int start)
    {
        int queue[MAX], front = 0, rear = 0;
        bool visisted[MAX] = {false};

        queue[rear++] = start;
        visisted[start] = true;

        cout << "\nBFS: ";

        while (front < rear)
        {
            int v = queue[front++];
            cout << v << " ";

            for (int i = 0; i < adj[v].size(); i++)
            {
                int neighbor = adj[v][i];
                if (!visisted[neighbor])
                {
                    queue[rear++] = neighbor;
                    visisted[neighbor] = true;
                }
            }
        }
    }
};

int main()
{

    Graph g;

    g.createGraph();
    g.display();

    int start;
    cout << "\nnEnter starting node (ID): ";
    cin >> start;

    g.callDFSRecursive(start);
    g.DFS_NonRecursive(start);
    g.BFS(start);

    return 0;
}