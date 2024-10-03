#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

vector<vector<int>> count_variants(int n, int m)
{
    vector<vector<int>> arr(n, vector<int>(m, 0));
    arr[0][0] = 1;
    for (int i = 1; i < n; ++i)
    {
        arr[i][0] += arr[i - 1][0];
    }
    for (int j = 1; j < m; ++j)
    {
        arr[0][j] += arr[0][j - 1];
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            arr[i][j] += arr[i - 1][j] + arr[i][j - 1] + arr[i - 1][j - 1];
        }
    }
    return arr;
}

int min(int a, int b, int c)
{
    if (b < a)
    {
        a = b;
    }
    if (c < a)
    {
        a = c;
    }
    return a;
}

vector<vector<int>> min_sum(vector<vector<int>> &base_arr)
{
    int n = base_arr.size();
    int m = base_arr[0].size();
    vector<vector<int>> arr(n, vector<int>(m, 0));
    arr[0][0] = base_arr[0][0];
    for (int i = 1; i < n; ++i)
    {
        arr[i][0] = arr[i - 1][0] + base_arr[i][0];
    }
    for (int j = 1; j < m; ++j)
    {
        arr[0][j] = arr[0][j - 1] + base_arr[0][j];
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            arr[i][j] = base_arr[i][j] + min(arr[i - 1][j], arr[i][j - 1], arr[i - 1][j - 1]);
        }
    }
    return arr;
}

void show(vector<vector<int>> &arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = 0; j < arr[0].size(); ++j)
        {
            int x = 1;
            if (arr[i][j] > 0) {
            x = log10(arr[i][j]);
            }
            x = 10 - x;
            cout << string(x, ' ');
            cout << arr[i][j];
        }
        cout << "\n";
    }
}

vector<vector<int>> gen_random_vector(int n, int m)
{
    random_device rd;
    mt19937 gen(rd());

    vector<vector<int>> arr(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            arr[i][j] = rd() % 1000;
        }
    }
    return arr;
}

int main()
{
    const int n = 10;
    const int m = 14;
    vector<vector<int>> arr = gen_random_vector(n, m);
    cout << "Исходная матрица:\n";
    show(arr);
    cout << endl
         << "Матрица количества вариантов:\n";
    auto new_arr = count_variants(n, m);
    show(new_arr);
    cout << endl
         << "Матрица минимальных значений:\n";
    auto min_arr = min_sum(arr);
    show(min_arr);
}