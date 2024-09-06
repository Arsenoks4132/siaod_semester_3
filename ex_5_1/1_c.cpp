#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

int main()
{
    unsigned int x = 25;
    const int n = 32;
    unsigned int mask = (1 << n - 1);
    cout << "Исходное число: " << x << endl;
    cout << "Начальный вид маски: " << bitset<n>(mask) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; ++i)
    {
        cout << ((x & mask) >> (n - i));
        mask = mask >> 1;
    }
    cout << endl;

    return 0;
}


