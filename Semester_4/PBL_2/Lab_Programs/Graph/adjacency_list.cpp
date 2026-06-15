#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int numVertices;
    vector<int> *adjList;

public:
    Graph(int vertices)
    {
        numVertices = vertices;
        adjList = new vector<int>[vertices];
    }

    ~Graph()
    {
        delete[] adjList;
    }

    void addEdge(int v1, int v2)
    {
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
    }

    void display()
    {
        cout << "\nAdjacency List Representation:\n";
        cout << "================================\n";

        for (int i = 0; i < numVertices; i++)
        {
            cout << "Vertex " << i << " -> ";

            for (int j = 0; j < adjList[i].size(); j++)
            {
                cout << adjList[i][j];
                if (j < adjList[i].size() - 1)
                {
                    cout << " -> ";
                }
            }

            if (adjList[i].size() == 0)
            {
                cout << "NULL";
            }

            cout << "\n";
        }
    }

    void DFS(int vertex, bool visited[])
    {
        visited[vertex] = true;
        cout << vertex << " ";

        for (int i = 0; i < adjList[vertex].size(); i++)
        {
            int neighbor = adjList[vertex][i];
            if (!visited[neighbor])
            {
                DFS(neighbor, visited);
            }
        }
    }

    void DFS_Traversal(int start)
    {
        cout << "\nDFS Traversal from vertex " << start << ": ";

        bool visited[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false;
        }

        DFS(start, visited);
        cout << "\n";
    }
};

int main()
{
    cout << "ADJACENCY LIST REPRESENTATION\n";

    Graph g(5);

    cout << "\nAdding edges to the graph...\n";
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 4);

    g.display();

    g.DFS_Traversal(0);

    return 0;
}