#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
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
bool goalFound = false; 
void DFS(string current, string goal, vector<string> &path, set<string> &visited) {
    if (goalFound) return; 
    path.push_back(current);
    visited.insert(current);
    cout << "Visiting: " << current << " | Path so far: ";
    for (auto &node : path) cout << node << " ";
    cout << endl;
    if (current == goal) {
        cout << "Reached goal! Final path:\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << endl;
        goalFound = true;
        return;
    }
    vector<string> neighbors = graph[current];
    sort(neighbors.begin(), neighbors.end());
    bool deadEnd = true;
    for (auto &n : neighbors) {
        if (!visited.count(n)) {
            deadEnd = false;
            DFS(n, goal, path, visited);
            if (goalFound) return; 
        }
    }
    if (deadEnd) {
        cout << "Dead end at: " << current << " -> going back\n";
    }

    path.pop_back();
    visited.erase(current);
}
int main() {
    vector<string> path;
    set<string> visited;
    DFS("S", "G", path, visited);
    if (!goalFound) {
        cout << "No path found from S to G.\n";
    }
    return 0;
}
