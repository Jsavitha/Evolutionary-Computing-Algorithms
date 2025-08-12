#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
map<string, vector<string>> buildGraph() {
    map<string, vector<string>> graph;
    graph["S"] = {"A", "B"};
    graph["A"] = {"B", "D"};
    graph["B"] = {"A", "C"};
    graph["C"] = {"E"};
    graph["D"] = {"G"};
    graph["E"] = {};
    graph["G"] = {};
    return graph;
}
void printPath(map<string, string> &parent, string goal) {
    vector<string> path;
    string node = goal;
    while (node != "") {
        path.push_back(node);
        node = parent[node];
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << endl;
}
void BFS(map<string, vector<string>> &graph, string start, string goal) {
    cout << "\nBFS Search:\n";
    map<string, bool> visited;
    map<string, string> parent;
    queue<string> q;
    visited[start] = true;
    parent[start] = "";
    q.push(start);
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        cout << "Visiting: " << current << endl;
        if (current == goal) {
            cout << "Reached goal!\n";
            printPath(parent, goal);
            return;
        }
        vector<string> neighbors = graph[current];
        sort(neighbors.begin(), neighbors.end()); // lexicographical order
        for (string n : neighbors) {
            if (!visited[n]) {
                visited[n] = true;
                parent[n] = current;
                q.push(n);
            }
        }
    }
    cout << "Goal not found.\n";
}

void DFS(map<string, vector<string>> &graph, string start, string goal) {
    cout << "\nDFS Search:\n";
    map<string, bool> visited;
    map<string, string> parent;
    stack<string> st;
    st.push(start);
    parent[start] = "";
    while (!st.empty()) {
        string current = st.top();
        st.pop();
        if (visited[current]) continue;
        visited[current] = true;
        cout << "Visiting: " << current << endl;
        if (current == goal) {
            cout << "Reached goal!\n";
            printPath(parent, goal);
            return;
        }

        vector<string> neighbors = graph[current];
        sort(neighbors.begin(), neighbors.end(), greater<string>()); // reverse for stack
        for (string n : neighbors) {
            if (!visited[n]) {
                parent[n] = current;
                st.push(n);
            }
        }
    }
    cout << "Goal not found.\n";
}
int main() {
    auto graph = buildGraph();
    BFS(graph, "S", "G");
    DFS(graph, "S", "G");
    return 0;
}
