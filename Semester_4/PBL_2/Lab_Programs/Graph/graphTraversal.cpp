#include <iostream>
#include <stack>
#include <queue>
using namespace std;

#define MAX 10

class Graph
{
private:
    int adjMatrix[MAX][MAX];
    int numVertices;

public:
    Graph(int vertices)
    {
        numVertices = vertices;

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int start, int end)
    {
        adjMatrix[start][end] = 1;
        adjMatrix[end][start] = 1;
    }

    void displayMatrix()
    {
        cout << "\nAdjacency Matrix:\n";
        cout << "   ";
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " ";
        }
        cout << "\n";

        for (int i = 0; i < numVertices; i++)
        {
            cout << i << "  ";
            for (int j = 0; j < numVertices; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }


    void DFS_Recursive_Helper(int v, bool visited[])
    {
        cout << v << " ";

        visited[v] = true;

        for (int w = 0; w < numVertices; w++)
        {
            // Check if 'w' is adjacent to 'v' (edge exists)
            // AND 'w' is not yet visited
            if (adjMatrix[v][w] == 1 && !visited[w])
            {
                DFS_Recursive_Helper(w, visited); // Recursively visit vertex 'w'
            }
        }
    }

    // Main DFS Recursive function (as per your notes)
    void DFS_Recursive(int startVertex)
    {
        cout << "\n=== DFS (Recursive) starting from vertex " << startVertex << " ===\n";

        // STEP 1: Create visited array and initialize all to false (not visited)
        bool visited[MAX];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false; // Initially no vertex is visited
        }

        // STEP 2: Start DFS from the starting vertex
        DFS_Recursive_Helper(startVertex, visited);

        cout << "\n";
    }

    // ==================== DFS NON-RECURSIVE (USING STACK) ====================
    // This is exactly from your notes (Slide 55-56)

    void DFS_Iterative(int startVertex)
    {
        cout << "\n=== DFS (Iterative using Stack) starting from vertex " << startVertex << " ===\n";

        // STEP 1: Create visited array and initialize all to false
        bool visited[MAX];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false; // Initially no vertex is visited
        }

        // STEP 2: Create a stack for DFS
        stack<int> s;

        // STEP 3: Push starting vertex to stack and mark it visited
        s.push(startVertex);
        visited[startVertex] = true;

        // STEP 4: Loop until stack is empty
        while (!s.empty())
        {
            // STEP 4a: Pop a vertex from stack
            int v = s.top();
            s.pop();

            // STEP 4b: Print the popped vertex
            cout << v << " ";

            // STEP 4c: Visit all adjacent vertices of popped vertex
            // If adjacent vertex is not visited, push it to stack
            for (int w = 0; w < numVertices; w++)
            {
                // Check if 'w' is adjacent to 'v' AND not visited
                if (adjMatrix[v][w] == 1 && !visited[w])
                {
                    s.push(w);         // Push to stack
                    visited[w] = true; // Mark as visited
                }
            }
        }

        cout << "\n";
    }

    // ==================== BFS (USING QUEUE) ====================
    // This is exactly from your notes (Slide 74)

    void BFS(int startVertex)
    {
        cout << "\n=== BFS (using Queue) starting from vertex " << startVertex << " ===\n";

        // STEP 1: Create visited array and initialize all to false
        bool visited[MAX];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false; // Initially no vertex is visited
        }

        // STEP 2: Create a queue for BFS
        queue<int> q;

        // STEP 3: Mark starting vertex as visited and enqueue it
        visited[startVertex] = true;
        q.push(startVertex);

        // STEP 4: Loop until queue is empty
        while (!q.empty())
        {
            // STEP 4a: Dequeue a vertex from queue
            int v = q.front();
            q.pop();

            // STEP 4b: Print the dequeued vertex
            cout << v << " ";

            // STEP 4c: Visit all adjacent vertices of dequeued vertex
            // If adjacent vertex is not visited, mark it visited and enqueue it
            for (int w = 0; w < numVertices; w++)
            {
                // Check if 'w' is adjacent to 'v' AND not visited
                if (adjMatrix[v][w] == 1 && !visited[w])
                {
                    visited[w] = true; // Mark as visited
                    q.push(w);         // Enqueue
                }
            }
        }

        cout << "\n";
    }
};

// ==================== MAIN FUNCTION ====================
int main()
{
    cout << "======================================\n";
    cout << "   GRAPH TRAVERSAL - DFS & BFS\n";
    cout << "======================================\n";

    // Create a graph with 8 vertices (0 to 7)
    // This matches the example from your notes (Slide 86)
    Graph g(8);

    // Add edges to create the graph from your notes
    // Graph structure from Slide 86:
    //       0
    //      /|\
    //     1 2 3
    //     |   |\
    //     4   5 6
    //         |
    //         7

    g.addEdge(0, 1); // Connect vertex 0 and 1
    g.addEdge(0, 2); // Connect vertex 0 and 2
    g.addEdge(0, 3); // Connect vertex 0 and 3
    g.addEdge(1, 4); // Connect vertex 1 and 4
    g.addEdge(3, 5); // Connect vertex 3 and 5
    g.addEdge(3, 6); // Connect vertex 3 and 6
    g.addEdge(5, 7); // Connect vertex 5 and 7

    // Display the adjacency matrix
    g.displayMatrix();

    cout << "\n======================================\n";
    cout << "   TRAVERSAL RESULTS\n";
    cout << "======================================\n";

    // Perform DFS Recursive starting from vertex 0
    g.DFS_Recursive(0);

    // Perform DFS Iterative (using stack) starting from vertex 0
    g.DFS_Iterative(0);

    // Perform BFS (using queue) starting from vertex 0
    g.BFS(0);

    cout << "\n======================================\n";
    cout << "   KEY DIFFERENCES:\n";
    cout << "======================================\n";
    cout << "DFS (Depth First Search):\n";
    cout << "  - Uses STACK (or recursion)\n";
    cout << "  - Goes DEEP into graph first\n";
    cout << "  - Explores one branch completely before backtracking\n\n";

    cout << "BFS (Breadth First Search):\n";
    cout << "  - Uses QUEUE\n";
    cout << "  - Goes LEVEL by LEVEL\n";
    cout << "  - Explores all neighbors first before going deeper\n";
    cout << "======================================\n";

    return 0;
}