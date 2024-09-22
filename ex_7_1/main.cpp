#include "funcs.h"

using namespace std;

int main()
{
    avl *tree = nullptr;
    double x;
    while (true)
    {
        int choise;
        cout << endl
             << "Что вы хотите сделать?" << endl
             << "1 - Вывод содержимого" << endl
             << "2 - Добавление записи" << endl
             << "3 - Прямой обход" << endl
             << "4 - Обратный обход" << endl
             << "5 - Симметричный обход" << endl
             << "6 - Обход в ширину" << endl
             << "7 - Сумма значений листьев" << endl
             << "8 - Среднее арифметическое узлов" << endl
             << "9 - Длина пути от корня до значения" << endl
             << "10 - Высота дерева" << endl
             << "0 - Выход" << endl
             << "Номер действия: ";
        cin >> choise;
        cout << endl;

        if (choise == 2)
        {
            cout << "Введите данные новой записи: ";
            cin >> x;
            tree = insert(tree, x);
            continue;
        }

        if (!tree)
        {
            cout << "Дерево пока что пустое, нечего выводить\n";
            continue;
        }

        if (choise == 1)
        {
            cout << "AVL дерево:\n";
            tree->show_tree(tree);
            cout << endl;
        }
        else if (choise == 3)
        {
            tree->preorder();
            cout << endl;
        }
        else if (choise == 4)
        {
            tree->postorder();
            cout << endl;
        }
        else if (choise == 5)
        {
            tree->inorder();
            cout << endl;
        }
        else if (choise == 6)
        {
            tree->breadth_first();
            cout << endl;
        }
        else if (choise == 7)
        {
            cout << "Сумма значений листьев: " << tree->leaves_sum();
            cout << endl;
        }
        else if (choise == 8)
        {
            cout << "Среднее арифметическое узлов: " << tree->avg();
            cout << endl;
        }
        else if (choise == 9)
        {
            cout << "Введите искомое значение: ";
            cin >> x;
            cout << endl;
            cout << "Длина пути от корня до значения: " << tree->find_length(x);
            cout << endl;
        }
        else if (choise == 10)
        {
            cout << "Высота дерева: " << tree->find_height();
            cout << endl;
        }
        else if (choise == 0)
        {
            break;
        }
        else {
            cout << "Неизвестная команда.";
            cout << endl;
        }
    }
    return 0;
}