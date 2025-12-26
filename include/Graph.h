#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Graph
{
private:
    std::unordered_map<int, std::vector<int>> adjList;

public:
    bool haveVertex(int v)
    {
        return adjList.find(v) != adjList.end();
    }

    bool haveEdge(int from, int to)
    {
        if (!haveVertex(from) || !haveVertex(to))
            return false;

        std::vector<int> &neighbors = adjList[from];
        for (int n : neighbors)
        {
            if (n == to)
                return true;
        }
        return false;
    }

    int countVertex()
    {
        return adjList.size();
    }

    int getNeighborCount(int v)
    {
        if (!haveVertex(v))
            return 0;
        return adjList[v].size();
    }

    void addVertex(int v);

    void addEdge(int u, int v);

    void delVertex(int v);

    void delEdge(int from, int to);

    void saveToFile(std::string filename);

    void loadFromFile(std::string filename);

    void printGraph();
};