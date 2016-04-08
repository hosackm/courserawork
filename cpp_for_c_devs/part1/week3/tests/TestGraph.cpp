#include <gtest/gtest.h>
#include "graph.h"
#include <list>

class GraphFixture : public testing::Test {
public:
    void SetUp() {
        g = new Graph(50);
    }
    void TearDown() {
        delete g;
    }
    Graph *g;
    std::list<int> neighbors;
};

class MSTExample : public testing::Test {
public:
    void SetUp() {
        g = new Graph(50);
        g->add(0, 0);
        g->setEdgeValue(0, 0, 99999);
        g->add(0, 1);
        g->setEdgeValue(0, 1, 2);
        g->add(0, 2);
        g->setEdgeValue(0, 2, 3);
        g->add(1, 0);
        g->setEdgeValue(1, 0, 2);
        g->add(1, 2);
        g->setEdgeValue(1, 2, 2);
        g->add(1, 3);
        g->setEdgeValue(1, 3, 4);
        g->add(1, 5);
        g->setEdgeValue(1, 5, 4);
        g->add(1, 6);
        g->setEdgeValue(1, 6, 6);
        g->add(2, 0);
        g->setEdgeValue(2, 0, 3);
        g->add(2, 1);
        g->setEdgeValue(2, 1, 2);
        g->add(2, 2);
        g->setEdgeValue(2, 2, 99999);
        g->add(2, 5);
        g->setEdgeValue(2, 5, 5);
        g->add(3, 1);
        g->setEdgeValue(3, 1, 4);
        g->add(3, 3);
        g->setEdgeValue(3, 3, 99999);
        g->add(3, 4);
        g->setEdgeValue(3, 4, 3);
        g->add(3, 6);
        g->setEdgeValue(3, 6, 5);
        g->add(4, 3);
        g->setEdgeValue(4, 3, 3);
        g->add(4, 4);
        g->setEdgeValue(4, 4, 99999);
        g->add(4, 6);
        g->setEdgeValue(4, 6, 5);
        g->add(5, 1);
        g->setEdgeValue(5, 1, 4);
        g->add(5, 2);
        g->setEdgeValue(5, 2, 5);
        g->add(5, 5);
        g->setEdgeValue(5, 5, 99999);
        g->add(5, 6);
        g->setEdgeValue(5, 6, 4);
        g->add(6, 1);
        g->setEdgeValue(6, 1, 6);
        g->add(6, 3);
        g->setEdgeValue(6, 3, 5);
        g->add(6, 4);
        g->setEdgeValue(6, 4, 5);
        g->add(6, 5);
        g->setEdgeValue(6, 5, 4);
        g->add(6, 6);
        g->setEdgeValue(6, 6, 99999);

        mst = g->primsAlgo();
    }
    void TearDown() {
        delete g;
    }
    Graph *g;
    MST mst;
};

TEST_F(GraphFixture, TestPasses){
    ASSERT_TRUE(true);
}

TEST_F(GraphFixture, OnCreateDiagonalsAreAdjacent){
    for(int i = 0; i < g->numVertices(); ++i){
        ASSERT_TRUE(g->adjacent(i, i));
    }
}

TEST_F(GraphFixture, OnCreateNonDiagonalsAreNonAdjacent){
    for(int i = 0; i < g->numVertices(); ++i){
        for(int j = 0; j < g->numVertices(); ++j){
            if(i == j){
                continue;
            }
            ASSERT_FALSE(g->adjacent(i, j));
        }
    }
}

TEST_F(GraphFixture, OnCreateNoVerticesValues){
    for(int i = 0; i < g->numVertices(); ++i){
        ASSERT_EQ(0, g->getVertexValue(i));
    }
}

TEST_F(GraphFixture, SetVertexValueGetSameValue){
    g->setVertexValue(1, 1234);
    ASSERT_EQ(1234, g->getVertexValue(1));
}

TEST_F(GraphFixture, OnCreateNoCosts){
    for(auto i = 0; i < g->numVertices(); ++i){
        for(auto j = 0; j < g->numVertices(); ++j){
            ASSERT_EQ(g->getEdgeValue(i, j), 0);
        }
    }
}

TEST_F(GraphFixture, SetCostGetSameCost){
    g->setEdgeValue(0, 0, 1234);
    ASSERT_EQ(g->getEdgeValue(0, 0), 1234);
}

TEST_F(GraphFixture, OnCreateNoNonDiagonalEdges){
    for(auto i = 0; i < g->numVertices(); ++i){
        for(auto j = 0; j < g->numVertices(); ++j){
            if(i == j) continue;
            ASSERT_FALSE(g->adjacent(i, j));
        }        
    }
}

TEST_F(GraphFixture, AddEdgeThenItExists){
    g->add(1, 3);
    ASSERT_TRUE(g->adjacent(1, 3));
    ASSERT_TRUE(g->adjacent(3, 1));
}

TEST_F(GraphFixture, RemoveEdgeThenDoesNotExists){
    g->add(1, 3);
    g->remove(3, 1);
    ASSERT_FALSE(g->adjacent(1, 3));
    ASSERT_FALSE(g->adjacent(3, 1));
}

TEST_F(GraphFixture, OnCreateNoNeighbors){
    neighbors = g->getNeighbors(1);
    ASSERT_EQ(0, neighbors.size());
}

TEST_F(GraphFixture, AddEdgeOneNeighbor){
    g->add(1, 3);
    neighbors = g->getNeighbors(1);
    ASSERT_EQ(1, neighbors.size());
}

TEST_F(GraphFixture, Add3Edges3Neighbors){
    g->add(1, 3);
    g->add(1, 8);
    g->add(1, 10);
    neighbors = g->getNeighbors(1);
    ASSERT_EQ(3, neighbors.size());
}

TEST_F(GraphFixture, AddEdgeRemoveEdgeNeighborsEmpty){
    g->add(1, 3);
    g->remove(1, 3);
    neighbors = g->getNeighbors(1);
    ASSERT_EQ(0, neighbors.size());
}

TEST_F(GraphFixture, AddEdgesRemoveEdgesNeighborsEmpty){
    g->add(1, 3);
    g->remove(1, 3);
    g->add(1, 4);
    g->remove(1, 4);
    neighbors = g->getNeighbors(1);
    ASSERT_EQ(0, neighbors.size());
}

TEST_F(GraphFixture, NoNegativeCosts){
    g->add(1, 2);
    g->setEdgeValue(1, 2, -100);
    ASSERT_EQ(0, g->getEdgeValue(1, 2));
}

TEST_F(MSTExample, MSTHasCorrectSize){
    ASSERT_EQ(7, mst.size());
}
