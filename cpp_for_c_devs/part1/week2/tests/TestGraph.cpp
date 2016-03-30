#include <gtest/gtest.h>
#include "graph.h"

class GraphFixture : public testing::Test {
public:
    void SetUp() {
        g = new Graph(50);
    }
    void TearDown() {
        delete g;
    }
    Graph *g;
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
        ASSERT_EQ(0, g->getNodeValue(i));
    }
}

TEST_F(GraphFixture, SetVertexValueGetSameValue){
    g->setNodeValue(1, 1234);
    ASSERT_EQ(1234, g->getNodeValue(1));
}

TEST_F(GraphFixture, OnCreateNoCosts){
    ASSERT_EQ(g->getEdgeValue(0, 0), 0);
}

TEST_F(GraphFixture, SetCostGetSameCost){
    g->setEdgeValue(0, 0, 1234);
    ASSERT_EQ(g->getEdgeValue(0, 0), 1234);
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
    std::vector<int> result;
    g->neighbors(1, result);
    ASSERT_EQ(0, result.size());
}

TEST_F(GraphFixture, AddEdgeOneNeighbor){
    std::vector<int> result;
    g->add(1, 3);
    g->neighbors(1, result);
    ASSERT_EQ(1, result.size());
}

TEST_F(GraphFixture, Add3Edges3Neighbors){
    std::vector<int> result;
    g->add(1, 3);
    g->add(1, 8);
    g->add(1, 10);
    g->neighbors(1, result);
    ASSERT_EQ(3, result.size());
}

TEST_F(GraphFixture, AddEdgeRemoveEdgeNeighborsEmpty){
    // Why is the Graph Fixture retaining state????
    g = new Graph(50);
    // I shouldn't have to call new Graph(50) again...
    std::vector<int> result;
    g->add(1, 3);
    g->remove(1, 3);
    g->neighbors(1, result);
    ASSERT_EQ(0, result.size());
}

TEST_F(GraphFixture, AddEdgesRemoveEdgesNeighborsEmpty){
    // Why is the Graph Fixture retaining state????
    g = new Graph(50);
    // I shouldn't have to call new Graph(50) again...
    std::vector<int> result;
    g->add(1, 3);
    g->remove(1, 3);
    g->add(1, 4);
    g->remove(1, 4);
    g->neighbors(1, result);
    ASSERT_EQ(0, result.size());
}

TEST_F(GraphFixture, NoNegativeCosts){
    g->add(1, 2);
    g->setEdgeValue(1, 2, -100);
    ASSERT_EQ(0, g->getEdgeValue(1, 2));
}
