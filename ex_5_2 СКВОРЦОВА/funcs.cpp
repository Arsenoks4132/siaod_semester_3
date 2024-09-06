#include "funcs.h"

using namespace std;

void display(string f_name)
{
    ifstream file;
    file.open(f_name);
    string line;
    while (!file.eof())
    {
        getline(file, line);
        cout << line << endl;
    }
    file.close();
}

void add_record(string f_name)
{
    ofstream file;
    file.open(f_name, ios::app);
    string line;
    cout << "Введите числа для записи в файл: ";
    getline(cin, line);
    file << "\n"
         << line;
    cout << "Числа успешно записаны" << endl;
    file.close();
}

void read_record(string f_name)
{
    ifstream file;
    file.open(f_name);
    int x, num;
    int cnt = 0;
    cout << "Введите номер числа: ";
    cin >> num;
    while (!file.eof())
    {
        file >> x;
        if (num == cnt)
        {
            cout << "Найденное число: " << x << endl;
            return;
        }
        ++cnt;
    }
    cout << "Число не найдено" << endl;

    file.close();
}

void count_nums(string f_name)
{
    ifstream file;
    file.open(f_name);
    int x;
    int cnt = 0;
    while (!file.eof())
    {
        file >> x;
        ++cnt;
    }
    cout << "Количество чисел: " << cnt << endl;
    file.close();
}