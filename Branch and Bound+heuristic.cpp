#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Node {
    string name;
    int g; 
    int h; 
    vector<string> path;
    int f() const { return g + h; }
};
map<string, vector<pair<string,int>>> graph = {
    {"S", {{"A",3}, {"B",5}}},
    {"A", {{"B",7}, {"D",6}}},
    {"B", {{"D",5}, {"A",4}, {"C",9}}},
    {"D", {{"G",5}}},
    {"C", {}},
    {"G", {}}
};
map<string, int> h = { {"S",1}, {"A",7}, {"B",6}, {"C",7}, {"D",0}, {"G",0} };
int main() {
    int bestCost = INT_MAX;
    vector<string> bestPath;
    auto cmp = [](Node a, Node b){ return a.f() > b.f(); };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    pq.push({"S", 0, h["S"], {"S"}});
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        if (cur.f() > bestCost) continue; 
        if (cur.name == "G") {
            if (cur.g < bestCost) {
                bestCost = cur.g;
                bestPath = cur.path;
            }
            continue;
        }
        for (auto &edge : graph[cur.name]) {
            Node next;
            next.name = edge.first;
            next.g = cur.g + edge.second;
            next.h = h[edge.first];
            next.path = cur.path;
            next.path.push_back(edge.first);
            pq.push(next);
        }
    }
    cout << "Branch & Bound + Heuristic Path: ";
    for (auto &n : bestPath) cout << n << " ";
    cout << "Cost=" << bestCost << endl;
}
