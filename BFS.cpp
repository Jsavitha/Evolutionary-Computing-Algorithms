#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

map<string, vector<string>> graph = {
    {"S", {"A", "B"}},
    {"A", {"B", "D"}},
    {"B", {"A", "C"}},
    {"C", {"E"}},
    {"D", {"G"}},
    {"E", {}},
    {"G", {}}
};

void BFS(string start, string goal) {
    queue<string> q;                 
    set<string> visited;             
    map<string, string> parent;      
    map<string, int> level;          
    q.push(start);
    visited.insert(start);
    level[start] = 0;
    parent[start] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        cout << "Visiting: " << current << " at level " << level[current] << endl;

        if (current == goal) {
            cout << "Reached goal!\n";
            // Show final path
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
            return; // stop search
        }

        // Sort neighbors for lexicographical order
        vector<string> neighbors = graph[current];
        sort(neighbors.begin(), neighbors.end());

        for (string n : neighbors) {
            if (!visited.count(n)) {
                visited.insert(n);
                q.push(n);
                parent[n] = current;
                level[n] = level[current] + 1;
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    BFS("S", "G");
    return 0;
}
