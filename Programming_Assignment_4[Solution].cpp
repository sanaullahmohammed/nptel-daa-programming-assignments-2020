#include<bits/stdc++.h>
using namespace std;

typedef struct Edge {
    int s, t, d;
    Edge(int s, int t, int d) {
        this->s = s, this->t = t, this->d = d;
    }
} edge;

bool comparator(edge a, edge b) {
    return a.s < b.s || (a.s == b.s && a.t < b.t);
}

class Graph {
    int n, infinite_weight = 0;
    vector<int> *adjList;
    vector<vector<int>> weights;
public:
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
        weights.resize(n+1, vector<int>(n+1, 0));
    }
    void addEdge(edge e);
    int min_distance_between(int source, int destination);
    void shortest_circular_route(vector<edge> &edges);
};

void Graph::addEdge(edge e) {
    adjList[e.s].push_back(e.t);
    adjList[e.t].push_back(e.s);
    weights[e.s][e.t] = weights[e.t][e.s] = e.d;
    infinite_weight += e.d;
}

int Graph::min_distance_between(int source, int destination) {
    vector<int> visited(n+1, 0);
    vector<int> distance(n+1, infinite_weight+1);

    distance[source] = 0;
    for(int i = 1; i <= n; i++) {
        int u, min = infinite_weight+1;
        for(int j = 1; j <= n; j++)  if(!visited[j] && distance[j] < min)  min = distance[j], u = j;
        visited[u] = 1;
        for (auto itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {
            if(distance[u] + weights[u][*itr] < distance[*itr])  distance[*itr] = distance[u] + weights[u][*itr];
        }
    }

    return distance[destination];
}

void Graph::shortest_circular_route(vector<edge> &edges) {
    int min = infinite_weight+1, cycle_distance;
    for(edge chosen : edges) {
        auto itr_s = find(adjList[chosen.s].begin(), adjList[chosen.s].end(), chosen.t);
        auto itr_t = find(adjList[chosen.t].begin(), adjList[chosen.t].end(), chosen.s);

        adjList[chosen.s].erase(itr_s); adjList[chosen.t].erase(itr_t);

        cycle_distance = weights[chosen.s][chosen.t];
        cycle_distance += min_distance_between(chosen.t, chosen.s);
        if(cycle_distance < min)  min = cycle_distance;

        adjList[chosen.s].insert(itr_s, chosen.t); adjList[chosen.t].insert(itr_t, chosen.s);
    }
    cout << min << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, t, d, vertices = 0;
    cin >> n;
    vector<edge> edges;
    for(int i = 1; i <= n; i++) {
        cin >> s >> t >> d;
        (s < t) ? edges.push_back((edge(s, t, d))) : edges.push_back((edge(t, s, d)));
        if(s > vertices)  vertices = s; if(t > vertices)  vertices = t;
    }
    sort(edges.begin(), edges.end(), &comparator);

    Graph g(vertices);
    for(int i = 0; i < n; i++)  g.addEdge(edges[i]);
    g.shortest_circular_route(edges);
    return 0;
} 
