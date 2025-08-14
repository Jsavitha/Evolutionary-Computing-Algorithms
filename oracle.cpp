#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
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
vector<string> oracle_path(const string& start, const string& goal){
    struct Item{ string v; int g; vector<string> path; };
    auto cmp = [&](const Item& a, const Item& b){ return a.g + H[a.v] > b.g + H[b.v]; };
    priority_queue<Item, vector<Item>, decltype(cmp)> pq(cmp);
    map<string,int> bestG; 
    pq.push({start, 0, {start}});
    bestG[start] = 0;
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        if(cur.v == goal) return cur.path;
        for(auto [nxt, w] : G[cur.v]){
            int ng = cur.g + w;
            if(!bestG.count(nxt) || ng < bestG[nxt]){
                bestG[nxt] = ng;
                auto p = cur.path; p.push_back(nxt);
                pq.push({nxt, ng, p});
            }
        }
    }
    return {}; 
}
int path_cost(const vector<string>& p){
    int sum = 0;
    for(size_t i=0; i+1<p.size(); ++i){
        const auto& u = p[i]; const auto& v = p[i+1];
        bool found=false;
        for(auto [n,w]: G[u]) if(n==v){ sum += w; found=true; break; }
        if(!found) return -1; 
    }
    return sum;
}
int main(){
    auto best = oracle_path("S","G");
    int bestCost = path_cost(best);
    vector<string> alt = {"S","B","A","D","G"};
    int altCost = path_cost(alt);
    cout << "Oracle path: ";
    for(size_t i=0;i<best.size();++i){ cout << best[i] << (i+1<best.size()?" -> ":""); }
    cout << "  (cost " << bestCost << ")\n";
    cout << "Possible path: ";
    for(size_t i=0;i<alt.size();++i){ cout << alt[i] << (i+1<alt.size()?" -> ":""); }
    cout << "  (cost " << altCost << ")\n";
}
