#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <string>
using namespace std;

class Graph {
private:
    int vertices;
    list<int> *adjList;
    string *names;
    
public:
    Graph(int v) {
        vertices = v;
        adjList = new list<int>[v];
        names = new string[v];
    }
    
    ~Graph() {
        delete[] adjList;
        delete[] names;
    }
    
    void addNames() {
        for(int i = 0; i < vertices; i++) {
            cout << "Name for ID " << i << ": ";
            cin >> names[i];
        }
    }
    
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    void createGraph() {
        int edges;
        cout << "Number of edges: ";
        cin >> edges;
        
        cout << "Enter edges (u v):\n";
        for(int i = 0; i < edges; i++) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }
    
    void displayGraph() {
        cout << "\nAdjacency List:\n";
        for(int i = 0; i < vertices; i++) {
            cout << i << " (" << names[i] << "): ";
            for(int j : adjList[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
    
    void DFS_Recursive(int start) {
        bool *visited = new bool[vertices];
        for(int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        cout << "DFS (Recursive): ";
        DFS_RecursiveUtil(start, visited);
        cout << endl;
        
        delete[] visited;
    }
    
private:
    void DFS_RecursiveUtil(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " ";
        
        for(int neighbor : adjList[v]) {
            if(!visited[neighbor]) {
                DFS_RecursiveUtil(neighbor, visited);
            }
        }
    }
    
public:
    void DFS_NonRecursive(int start) {
        bool *visited = new bool[vertices];
        for(int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        stack<int> s;
        s.push(start);
        
        cout << "DFS (Stack): ";
        
        while(!s.empty()) {
            int v = s.top();
            s.pop();
            
            if(!visited[v]) {
                visited[v] = true;
                cout << v << " ";
                
                list<int>::reverse_iterator rit;
                for(rit = adjList[v].rbegin(); rit != adjList[v].rend(); ++rit) {
                    if(!visited[*rit]) {
                        s.push(*rit);
                    }
                }
            }
        }
        cout << endl;
        
        delete[] visited;
    }
    
    void BFS(int start) {
        bool *visited = new bool[vertices];
        for(int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        queue<int> q;
        visited[start] = true;
        q.push(start);
        
        cout << "BFS (Queue): ";
        
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";
            
            for(int neighbor : adjList[v]) {
                if(!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
        
        delete[] visited;
    }
};

int main() {
    int numUsers, startNode;
    
    cout << "Number of users: ";
    cin >> numUsers;
    
    Graph g(numUsers);
    
    g.addNames();
    g.createGraph();
    
    int choice;
    do {
        cout << "\n1. Display Graph\n";
        cout << "2. DFS Recursive\n";
        cout << "3. DFS Non-Recursive\n";
        cout << "4. BFS\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                g.displayGraph();
                break;
                
            case 2:
                cout << "Start node: ";
                cin >> startNode;
                g.DFS_Recursive(startNode);
                break;
                
            case 3:
                cout << "Start node: ";
                cin >> startNode;
                g.DFS_NonRecursive(startNode);
                break;
                
            case 4:
                cout << "Start node: ";
                cin >> startNode;
                g.BFS(startNode);
                break;
                
            case 5:
                cout << "Exiting\n";
                break;
                
            default:
                cout << "Invalid choice\n";
        }
        
    } while(choice != 5);
    
    return 0;
}
