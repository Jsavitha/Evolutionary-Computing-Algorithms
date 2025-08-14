#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    map<string, vector<string>> graph = {
        {"S", {"A", "B"}},
        {"A", {"B", "D"}},
        {"B", {"A", "C"}},
        {"C", {}},
        {"D", {"G"}},
        {"G", {}}
    };
    map<string, int> h = {
        {"S", 8}, {"A", 7}, {"B", 6},
        {"C", 7}, {"D", 5}, {"G", 0}
    };
    int beamWidth = 2;
    vector<string> level = {"S"};
    vector<string> path = {"S"};
    vector<string> history = {"S"};
    while (!level.empty()) {
        for (string node : level) {
            if (node == "G") {
                cout << "Path: ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i] << (i + 1 < path.size() ? " -> " : "");
                }
                cout << "\nSearch History: ";
                for (size_t i = 0; i < history.size(); i++) {
                    cout << history[i] << (i + 1 < history.size() ? " -> " : "");
                }
                cout << endl;
                return 0;
            }
        }
        vector<string> nextLevel;
        for (string node : level) {
            for (string neigh : graph[node]) {
                nextLevel.push_back(neigh);
                history.push_back(neigh);
            }
        }
        if (nextLevel.empty()) break;
        sort(nextLevel.begin(), nextLevel.end(),
             [&](string a, string b) { return h[a] < h[b]; });
        if ((int)nextLevel.size() > beamWidth)
            nextLevel.resize(beamWidth);
        path.push_back(nextLevel[0]);
        level = nextLevel;
    }
    cout << "Goal not found.\n";
}
