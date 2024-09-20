#include "hash.h"

using namespace std;

int main()
{
    dict d = dict();
    cout << "Элементы хеш-таблицы:\n";
    d.show();
    string code, name;

    unispec *x;

    while (true)
    {
        int choise;
        cout << endl
             << "Что вы хотите сделать?" << endl
             << "1 - Вывод содержимого" << endl
             << "2 - Добавление записи" << endl
             << "3 - Удаление записи" << endl
             << "4 - Поиск записи" << endl
             << "0 - Выход" << endl
             << "Номер действия: ";
        cin >> choise;
        cout << endl;
        if (choise == 1)
        {
            cout << "Элементы хеш-таблицы:\n";
            d.show();
        }
        else if (choise == 2)
        {
            cout << "Введите данные новой записи: ";
            x = new unispec();
            cin >> code >> name;
            x->code = code;
            x->name = name;
            d.insert(x);
        }
        else if (choise == 3)
        {
            cout << "Введите код записи для удаления: ";
            cin >> code;
            d.del(code);
        }
        else if (choise == 4)
        {
            cout << "Введите код записи для поиска: ";
            cin >> code;
            x = d.find(code);
            if (x)
            {
                cout << "Найденная запись:\n"
                     << x->code << " " << x->name;
            }
        }
        else
        {
            break;
        }
    }
}