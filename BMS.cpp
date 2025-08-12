#include <bits/stdc++.h>
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
vector<vector<string>> allPaths; 
void BMS(string current, string goal, vector<string> path, set<string> visited) {
    path.push_back(current);
    visited.insert(current);
    if (current == goal) { 
        allPaths.push_back(path);
        return;
    }
    vector<string> neighbors = graph[current];
    sort(neighbors.begin(), neighbors.end());

    bool moved = false;
    for (auto &n : neighbors) {
        if (!visited.count(n)) {
            moved = true;
            BMS(n, goal, path, visited); 
        }
    }
}
int main() {
    vector<string> path;
    set<string> visited;
    BMS("S", "G", path, visited);
    cout << "All possible paths from S to G:\n";
    for (auto &p : allPaths) {
        for (int i = 0; i < p.size(); i++) {
            cout << p[i];
            if (i != p.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
}

