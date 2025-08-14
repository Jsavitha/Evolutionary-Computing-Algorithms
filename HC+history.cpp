#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, vector<string>> G = {
        {"S", {"A","B"}},
        {"A", {"B","D"}},
        {"B", {"A","C"}},
        {"C", {}},
        {"D", {"G"}},
        {"G", {}}
    };
    map<string,int> h = { {"S",8}, {"A",7}, {"B",6}, {"C",7}, {"D",5}, {"G",0} };
    string start="S", goal="G";
    map<string,bool> visited;
    vector<string> path;
    vector<string> history;
    function<bool(string)> dfs = [&](string u){
        history.push_back(u);       // record visit
        path.push_back(u);
        if(u == goal) return true;
        visited[u] = true;
        auto nbrs = G[u];
        sort(nbrs.begin(), nbrs.end(), [&](const string& a, const string& b){
            if(h[a] != h[b]) return h[a] < h[b];
            return a < b; 
        });
        for(auto &v : nbrs){
            if(!visited[v]){
                if(dfs(v)) return true;
            }
        }
        path.pop_back(); 
        return false;
    };
    if(dfs(start)){
        cout << "Path: ";
        for(size_t i=0;i<path.size();i++){
            cout << path[i] << (i+1<path.size() ? " -> " : "\n");
        }
    } else {
        cout << "No path found\n";
    }
    cout << "History: ";
    for(size_t i=0;i<history.size();i++){
        cout << history[i] << (i+1<history.size() ? " -> " : "\n");
    }
}
