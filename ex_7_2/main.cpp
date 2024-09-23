#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

vector<vector<int>> enter_graph(int n)
{
    int x;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        cout << "Введите веса дуг, исходящих из вершины " << i << ": ";
        for (int j = 0; j < n; ++j)
        {
            cin >> x;
            graph[i][j] = x;
        }
    }
    return graph;
}

vector<vector<int>> read_graph()
{
    ifstream file("graph.txt");
    int x, n;
    file >> n;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            file >> x;
            graph[i][j] = x;
        }
    }
    file.close();
    return graph;
}

void build_graph(vector<vector<int>> &graph)
{
    int n = graph.size();
    int inf = 999;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (graph[i][j] == 0 && i != j)
            {
                graph[i][j] = inf;
            }
        }
    }
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (graph[i][k] + graph[k][j] < graph[i][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

void show_graph(vector<vector<int>> &graph)
{
    int n = graph.size();
    cout << "  \\ ";
    int offset = 0;
    for (int i = 0; i < n; ++i)
    {
        offset = (int)log10(i);
        offset = offset < 0 ? 0 : offset;
        cout << string(3 - offset, ' ') << i;
    }
    cout << endl
         << "   \\" << string(n * 4 + 1, '-') << endl;
    int x;
    for (int i = 0; i < n; ++i)
    {
        offset = (int)log10(i);
        offset = offset < 0 ? 0 : offset;
        cout << string(2 - offset, ' ') << i << "|";
        for (int j = 0; j < n; ++j)
        {
            x = graph[i][j];
            if (x != 999)
            {
                offset = (int)log10(x);
                offset = offset < 0 ? 0 : offset;
                cout << string(3 - offset, ' ') << x;
            }
            else
            {
                cout << "   -";
            }
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> graph;
    int n, i, j, s;
    while (true)
    {
        int choise;
        cout << endl
             << "Что вы хотите сделать?" << endl
             << "1 - Ввод графа с клавиатуры" << endl
             << "2 - Ввод графа из файла" << endl
             << "0 - Выход" << endl
             << "Номер действия: ";
        cin >> choise;
        cout << endl;
        if (choise == 1)
        {
            cout << "Введите количество вершин графа: ";
            cin >> n;
            graph = enter_graph(n);
            cout << endl
                 << "Граф считан:\n\n";
        }
        else if (choise == 2)
        {
            cout << "Граф считан из файла:\n\n";
            graph = read_graph();
        }
        else if (choise == 0)
        {
            break;
        }
        else
        {
            cout << "Неизвестная команда.";
            cout << endl;
            continue;
        }

        show_graph(graph);
        cout << endl;
        cout << "Введите номера начального и конечного узлов: ";
        cin >> i >> j;
        cout << "Матрица кратчайших путей:\n\n";
        build_graph(graph);
        show_graph(graph);
        s = graph[i][j];
        cout << endl;
        if (s == 999)
        {
            cout << "Между этими узлами нет соединения." << endl;
        }
        else
        {
            cout << "Расстояние между " << i << " и " << j << ": " << s;
        }
        cout << endl;
    }
    return 0;
}