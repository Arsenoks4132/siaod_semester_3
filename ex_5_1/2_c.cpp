#include <iostream>

using namespace std;

int main() {
    cout << "Введите количество чисел: ";
    int n;
    cin >> n;
    unsigned char bit_arr[8];
    for (int i = 0; i < 8; ++i) {
        bit_arr[i] = 0; 
    }
    int num;
    unsigned char bit_one = 1;
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        cin >> num;
        bit_arr[(7 - num / 8)] = bit_arr[(7 - num / 8)] | (bit_one << (num % 8));
    }

    cout << endl;
    cout << "Отсортированный список:";
    for (int i = 0; i < 64; ++i) {
        if (bit_arr[(7 - i / 8)] & (bit_one << (i % 8))) {
            cout << " " << i;
        }
    }


    return 0;
}