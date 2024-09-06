#include "funcs.h"

using namespace std;

int main()
{
    const string f_name = "my_test.txt";

    while (true)
    {
        string f_name;
        cout << "Введите имя файла для работы или 0 для выхода: ";
        cin >> f_name;
        if (f_name == "0")
        {
            break;
        }

        ifstream iff(f_name);
        if (iff.bad() == true)
        {
            cout << "Файл с таким именем не найден." << endl;
            continue;
        }

        while (true)
        {
            int choise;
            cout << "Что вы хотите сделать?" << endl
                 << "1 - Вывод содержимого" << endl
                 << "2 - Добавление записи" << endl
                 << "3 - Найти значение по номеру" << endl
                 << "4 - Определить количество значений" << endl
                 << "0 - Выход" << endl
                 << "Номер действия: ";
            cin >> choise;
            if (choise == 1) {
                display(f_name);
            }
            else if (choise == 2) {
                add_record(f_name);
            }
            else if (choise == 3) {
                read_record(f_name);
            }
            else if (choise == 4) {
                count_nums(f_name);
            }
            else {
                break;
            }
        }
    }
}