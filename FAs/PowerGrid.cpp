#include <iostream>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class PowerGrid
{

    map<string, list<string>> graph;

public:
    // Add substation
    void addSubstation(string node)
    {
        if (graph.find(node) == graph.end())
        {
            graph[node] = list<string>();
            cout << "Substation added: " << node << endl;
        }
        else
            cout << "Substation already exists\n";
    }

    // Add transmission line
    void addLine(string u, string v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);

        cout << "Transmission line added between "
             << u << " and " << v << endl;
    }

    // Remove transmission line
    void removeLine(string u, string v)
    {
        if (graph.find(u) == graph.end() || graph.find(v) == graph.end())
        {
            cout << "One or both substations do not exist\n";
            return;
        }

        graph[u].remove(v);
        graph[v].remove(u);

        cout << "Transmission line removed between "
             << u << " and " << v << endl;
    }

    // Tree display helper
    void displayTree(string node, string parent, string prefix, bool isLast)
    {
        cout << prefix;

        if (isLast)
            cout << "+-- ";
        else
            cout << "|-- ";

        cout << node << endl;

        prefix += (isLast ? "    " : "|   ");

        vector<string> children;

        for (auto neighbor : graph[node])
        {
            if (neighbor != parent)
                children.push_back(neighbor);
        }

        for (int i = 0; i < children.size(); i++)
        {
            bool last = (i == children.size() - 1);
            displayTree(children[i], node, prefix, last);
        }
    }

    // Display grid
    void displayGrid()
    {
        if (graph.empty())
        {
            cout << "Grid empty\n";
            return;
        }

        cout << "\nPower Grid Structure\n";

        string root = "Station";

        if (graph.find(root) == graph.end())
        {
            cout << "Root 'Station' not found\n";
            return;
        }

        cout << root << endl;

        vector<string> children;

        for (auto neighbor : graph[root])
            children.push_back(neighbor);

        for (int i = 0; i < children.size(); i++)
        {
            bool last = (i == children.size() - 1);
            displayTree(children[i], root, "", last);
        }
    }

    // BFS traversal
    void BFS(string start)
    {
        set<string> visited;
        queue<string> q;

        q.push(start);
        visited.insert(start);

        cout << "\nBFS Traversal: ";

        while (!q.empty())
        {
            string node = q.front();
            q.pop();

            cout << node << " ";

            for (auto nbr : graph[node])
            {
                if (!visited.count(nbr))
                {
                    visited.insert(nbr);
                    q.push(nbr);
                }
            }
        }

        cout << endl;
    }

    // DFS helper
    void DFSUtil(string node, set<string> &visited)
    {
        visited.insert(node);
        cout << node << " ";

        for (auto nbr : graph[node])
        {
            if (!visited.count(nbr))
                DFSUtil(nbr, visited);
        }
    }

    // DFS traversal
    void DFS(string start)
    {
        set<string> visited;

        cout << "\nDFS Traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Articulation point helper
    void APUtil(string u,
                map<string, bool> &visited,
                map<string, int> &disc,
                map<string, int> &low,
                map<string, string> &parent,
                set<string> &ap,
                int &time)
    {
        int children = 0;

        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (auto v : graph[u])
        {
            if (!visited[v])
            {
                children++;
                parent[v] = u;

                APUtil(v, visited, disc, low, parent, ap, time);

                low[u] = min(low[u], low[v]);

                if (parent[u] == "" && children > 1)
                    ap.insert(u);

                if (parent[u] != "" && low[v] >= disc[u])
                    ap.insert(u);
            }
            else if (v != parent[u])
                low[u] = min(low[u], disc[v]);
        }
    }

    // Find critical substations
    void articulationPoints()
    {
        map<string, bool> visited;
        map<string, int> disc;
        map<string, int> low;
        map<string, string> parent;

        set<string> ap;

        int time = 0;

        for (auto node : graph)
        {
            visited[node.first] = false;
            parent[node.first] = "";
        }

        for (auto node : graph)
        {
            if (!visited[node.first])
                APUtil(node.first, visited, disc, low, parent, ap, time);
        }

        cout << "\nCritical Substations\n";

        if (ap.empty())
            cout << "None\n";
        else
            for (auto node : ap)
                cout << node << endl;
    }

    // Simulate substation failure
    void simulateFailure(string node)
    {
        if (graph.find(node) == graph.end())
        {
            cout << "Substation not found\n";
            return;
        }

        cout << "\nSimulating failure of " << node << endl;

        for (auto nbr : graph[node])
            graph[nbr].remove(node);

        graph.erase(node);

        displayGrid();
    }

    // Find alternative path
    void findPath(string start, string end)
    {
        set<string> visited;
        queue<vector<string>> q;

        q.push({start});

        while (!q.empty())
        {
            vector<string> path = q.front();
            q.pop();

            string node = path.back();

            if (node == end)
            {
                cout << "\nAlternative Path: ";

                for (int i = 0; i < path.size(); i++)
                {
                    cout << path[i];

                    if (i != path.size() - 1)
                        cout << " -> ";
                }

                cout << endl;
                return;
            }

            if (!visited.count(node))
            {
                visited.insert(node);

                for (auto nbr : graph[node])
                {
                    vector<string> newpath = path;
                    newpath.push_back(nbr);
                    q.push(newpath);
                }
            }
        }

        cout << "No path found\n";
    }
};

int main()
{
    PowerGrid grid;
    int choice;

    while (true)
    {
        cout << "\n------ POWER GRID SYSTEM ------\n";
        cout << "1 Add Substation\n";
        cout << "2 Add Transmission Line\n";
        cout << "3 Remove Transmission Line\n";
        cout << "4 Display Grid\n";
        cout << "5 BFS Traversal\n";
        cout << "6 DFS Traversal\n";
        cout << "7 Find Critical Substations\n";
        cout << "8 Simulate Substation Failure\n";
        cout << "9 Find Alternative Path\n";
        cout << "10 Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string node;
            cout << "Enter substation: ";
            cin >> node;
            grid.addSubstation(node);
        }

        else if (choice == 2)
        {
            string u, v;
            cout << "Enter first substation: ";
            cin >> u;
            cout << "Enter second substation: ";
            cin >> v;
            grid.addLine(u, v);
        }

        else if (choice == 3)
        {
            string u, v;
            cout << "Enter first substation: ";
            cin >> u;
            cout << "Enter second substation: ";
            cin >> v;
            grid.removeLine(u, v);
        }

        else if (choice == 4)
            grid.displayGrid();

        else if (choice == 5)
        {
            string start;
            cout << "Start node: ";
            cin >> start;
            grid.BFS(start);
        }

        else if (choice == 6)
        {
            string start;
            cout << "Start node: ";
            cin >> start;
            grid.DFS(start);
        }

        else if (choice == 7)
            grid.articulationPoints();

        else if (choice == 8)
        {
            string node;
            cout << "Substation to fail: ";
            cin >> node;
            grid.simulateFailure(node);
        }

        else if (choice == 9)
        {
            string start, end;
            cout << "Start node: ";
            cin >> start;
            cout << "End node: ";
            cin >> end;
            grid.findPath(start, end);
        }

        else if (choice == 10)
            break;

        else
            cout << "Invalid choice\n";
    }

    return 0;
}