#include "graph.h"

DisjointSet::DisjointSet(int numVertices) : subsets(numVertices) {
    for (int i = 0; i < numVertices; i++) {
        subsets[i].parent = i;
    }
}

void DisjointSet::makeSet(Vertex x) {
    subsets[x].parent = x;
}

Vertex DisjointSet::findSet(Vertex x) {
    if (subsets[x].parent != x) {
        subsets[x].parent = findSet(subsets[x].parent);
    }
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y) {
    Vertex rootX = findSet(x);
    Vertex rootY = findSet(y);
    if (rootX == rootY) return;
    subsets[rootY].parent = rootX;
}

Graph Graph::sort_edges() const {
    Graph sorted = *this;
    sort(sorted.begin(), sorted.end(), 
        [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });
    return sorted;
}

VertexList Graph::edges_from(Vertex vertex) const {
    VertexList neighbors;
    for (const Edge& e : *this) {
        if (e.u == vertex) neighbors.push_back(e.v);
        else if (e.v == vertex) neighbors.push_back(e.u);
    }
    return neighbors;
}

EdgeList Kruskals(const Graph& G) {
    EdgeList F;
    DisjointSet ds(G.numVertices);

    Graph sorted = G.sort_edges();

    for (const Edge& e : sorted) {
        if (ds.findSet(e.u) != ds.findSet(e.v)) {
            F.push_back(Edge{e.u, e.v, e.weight});
            F.push_back(Edge{e.v, e.u, e.weight});
            ds.unionSets(e.u, e.v);
        }
    }
    return F;
}

void error(string msg) {
    cerr << msg << endl;
}

int sum_weights(EdgeList const& L) { 
    int total = 0;
    for (const Edge& e : L) {
        total += e.weight;
    }
    return total / 2;
}

VertexList dfs(const Graph& graph, Vertex startVertex) { 
    vector<Vertex> result;
    vector<bool> visited(graph.numVertices, false);
    visited[startVertex] = true;
    stack<Vertex> S;
    S.push(startVertex);

    while (!S.empty()) {
        Vertex v = S.top();
        S.pop();
        result.push_back(v);

        VertexList neighbors = graph.edges_from(v);
        sort(neighbors.begin(), neighbors.end());
        for (Vertex w : neighbors) {
            if (!visited[w]) {
                visited[w] = true;
                S.push(w);
            }
        }

    }
    return result;
}


VertexList bfs(const Graph& graph, Vertex startVertex) { 
    queue<Vertex> Q;
    vector<bool>visited(graph.numVertices, false);
    vector<Vertex> result;
    visited[startVertex] = true;
    Q.push(startVertex);

    while (!Q.empty()) {
        Vertex v = Q.front();
        Q.pop();
        result.push_back(v);

        for (Vertex w : graph.edges_from(v)) {
            if (!visited[w]) {
                visited[w] = true;
                Q.push(w);
            }
        }
    }
    return result;


}


string get_arg(int argc, char *argv[], string def) {
    if (argc > 1)
        return argv[1];
    return def;
}

void file_to_graph(string filename, Graph& G) {
    ifstream in(filename);
    if (!in) error("unable to find input file");
    in >> G;
}


