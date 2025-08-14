#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    // Graph definition
    map<string, vector<string>> graph = {
        {"S", {"A", "B"}},
        {"A", {"B", "D"}},
        {"B", {"A", "C"}},
        {"C", {"E"}},
        {"D", {"G"}},
        {"E", {}},
        {"G", {}}
    };

    string start = "S", goal = "G";
    map<string, bool> visited;
    vector<string> history;
    queue<string> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        history.push_back(current);
        cout << "Visiting: " << current << endl;

        if (current == goal) {
            cout << "Reached goal!\n";
            cout << "Search History: ";
            for (size_t i = 0; i < history.size(); i++) {
                cout << history[i];
                if (i + 1 < history.size()) cout << " -> ";
            }
            cout << endl;
            return 0;
        }

        vector<string> neighbors = graph[current];
        sort(neighbors.begin(), neighbors.end()); // lexicographical order
        for (auto &n : neighbors) {
            if (!visited[n]) {
                visited[n] = true;
                q.push(n);
            }
        }
    }

    cout << "Goal not found.\n";
}
