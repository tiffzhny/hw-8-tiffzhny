#include "graph.h"

int main(int argc, char *argv[]) {
    vector<string> files = {"src/small.txt", "src/medium.txt", "src/large.txt", "src/largest.txt"};

    for (const string& filename : files) {
        Graph G;
        file_to_graph(filename, G);

        cout << "=== " << filename << " ===" << endl;

        cout << "MST: ";
        EdgeList mst = Kruskals(G);
        cout << mst << endl;
        cout << "Total weight = " << sum_weights(mst) << endl;

        cout << "DFS traversal: ";
        cout << dfs(G, 0) << endl;

        cout << "BFS traversal: ";
        cout << bfs(G, 0) << endl;

        cout << endl;
    }
}