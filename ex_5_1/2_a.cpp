#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

int main() {
    cout << "Введите количество чисел: ";
    int n;
    cin >> n;
    unsigned char bit_arr = 0;
    int num;
    unsigned char bit_num = 1;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        bit_arr = (bit_arr | (bit_num << num));
    }
    cout << "Отсортированный массив:";
    for (int i = 0; i < sizeof(bit_arr) * 8; ++i) {
        if (bit_arr & (bit_num << i)) {
            cout << " " << i;
        }
    }
    return 0;
}


