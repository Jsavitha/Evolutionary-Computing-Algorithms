#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
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
    map<string, string> parent;
    vector<string> history;
    stack<string> st;
    st.push(start);
    parent[start] = "";
    while (!st.empty()) {
        string current = st.top();
        st.pop();
        if (visited[current]) continue;
        visited[current] = true;
        history.push_back(current);
        cout << "Visiting: " << current << endl;
        if (current == goal) {
            cout << "Reached goal!\n";
            vector<string> path;
            for (string node = goal; node != ""; node = parent[node])
                path.push_back(node);
            reverse(path.begin(), path.end());
            cout << "Path: ";
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i + 1 < path.size()) cout << " -> ";
            }
            cout << endl;
            cout << "Search History: ";
            for (size_t i = 0; i < history.size(); i++) {
                cout << history[i];
                if (i + 1 < history.size()) cout << " -> ";
            }
            cout << endl;
            return 0;
        }
        vector<string> neighbors = graph[current];
        sort(neighbors.begin(), neighbors.end(), greater<string>());
        for (auto &n : neighbors) {
            if (!visited[n]) {
                parent[n] = current;
                st.push(n);
            }
        }
    }

    cout << "Goal not found.\n";
}
