#include <iostream>
#include <cmath>

using namespace std;

int main() {
    unsigned char x=255;
    unsigned char maska = 1;
    x = x & (~ (maska<<4));
    cout << +x;
    cout << endl;

    x = 0;
    x = x | (maska << 6);

    cout << +x;

    return 0;
}