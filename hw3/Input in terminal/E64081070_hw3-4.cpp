#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int, int> intPair;
struct Graph
{
    int V, E;
    vector<pair<int, intPair>> edges;

    // Constructor
    Graph(int V, int E){
        this->V = V;
        this->E = E;
    }
    
    void addEdge(int u, int v, int cost){
        edges.push_back({cost, {u, v}});
    }

    int kruskal();

};

struct DisjointSets
{
    int *parent, *rank;
    int n;

    //Constructor
    DisjointSets(int n){
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];

        //vertices are in different sets in the begining, rank=0
        for(int i=0; i<=n; i++){
            rank[i] = 0;
            parent[i] = i;  //every element is parent of itself
        }
    }

    int find(int u) // find parent
    {
        if(u != parent[u]) parent[u]=find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y){
        x=find(x);
        y=find(y);

        if(rank[x] > rank[y]) parent[y] = x;
        else parent[x] = y;

        if(rank[x] == rank[y]) rank[y]++;
    }
};

int Graph::kruskal(){
    int total_cost = 0;
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);
    vector<pair<int, intPair>>::iterator item;
    for(item=edges.begin(); item!=edges.end(); item++){
        int u = item->second.first;
        int v = item->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        //check if edge create cycle
        if(set_u != set_v){
            total_cost += item->first;
            ds.merge(set_u, set_v);
        }
    }

    return total_cost;
}

int main(){
    int V, E;
    cin >> V >> E;
    Graph g(V, E);
    int u, v, cost;

    for(int i=0; i<E; i++){
        cin >> u >> v >> cost;
        g.addEdge(u, v, cost);
    }

    int total_cost = g.kruskal();
    cout << endl << total_cost << endl;
    return 0;
}