#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string,int>>> G = {
    {"S", {{"A",3}, {"B",5}}},
    {"A", {{"B",4}, {"D",3}}},
    {"B", {{"A",4}, {"C",5}, {"E",10}}},
    {"C", {{"E",6}}},
    {"D", {{"G",5}}},
    {"E", {}},
    {"G", {}}
};
map<string,int> H = { {"S",0}, {"A",4}, {"B",7}, {"C",12}, {"D",5}, {"E",16}, {"G",0} };
struct Item {
    string v;              
    int g;                 
    vector<string> path;   
    int f() const { return g + H.at(v); }
};
int main(){
    auto cmp = [](const Item& a, const Item& b){ return a.f() > b.f(); };
    priority_queue<Item, vector<Item>, decltype(cmp)> pq(cmp);
    map<string,int> bestG;
    int bestGoal = INT_MAX;
    vector<string> bestPath;
    pq.push({"S", 0, {"S"}});
    bestG["S"] = 0;
    while(!pq.empty()){
        Item cur = pq.top(); pq.pop();
        if(cur.f() >= bestGoal) continue;
        if(bestG.count(cur.v) && cur.g > bestG[cur.v]) continue;
        if(cur.v == "G"){
            if(cur.g < bestGoal){ bestGoal = cur.g; bestPath = cur.path; }
            continue; 
        }
        for(auto [nxt, w] : G[cur.v]){
            int ng = cur.g + w;
            if(!bestG.count(nxt) || ng < bestG[nxt]){
                bestG[nxt] = ng;
                auto p = cur.path; p.push_back(nxt);
                pq.push({nxt, ng, p});
            }
        }
    }
    if(bestPath.empty()){
        cout << "No path to G\n";
    }else{
        cout << "Branch&Bound-Oracle path: ";
        for(size_t i=0;i<bestPath.size();++i){
            cout << bestPath[i] << (i+1<bestPath.size()?" -> ":"");
        }
        cout << "  (cost " << bestGoal << ")\n";
    }
    return 0;
}
