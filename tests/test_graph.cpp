#include <gtest/gtest.h>
#include "Graph.h"
#include <filesystem>
#include <windows.h>

TEST(GraphTest, CreateAndCheckGraph)
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    EXPECT_TRUE(g.haveVertex(1));
    EXPECT_TRUE(g.haveVertex(2));
    EXPECT_TRUE(g.haveVertex(3));
    EXPECT_TRUE(g.haveVertex(4));
    EXPECT_EQ(g.countVertex(), 4);

    EXPECT_TRUE(g.haveEdge(1, 2));
    EXPECT_TRUE(g.haveEdge(2, 1));
    EXPECT_TRUE(g.haveEdge(1, 3));
    EXPECT_TRUE(g.haveEdge(3, 1));
    EXPECT_TRUE(g.haveEdge(2, 3));
    EXPECT_TRUE(g.haveEdge(3, 2));
    EXPECT_TRUE(g.haveEdge(3, 4));
    EXPECT_TRUE(g.haveEdge(4, 3));

    EXPECT_FALSE(g.haveEdge(1, 4));
    EXPECT_FALSE(g.haveEdge(2, 4));
    EXPECT_FALSE(g.haveEdge(4, 1));
    EXPECT_FALSE(g.haveEdge(4, 2));

    EXPECT_EQ(g.getNeighborCount(1), 2);
    EXPECT_EQ(g.getNeighborCount(2), 2);
    EXPECT_EQ(g.getNeighborCount(3), 3);
    EXPECT_EQ(g.getNeighborCount(4), 1);
}

TEST(GraphTest, AddVertexToExistingGraph)
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    g.addVertex(5);

    EXPECT_TRUE(g.haveVertex(5));
    EXPECT_EQ(g.getNeighborCount(5), 0);

    g.addEdge(5, 1);

    EXPECT_TRUE(g.haveEdge(5, 1));
    EXPECT_TRUE(g.haveEdge(1, 5));
    EXPECT_EQ(g.getNeighborCount(5), 1);
    EXPECT_EQ(g.getNeighborCount(1), 3);
}

TEST(GraphTest, RemoveVertexFromGraph)
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    EXPECT_TRUE(g.haveVertex(3));
    g.delVertex(3);

    EXPECT_FALSE(g.haveVertex(3));

    EXPECT_FALSE(g.haveEdge(1, 3));
    EXPECT_FALSE(g.haveEdge(2, 3));
    EXPECT_FALSE(g.haveEdge(3, 4));
    EXPECT_FALSE(g.haveEdge(4, 3));

    EXPECT_TRUE(g.haveEdge(1, 2));
    EXPECT_TRUE(g.haveEdge(2, 1));

    EXPECT_TRUE(g.haveVertex(4));
    EXPECT_EQ(g.getNeighborCount(4), 0);
}

TEST(GraphTest, RemoveEdgeFromGraph)
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    EXPECT_TRUE(g.haveEdge(1, 3));
    g.delEdge(1, 3);

    EXPECT_FALSE(g.haveEdge(1, 3));
    EXPECT_FALSE(g.haveEdge(3, 1));

    EXPECT_TRUE(g.haveEdge(1, 2));
    EXPECT_TRUE(g.haveEdge(2, 3));
    EXPECT_TRUE(g.haveEdge(3, 4));

    EXPECT_EQ(g.getNeighborCount(1), 1);
    EXPECT_EQ(g.getNeighborCount(3), 2);

    g.delEdge(3, 4);
    EXPECT_FALSE(g.haveEdge(3, 4));
    EXPECT_FALSE(g.haveEdge(4, 3));
    EXPECT_EQ(g.getNeighborCount(4), 0);
}

TEST(GraphTest, SaveAndLoadFile)
{
    Graph g1;
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);

    const std::string filename = "test_graph_save.txt";

    g1.saveToFile(filename);

    EXPECT_TRUE(std::filesystem::exists(filename));

    Graph g2;
    g2.loadFromFile(filename);

    EXPECT_EQ(g2.countVertex(), 4);
    EXPECT_TRUE(g2.haveVertex(1));
    EXPECT_TRUE(g2.haveVertex(2));
    EXPECT_TRUE(g2.haveVertex(3));
    EXPECT_TRUE(g2.haveVertex(4));

    EXPECT_TRUE(g2.haveEdge(1, 2));
    EXPECT_TRUE(g2.haveEdge(1, 3));
    EXPECT_TRUE(g2.haveEdge(2, 3));
    EXPECT_TRUE(g2.haveEdge(3, 4));

    EXPECT_FALSE(g2.haveEdge(1, 4));
    EXPECT_FALSE(g2.haveEdge(2, 4));

    EXPECT_EQ(g2.getNeighborCount(1), 2);
    EXPECT_EQ(g2.getNeighborCount(2), 2);
    EXPECT_EQ(g2.getNeighborCount(3), 3);
    EXPECT_EQ(g2.getNeighborCount(4), 1);

    std::filesystem::remove(filename);
}

TEST(GraphTest, ErrorOperations)
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    EXPECT_FALSE(g.haveVertex(88));
    g.delVertex(88);
    EXPECT_FALSE(g.haveEdge(1, 3));
    g.delEdge(1, 3);

    EXPECT_TRUE(g.haveEdge(1, 2));
    EXPECT_TRUE(g.haveEdge(2, 3));

    g.addEdge(5, 5);
    EXPECT_FALSE(g.haveEdge(5, 5));

    g.addEdge(1, 2);
    g.addEdge(2, 1);
    EXPECT_EQ(g.getNeighborCount(1), 1);
    EXPECT_EQ(g.getNeighborCount(2), 2);
}

TEST(GraphTest, EmptyGraphOperations)
{
    Graph g;
    EXPECT_EQ(g.countVertex(), 0);

    g.addVertex(1);
    EXPECT_TRUE(g.haveVertex(1));
    EXPECT_EQ(g.getNeighborCount(1), 0);

    g.delVertex(1);
    EXPECT_FALSE(g.haveVertex(1));
    EXPECT_EQ(g.countVertex(), 0);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    EXPECT_EQ(g.countVertex(), 3);

    g.delVertex(1);
    g.delVertex(2);
    g.delVertex(3);
    EXPECT_EQ(g.countVertex(), 0);
}

TEST(GraphTest, AddVertexAfterEdges)
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    EXPECT_TRUE(g.haveVertex(1));
    EXPECT_TRUE(g.haveVertex(2));
    EXPECT_TRUE(g.haveVertex(3));

    g.addVertex(4);
    EXPECT_TRUE(g.haveVertex(4));
    EXPECT_EQ(g.getNeighborCount(4), 0);

    g.addEdge(4, 1);
    EXPECT_TRUE(g.haveEdge(4, 1));
    EXPECT_EQ(g.getNeighborCount(4), 1);
    EXPECT_EQ(g.getNeighborCount(1), 2);
}

int main(int argc, char **argv)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}