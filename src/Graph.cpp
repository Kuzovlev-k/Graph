#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

bool contains(std::vector<int> vec, int value)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == value)
            return true;
    }
    return false;
}

void Graph::addVertex(int v)
{
    if (haveVertex(v))
    {
        std::cout << "Вершина " << v << " уже существует" << std::endl;
        return;
    }

    adjList[v] = std::vector<int>{};

    std::cout << "Добавлена вершина " << v << std::endl;
}

void Graph::addEdge(int u, int v)
{
    if (u == v)
    {
        std::cout << "Петля " << u << "-" << v << " не добавляется\n";
        return;
    }

    std::cout << "Добавляем ребро " << u << "-" << v << ": ";

    if (!haveVertex(u))
    {
        adjList[u] = std::vector<int>{};
    }
    if (!haveVertex(v))
    {
        adjList[v] = std::vector<int>{};
    }

    if (haveEdge(u, v))
    {
        std::cout << "Ребро уже есть! (пропускаем)\n";
        return;
    }

    adjList[u].push_back(v);
    adjList[v].push_back(u);

    std::cout << "Успешно добавлено!\n";
}

void Graph::delVertex(int v)
{
    if (!haveVertex(v))
    {
        std::cout << "Ошибка: вершины " << v << " нет в графе!\n";
        return;
    }

    std::cout << "Вершина найдена!\n";

    adjList.erase(v);
    std::cout << "1) Вершина " << v << " удалена из графа\n";
    int removedCount = 0;

    std::vector<int> allVertices;
    for (auto &element : adjList)
    {
        allVertices.push_back(element.first);
    }

    for (int currentVertex : allVertices)
    {
        std::vector<int> &neighbors = adjList[currentVertex];

        bool found = false;
        int foundIndex = -1;

        for (int i = 0; i < neighbors.size(); i++)
        {
            if (neighbors[i] == v)
            {
                found = true;
                foundIndex = i;
                break;
            }
        }

        if (found)
        {
            std::vector<int> newList;
            for (int j = 0; j < neighbors.size(); j++)
            {
                if (j != foundIndex)
                {
                    newList.push_back(neighbors[j]);
                }
            }
            neighbors = newList;
            removedCount++;
            std::cout << "2) Удалена из соседей вершины " << currentVertex << "\n";
        }
    }

    std::cout << "Вершина " << v << " удалена. Удалено "
              << removedCount << " упоминаний в других вершинах\n";
}

void Graph::delEdge(int from, int to)
{
    if (!haveVertex(from) || !haveVertex(to))
    {
        std::cout << "Ошибка: одной из вершин нет в графе!\n";
        return;
    }

    bool foundFromTo = false;
    std::vector<int> list1 = adjList[from];
    for (int i = 0; i < list1.size(); i++)
    {
        if (list1[i] == to)
        {
            foundFromTo = true;
            break;
        }
    }

    bool foundToFrom = false;
    std::vector<int> list2 = adjList[to];
    for (int i = 0; i < list2.size(); i++)
    {
        if (list2[i] == from)
        {
            foundToFrom = true;
            break;
        }
    }

    if (!foundFromTo || !foundToFrom)
    {
        std::cout << "Ошибка: ребра нет!\n";
        return;
    }

    std::vector<int> newList1;
    for (int i = 0; i < list1.size(); i++)
    {
        if (list1[i] != to)
        {
            newList1.push_back(list1[i]);
        }
    }
    adjList[from] = newList1;

    std::vector<int> newList2;
    for (int i = 0; i < list2.size(); i++)
    {
        if (list2[i] != from)
        {
            newList2.push_back(list2[i]);
        }
    }
    adjList[to] = newList2;

    std::cout << "Ребро удалено!\n";
}

void Graph::saveToFile(std::string filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для записи\n";
        return;
    }

    std::cout << "Сохраняем граф в файл '" << filename << "'...\n";

    file << "Вершин: " << countVertex() << "\n";

    for (const auto &element : adjList)
    {
        int vertex = element.first;
        const std::vector<int> &neighbors = element.second;

        file << vertex << ":";
        for (int n : neighbors)
        {
            file << " " << n;
        }
        file << "\n";
    }

    file.close();
    std::cout << "Граф сохранён в файл '" << filename << "'\n";
}

void Graph::loadFromFile(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла " << filename << "\n";
        return;
    }

    std::cout << "Загружаем граф из '" << filename << "'...\n";
    adjList.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line.find("Вершин:") == 0)
            continue;

        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos)
            continue;

        int vertex = std::stoi(line.substr(0, colonPos));

        std::istringstream neighborsStream(line.substr(colonPos + 1));
        int neighbor;

        if (!haveVertex(vertex))
        {
            adjList[vertex] = std::vector<int>{};
        }

        while (neighborsStream >> neighbor)
        {
            if (vertex == neighbor)
                continue;
            addEdge(vertex, neighbor);
        }
    }

    printGraph();
    std::cout << "Готово! Загружено вершин: " << countVertex() << "\n";
}

void Graph::printGraph()
{
    std::cout << "\n=== ТЕКУЩИЙ ГРАФ (" << countVertex() << " вершин) ===\n";

    if (adjList.empty())
    {
        std::cout << "пустой граф!\n";
        return;
    }

    for (auto &element : adjList)
    {
        int vertex = element.first;
        std::vector<int> neighbors = element.second;

        std::cout << vertex << ": ";
        if (neighbors.empty())
        {
            std::cout << "нет соседей";
        }
        else
        {
            for (int n : neighbors)
            {
                std::cout << n << " ";
            }
        }
        std::cout << std::endl;
    }
}