#include "Graph.h"
#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Graph graph;
    int choice;

    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "            МЕНЮ УПРАВЛЕНИЯ ГРАФОМ\n";
        std::cout << "=========================================\n";
        std::cout << "1. Добавить вершину\n";
        std::cout << "2. Добавить ребро\n";
        std::cout << "3. Удалить вершину\n";
        std::cout << "4. Удалить ребро\n";
        std::cout << "5. Сохранить граф в файл\n";
        std::cout << "6. Загрузить граф из файла\n";
        std::cout << "7. Вывести граф на экран\n";
        std::cout << "0. Выход\n";
        std::cout << "=========================================\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            int v;
            std::cout << "Введите номер вершины: ";
            std::cin >> v;
            graph.addVertex(v);
            break;
        }
        case 2:
        {
            int from, to;
            std::cout << "Введите ребро (from to): ";
            std::cin >> from >> to;
            graph.addEdge(from, to);
            break;
        }
        case 3:
        {
            int v;
            std::cout << "Введите вершину для удаления: ";
            std::cin >> v;
            graph.delVertex(v);
            break;
        }
        case 4:
        {
            int from, to;
            std::cout << "Введите ребро для удаления (from to): ";
            std::cin >> from >> to;
            graph.delEdge(from, to);
            break;
        }
        case 5:
        {
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::getline(std::cin, filename);
            graph.saveToFile(filename);
            break;
        }
        case 6:
        {
            std::string filename;
            std::cout << "Введите имя файла для загрузки: ";
            std::getline(std::cin, filename);
            graph.loadFromFile(filename);
            break;
        }
        case 7:
        {
            graph.printGraph();
            break;
        }
        case 0:
        {
            std::cout << "Выход из программы\n";
            break;
        }
        default:
        {
            std::cout << "Неверный выбор!\n";
            break;
        }
        }

        if (choice != 0)
        {
            std::cout << "\nНажмите Enter для продолжения";
            std::cin.get();
        }

    } while (choice != 0);

    return 0;
}