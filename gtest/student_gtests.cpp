#include <gtest/gtest.h>
#include "graph.h"

TEST(DisjointSet, UnionAndFind) {
    DisjointSet ds(4);
    EXPECT_NE(ds.findSet(0), ds.findSet(1));
    ds.unionSets(0, 1);
    EXPECT_EQ(ds.findSet(0), ds.findSet(1));
    ds.unionSets(1, 2);
    EXPECT_EQ(ds.findSet(0), ds.findSet(2));
    EXPECT_NE(ds.findSet(0), ds.findSet(3));
}

TEST(Kruskals, SmallGraph) {
    Graph G;
    G.numVertices = 4;
    G.push_back({0, 1, 5});
    G.push_back({0, 2, 4});
    G.push_back({0, 3, 1});
    G.push_back({1, 2, 3});
    G.push_back({1, 3, 2});
    G.push_back({2, 3, 6});

    EdgeList mst = Kruskals(G);
    EXPECT_EQ(mst.size(), 6);    
    EXPECT_EQ(sum_weights(mst), 6); 
}

TEST(Kruskals, SkipsCycleEdge) {
    Graph G;
    G.numVertices = 3;
    G.push_back({0, 1, 1});
    G.push_back({1, 2, 2});
    G.push_back({0, 2, 10});

    EdgeList mst = Kruskals(G);
    EXPECT_EQ(sum_weights(mst), 3); 
}

TEST(DFS, SmallGraph) {
    Graph G;
    G.numVertices = 4;
    G.push_back({0, 1, 5});
    G.push_back({0, 2, 4});
    G.push_back({0, 3, 1});
    G.push_back({1, 2, 3});
    G.push_back({1, 3, 2});
    G.push_back({2, 3, 6});

    VertexList result = dfs(G, 0);
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0);  // always starts at 0
}

TEST(DFS, VisitsAllVertices) {
    Graph G;
    G.numVertices = 3;
    G.push_back({0, 1, 1});
    G.push_back({1, 2, 2});

    VertexList result = dfs(G, 0);
    EXPECT_EQ(result.size(), 3);
}

TEST(BFS, SmallGraph) {
    Graph G;
    G.numVertices = 4;
    G.push_back({0, 1, 5});
    G.push_back({0, 2, 4});
    G.push_back({0, 3, 1});
    G.push_back({1, 2, 3});
    G.push_back({1, 3, 2});
    G.push_back({2, 3, 6});

    VertexList result = bfs(G, 0);
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0);
}

TEST(BFS, VisitsAllVertices) {
    Graph G;
    G.numVertices = 3;
    G.push_back({0, 1, 1});
    G.push_back({1, 2, 2});

    VertexList result = bfs(G, 0);
    EXPECT_EQ(result.size(), 3);
}