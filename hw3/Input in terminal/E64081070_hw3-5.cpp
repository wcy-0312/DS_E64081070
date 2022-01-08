#include<iostream>
#include<queue>
#include<vector>
#include<list>
using namespace std;

typedef pair<int, int> intPair;
# define INF 0x3f3f3f3f

class Graph{
    int V; // number of vertices
    list<intPair> *adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int c);
    void shortestPath(int s);
};

Graph::Graph(int V){
    this->V = V;
    adj = new list<intPair> [V];
}

void Graph::addEdge(int u, int v, int c){
    adj[u].push_back(make_pair(v, c));
    adj[v].push_back(make_pair(u, c));
}

void Graph::shortestPath(int src){
    priority_queue<intPair, vector<intPair>, greater<intPair>> pq;
    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        list<intPair>::iterator i;
        for(i=adj[u].begin(); i!=adj[u].end(); ++i){
            int v = (*i).first; // vertex label
            int cost = (*i).second;  // cost

            if(dist[v] > dist[u] + cost){  // shorter path through u to v
                dist[v] = dist[u] + cost;   // update distance of v
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for(int i=0; i<V; ++i)
        cout << i+1 << " " << dist[i] << endl;
}

int main(){
    int V; // number of vertices
    cin >> V;
    Graph g(V);
    int u, v, c;  // u->v with cost
    for(int i=1; i<V; i++){
        cin >> u >> v >> c;
        g.addEdge(u-1, v-1, c);
    }

    int src;  // root of the tree
    cin >> src;
    cout << endl;
    g.shortestPath(src-1);

}